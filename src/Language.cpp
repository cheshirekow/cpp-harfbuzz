/*
 *  \file   Language.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Language.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{


Language::Language()
{
    m_data = 0;
}

Language::Language(const data_t& data)
{
    m_data = data;
}

const char* Language::to_string()
{
    return hb_language_to_string( (hb_language_t)m_data );
}

Language Language::from_string(const char* str, int len)
{
    return Language( hb_language_from_string(str,len) );
}

Language Language::get_default()
{
    return Language( hb_language_get_default() );
}

Language Language::invalid()
{
    return Language( 0 );
}




} // namespace harfbuzz
