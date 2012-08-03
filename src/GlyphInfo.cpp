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
 *  \file   GlyphInfo.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/GlyphInfo.h"
#include <harfbuzz/hb.h>

namespace harfbuzz
{


GlyphInfo::GlyphInfo(void* ptr):
    Handle(ptr)
{

}



codepoint_t GlyphInfo::codepoint()
{
    return ((hb_glyph_info_t*)m_ptr)->codepoint;
}

mask_t GlyphInfo::mask()
{
    return ((hb_glyph_info_t*)m_ptr)->mask;
}

uint32_t GlyphInfo::cluster()
{
    return ((hb_glyph_info_t*)m_ptr)->cluster;
}

GlyphInfoArray::GlyphInfoArray(void* ptr, unsigned int length):
    Handle(ptr),
    m_length(length)
{

}

unsigned int GlyphInfoArray::size()
{
    return m_length;
}

GlyphInfo GlyphInfoArray::operator [](int idx)
{
    return GlyphInfo(
        ((hb_glyph_info_t*)m_ptr) + idx
    );
}


} // namespace harfbuzz 
