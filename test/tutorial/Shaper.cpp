/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of cppharfbuzz.
 *
 *  cppharfbuzz is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  cppharfbuzz is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   Shaper.cpp
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "Shaper.h"

#include <cppharfbuzz/shape.h>
#include <cstring>


namespace harfbuzz {
namespace  hb_view {

static inline bool is_space( char c )
{
    return (( c )==' '
                || ( c )=='\f'
                ||( c )=='\n'
                ||( c )=='\r'
                ||( c )=='\t'
                ||( c )=='\v' );
};

static inline bool is_alnum( char c )
{
    return (( 'a' <= ( c ) && ( c ) <= 'z' )
            || ( 'A' <= ( c )  && ( c ) <= 'Z' )
            || ( '0' <= ( c ) && ( c ) <= '9' ));
}


static void parse_space ( const char **pp )
{
    char c;
    while (c = **pp, is_space( c ))
        ( *pp )++;
}

static bool parse_char ( const char **pp, char c )
{
    parse_space ( pp );

    if (**pp != c)
        return false;

    ( *pp )++;
    return true;
}

static bool parse_uint ( const char **pp, unsigned int& pv )
{
    const char * p = *pp;
    char *       end;
    unsigned int v;

    v   = strtol ( p, &end, 0 );
    *pp = end;

    if (p == *pp)
        return false;

    pv = v;
    return true;
}

static bool parse_feature_value_prefix ( const char **pp, Feature feature )
{
    if (parse_char ( pp, '-' ))
        feature.value(0);
    else
    {
        parse_char ( pp, '+' );
        feature.value(1);
    }

    return true;
}

static bool parse_feature_tag ( const char **pp, Feature feature )
{
    const char *p = *pp;
    char c;

    parse_space ( pp );

    while (c = **pp, is_alnum( c ))
        ( *pp )++;

    if (p == *pp)
        return false;

    feature.tag( Tag::from_string( p, (int)(*pp - p) ) );
    return true;
}

static bool parse_feature_indices ( const char **pp, Feature feature )
{
    parse_space ( pp );

    bool has_start;

    unsigned int start = 0;
    unsigned int end   = (unsigned int) -1;

    if (!parse_char ( pp, '[' ))
        return true;

    has_start  = parse_uint ( pp, start );

    if (parse_char ( pp, ':' ))
        parse_uint ( pp, end );
    else
    {
        if (has_start)
            end = start + 1;
    }

    feature.start(start);
    feature.end(end);

    return parse_char ( pp, ']' );
}

static bool parse_feature_value_postfix ( const char **pp, Feature feature )
{
    unsigned int value;
    bool result1 = !parse_char( pp, '=' );
    bool result2 = parse_uint( pp, value );

    feature.value(value);

    return result1 || result2;
}

static bool parse_one_feature ( const char **pp, Feature feature )
{
    return parse_feature_value_prefix ( pp, feature )
           && parse_feature_tag ( pp, feature )
           && parse_feature_indices ( pp, feature )
           && parse_feature_value_postfix ( pp, feature )
           && ( parse_char ( pp, ',' ) || **pp == '\0' );
}


static void skip_one_feature( const char** pp )
{
    const char *e;
    e = strchr ( *pp, ',' );
    if (e)
        *pp = e + 1;
    else
        *pp = *pp + strlen ( *pp );
}

static void parse_shapers (
        char*&                  shapersStorage,
        const char * const *&   shapers
        )
{
    // first go through and count the number of tokens
    std::list<char*> tokList;
    char* tok   = strtok(shapersStorage,",");

    while(tok != NULL)
    {
        tokList.push_back(tok);
        tok = strtok(NULL,",");
    }

    char** tokArray = new char*[tokList.size()];
    char** nextTok  = tokArray;

    for( std::list<char*>::iterator ipChar = tokList.begin();
            ipChar != tokList.end(); ipChar++ )
    {
        *nextTok = *ipChar;
        nextTok++;
    }

    shapers = tokArray;
}


Shaper::Shaper(CommandLine& cmd)
{
    m_buffer = Buffer::create();

    m_direction = Direction::from_string(cmd.direction.getValue().c_str() );
    m_script    = Script::from_string( cmd.script.getValue().c_str() );
    m_language  = Language::from_string( cmd.language.getValue().c_str() );
    m_utf8Clusters = cmd.utf8Clusters.getValue();

    // parse shapers
    m_shapersStorage = strdup( cmd.shapers.getValue().c_str() );
    parse_shapers( m_shapersStorage, m_shapers );

    // parse features
    std::string features = cmd.features.getValue();

    const char* s = features.c_str();
    const char* p = s;
    int         num_features = 0;

    if(!*s)
        return;

    // first, count features so we can allocate memory
    while(p)
    {
        num_features++;
        p = strchr(p,',');
        if(p)
            p++;
    }

    m_features.reserve(num_features);

    // now do the actual parsing
    p    = s;
    int i= 0;
    while(*p)
    {
        if( parse_one_feature( &p, m_features[i]) )
            i++;
        else
            skip_one_feature( &p );
    }
}

Shaper::~Shaper()
{
    delete [] m_shapers;
}

void Shaper::setup_buffer()
{
    m_buffer.set_direction( m_direction );
    m_buffer.set_script( m_script );
    m_buffer.set_language( m_language );
}

void Shaper::populate_buffer(std::string& str)
{
    m_buffer.reset();
    m_buffer.add_utf8( str.c_str(), str.size(), 0, str.size() );

    if(!m_utf8Clusters)
    {
        unsigned int   num_glyphs = m_buffer.get_length();
        GlyphInfoArray info       = m_buffer.get_glyph_info();
        for( unsigned int i=0; i < num_glyphs; i++ )
            info[i].cluster() = i;
    }

    setup_buffer();
}

bool Shaper::shape(Font font)
{
    bool result = shape_full(font,m_buffer,m_features,m_shapers);
    return true;
}

Buffer Shaper::get_buffer()
{
    return m_buffer;
}




} // namespace hb_view 
} // namespace harfbuzz 
