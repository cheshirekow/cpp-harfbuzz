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
 *  \file   GlyphExtents.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/GlyphExtents.h"

#include <harfbuzz/hb.h>

namespace harfbuzz
{

GlyphExtents::GlyphExtents(void* ptr):
    Handle(ptr)
{

}

position_t& GlyphExtents::x_bearing()
{
    return ((hb_glyph_extents_t*)m_ptr)->x_bearing;
}

const position_t& GlyphExtents::x_bearing() const
{
    return ((hb_glyph_extents_t*)m_ptr)->x_bearing;
}

position_t& GlyphExtents::y_bearing()
{
    return ((hb_glyph_extents_t*)m_ptr)->y_bearing;
}

const position_t& GlyphExtents::y_bearing() const
{
    return ((hb_glyph_extents_t*)m_ptr)->y_bearing;
}

position_t& GlyphExtents::width()
{
    return ((hb_glyph_extents_t*)m_ptr)->width;
}

const position_t& GlyphExtents::width() const
{
    return ((hb_glyph_extents_t*)m_ptr)->width;
}

position_t& GlyphExtents::height()
{
    return ((hb_glyph_extents_t*)m_ptr)->height;
}

const position_t& GlyphExtents::height() const
{
    return ((hb_glyph_extents_t*)m_ptr)->height;
}






} // namespace freetype 
