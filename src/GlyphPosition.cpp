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
 *  \file   GlyphPosition.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/GlyphPosition.h"
#include <harfbuzz/hb.h>

namespace harfbuzz
{


GlyphPosition::GlyphPosition( void* ptr ):
    Handle(ptr)
{
}





position_t GlyphPosition::x_advance()
{
    return ((hb_glyph_position_t*)m_ptr)->x_advance;
}

position_t GlyphPosition::y_advance()
{
    return ((hb_glyph_position_t*)m_ptr)->y_advance;
}

position_t GlyphPosition::x_offset()
{
    return ((hb_glyph_position_t*)m_ptr)->x_offset;
}

position_t GlyphPosition::y_offset()
{
    return ((hb_glyph_position_t*)m_ptr)->y_offset;
}




GlyphPositionArray::GlyphPositionArray(void* ptr, unsigned int length ):
    Handle(ptr),
    m_length(length)
{
}


unsigned int GlyphPositionArray::size()
{
    return m_length;
}

GlyphPosition GlyphPositionArray::operator [](int idx)
{
    return GlyphPosition( ((hb_glyph_position_t*)m_ptr) + idx );
}





} // namespace harfbuzz 
