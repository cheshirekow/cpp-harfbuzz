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
 * Font.cpp
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Font.h>

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace harfbuzz
{

void Font::reference()
{
    if(m_ptr)
        hb_font_reference( (hb_font_t*)m_ptr );
}

void Font::drop()
{
    if(m_ptr)
        hb_font_destroy( (hb_font_t*)m_ptr );
}

Font::Font(void* ptr, bool reference) :
        Handle(ptr)
{
    if (reference)
        this->reference();
}

Font::Font(const Font& other):
    Handle(other.m_ptr)
{
    reference();
}

Font::~Font()
{
    drop();
}

Font& Font::operator =(const Font& other)
{
    drop();
    m_ptr = other.m_ptr;
    reference();
    return *this;
}

void Font::invalidate()
{
    drop();
    m_ptr = 0;
}

bool Font::get_glyph( codepoint_t  unicode,
                      codepoint_t  variation_selector,
                      codepoint_t& glyph)
{
    return hb_font_get_glyph( (hb_font_t*)m_ptr,
                                unicode,
                                variation_selector,
                                &glyph );
}

position_t Font::get_h_advance(codepoint_t glyph)
{
    return hb_font_get_glyph_h_advance( (hb_font_t*)m_ptr, glyph );
}

position_t Font::get_v_advance(codepoint_t glyph)
{
    return hb_font_get_glyph_v_advance( (hb_font_t*)m_ptr, glyph );
}

bool Font::get_h_origin(codepoint_t glyph, position_t& x, position_t& y)
{
    return hb_font_get_glyph_h_origin( (hb_font_t*)m_ptr,
                                        glyph,
                                        &x,
                                        &y );
}

bool Font::get_v_origin(codepoint_t glyph, position_t& x, position_t& y)
{
    return hb_font_get_glyph_v_origin( (hb_font_t*)m_ptr,
                                        glyph,
                                        &x,
                                        &y );
}

position_t Font::get_h_kerning(codepoint_t left_glyph, codepoint_t right_glyph)
{
    return hb_font_get_glyph_h_kerning( (hb_font_t*)m_ptr,
                                         left_glyph,
                                         right_glyph );
}

position_t Font::get_v_kerning(codepoint_t left_glyph, codepoint_t right_glyph)
{
    return hb_font_get_glyph_v_kerning( (hb_font_t*)m_ptr,
                                         left_glyph,
                                         right_glyph );
}

bool Font::get_extents(codepoint_t glyph, GlyphExtents extents)
{
    return hb_font_get_glyph_extents( (hb_font_t*)m_ptr,
                                      glyph,
                                      (hb_glyph_extents_t*)extents.get_ptr() );
}

bool Font::get_contour_point(codepoint_t  glyph,
                             unsigned int point_index,
                             position_t&  x,
                             position_t&  y)
{
    return hb_font_get_glyph_contour_point( (hb_font_t*)m_ptr,
                                            glyph,
                                            point_index,
                                            &x,
                                            &y );
}

bool Font::get_name(codepoint_t glyph, char* name, unsigned int size)
{
    return hb_font_get_glyph_name( (hb_font_t*)m_ptr, glyph, name, size );
}

bool Font::get_glyph_from_name(const char* name, int len, codepoint_t& glyph)
{
    return hb_font_get_glyph_from_name( (hb_font_t*)m_ptr, name, len, &glyph );
}

void Font::get_advance_for_direction(codepoint_t glyph, Direction direction,
        position_t& x, position_t& y)
{
    hb_font_get_glyph_advance_for_direction(
            (hb_font_t*)m_ptr,
            glyph,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

void Font::get_origin_for_direction(
        codepoint_t glyph,
        Direction   direction,
        position_t& x,
        position_t& y)
{
    hb_font_get_glyph_origin_for_direction(
            (hb_font_t*)m_ptr,
            glyph,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

void Font::add_origin_for_direction(
        codepoint_t glyph,
        Direction   direction,
        position_t& x,
        position_t& y)
{
    hb_font_add_glyph_origin_for_direction(
            (hb_font_t*)m_ptr,
            glyph,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

void Font::subtract_origin_for_direction(
        codepoint_t glyph,
        Direction direction,
        position_t& x,
        position_t& y)
{
    hb_font_subtract_glyph_origin_for_direction(
            (hb_font_t*)m_ptr,
            glyph,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

void Font::get_kerning_for_direction(
        codepoint_t first_glyph,
        codepoint_t second_glyph,
        Direction   direction,
        position_t& x,
        position_t& y)
{
    hb_font_get_glyph_kerning_for_direction(
            (hb_font_t*)m_ptr,
            first_glyph,
            second_glyph,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

bool Font::get_extents_for_origin(
        codepoint_t glyph,
        Direction direction,
        GlyphExtents extents)
{
    return hb_font_get_glyph_extents_for_origin(
            (hb_font_t*)m_ptr,
            glyph,
            (hb_direction_t)direction.value(),
            (hb_glyph_extents_t*)extents.get_ptr() );
}

bool Font::get_contour_point_for_origin(
        codepoint_t glyph,
        unsigned int point_index,
        Direction direction,
        position_t& x,
        position_t& y)
{
    return hb_font_get_glyph_contour_point_for_origin(
            (hb_font_t*)m_ptr,
            glyph,
            point_index,
            (hb_direction_t)direction.value(),
            &x,
            &y );
}

void Font::set_scale(int x, int y)
{
    hb_font_set_scale( (hb_font_t*)m_ptr, x, y );
}

void Font::get_scale(int& x, int& y)
{
    hb_font_get_scale( (hb_font_t*)m_ptr, &x, &y );
}

void Font::set_ppem(unsigned int x, unsigned int y)
{
    hb_font_set_ppem( (hb_font_t*)m_ptr, x, y );
}

void Font::get_ppem(unsigned int& x, unsigned int& y)
{
    hb_font_get_ppem( (hb_font_t*)m_ptr, &x, &y );
}

Font Font::create_ft(   freetype::Face  ft_face,
                        destroy_func_t  ft_destroy )
{
    return Font(
            hb_ft_font_create ( (FT_Face)ft_face.get_ptr(),
                                ft_destroy )
            );
}

void Font::set_ft_funcs()
{
    hb_ft_font_set_funcs( (hb_font_t*)m_ptr );
}

freetype::Face Font::get_ft_face()
{
    return freetype::Face( hb_ft_font_get_face( (hb_font_t*)m_ptr ) );
}



} /* namespace harfbuzz */
