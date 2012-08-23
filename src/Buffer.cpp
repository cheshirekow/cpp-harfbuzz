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
 *  \file   Buffer.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/Buffer.h"
#include <harfbuzz/hb.h>

namespace harfbuzz
{


void Buffer::reference()
{
    if(m_ptr)
        hb_buffer_reference( (hb_buffer_t*) (m_ptr));
}

void Buffer::drop()
{
    if(m_ptr)
        hb_buffer_destroy((hb_buffer_t*) (m_ptr));
}

Buffer::Buffer(void* ptr, bool reference) :
        Handle(ptr)
{
    if (reference)
        this->reference();
}
Buffer::Buffer(const Buffer& other) :
        Handle(other.m_ptr)
{
    reference();
}

Buffer::~Buffer()
{
    drop();
}

Buffer& Buffer::operator =(const Buffer& other)
{
    drop();
    m_ptr = other.m_ptr;
    reference();
    return *this;
}

void Buffer::invalidate()
{
    drop();
    m_ptr = 0;
}

bool Buffer::is_valid()
{
    return (m_ptr != 0);
}

Buffer Buffer::create()
{
    return Buffer(hb_buffer_create());
}

Buffer Buffer::get_empty()
{
    return Buffer(hb_buffer_get_empty());
}

void Buffer::set_direction(Direction direction)
{
    hb_buffer_set_direction((hb_buffer_t*) (m_ptr),
            (hb_direction_t)(direction.value()));
}

Direction Buffer::get_direction()
{
    return Direction(
            (Direction::Value)(hb_buffer_get_direction((hb_buffer_t*) (m_ptr))));
}

void Buffer::set_script(Script script)
{
    hb_buffer_set_script((hb_buffer_t*) (m_ptr), (hb_script_t)(script.value()));
}

Script Buffer::get_script()
{
    return Script(hb_buffer_get_script((hb_buffer_t*) (m_ptr)));
}

void Buffer::set_language(Language language)
{
    hb_buffer_set_language((hb_buffer_t*) (m_ptr),
            (hb_language_t)(language.get_ptr()));
}

Language Buffer::get_language()
{
    return Language(hb_buffer_get_language((hb_buffer_t*) (m_ptr)));
}

void Buffer::reset()
{
    hb_buffer_reset((hb_buffer_t*) (m_ptr));
}

bool Buffer::pre_allocate(unsigned int size)
{
    return hb_buffer_pre_allocate((hb_buffer_t*) (m_ptr), size);
}

bool Buffer::allocation_successful()
{
    return hb_buffer_allocation_successful((hb_buffer_t*) (m_ptr));
}

void Buffer::reverse()
{
    hb_buffer_reverse((hb_buffer_t*) (m_ptr));
}

void Buffer::reverse_clusters()
{
    hb_buffer_reverse_clusters((hb_buffer_t*) (m_ptr));
}

void Buffer::guess_properties()
{
    hb_buffer_guess_properties((hb_buffer_t*) (m_ptr));
}

void Buffer::add(codepoint_t codepoint, mask_t mask, unsigned int cluster)
{
    hb_buffer_add((hb_buffer_t*) (m_ptr), codepoint, mask, cluster);
}

void Buffer::add_utf8(const char* text, int text_length,
        unsigned int item_offset, int item_length)
{
    hb_buffer_add_utf8((hb_buffer_t*) (m_ptr), text, text_length, item_offset,
            item_length);
}

void Buffer::add_utf16(const char* text, int text_length,
        unsigned int item_offset, int item_length)
{
    hb_buffer_add_utf8((hb_buffer_t*) (m_ptr), text, text_length, item_offset,
            item_length);
}

void Buffer::add_utf32(const char* text, int text_length,
        unsigned int item_offset, int item_length)
{
    hb_buffer_add_utf8((hb_buffer_t*) (m_ptr), text, text_length, item_offset,
            item_length);
}

bool Buffer::set_length(unsigned int length)
{
    return hb_buffer_set_length((hb_buffer_t*) (m_ptr), length);
}

unsigned int Buffer::get_length()
{
    return hb_buffer_get_length((hb_buffer_t*) (m_ptr));
}

GlyphInfoArray Buffer::get_glyph_info()
{
    unsigned int        length;
    hb_glyph_info_t*    ptr;

    ptr = hb_buffer_get_glyph_infos( (hb_buffer_t*)m_ptr, &length);
    return GlyphInfoArray(ptr,length);
}

GlyphPositionArray Buffer::get_glyph_position()
{
    unsigned int            length;
    hb_glyph_position_t*    ptr;

    ptr = hb_buffer_get_glyph_positions( (hb_buffer_t*)m_ptr, &length);
    return GlyphPositionArray(ptr,length);
}

void Buffer::normalize_glyphs()
{
    hb_buffer_normalize_glyphs((hb_buffer_t*) (m_ptr));
}




} // namespace harfbuzz 
