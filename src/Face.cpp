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
 *  \file   Face.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/Face.h"

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace harfbuzz
{

void Face::reference()
{
    if(m_ptr)
        hb_face_reference( (hb_face_t*) (m_ptr));
}
void Face::drop()
{
    if (m_ptr)
        hb_face_destroy((hb_face_t*) (m_ptr));
}
Face::Face(void* ptr, bool reference) :
        Handle(ptr)
{
    if (reference)
        this->reference();
}
Face::Face(const Face& other) :
        Handle(other.m_ptr)
{
    reference();
}

Face::~Face()
{
    drop();
}

Face& Face::operator =(const Face& other)
{
    drop();
    m_ptr = other.m_ptr;
    reference();
    return *this;
}

void Face::invalidate()
{
    drop();
    m_ptr = 0;
}





void Face::make_immutable()
{
    hb_face_make_immutable( (hb_face_t*)m_ptr );
}

bool Face::is_immutable()
{
    return hb_face_is_immutable(  (hb_face_t*)m_ptr  );
}

Blob Face::reference_table(Tag tag)
{
    return Blob(
        hb_face_reference_table( (hb_face_t*)m_ptr, tag.value() )
    );
}

Blob Face::reference_blob()
{
    return Blob(
        hb_face_reference_blob(  (hb_face_t*)m_ptr  )
    );
}

void Face::set_index(unsigned int index)
{
    hb_face_set_index( (hb_face_t*)m_ptr, index );
}

unsigned int Face::get_index()
{
    return hb_face_get_index( (hb_face_t*)m_ptr );
}

void Face::set_upem(unsigned int upem)
{
    hb_face_set_upem( (hb_face_t*)m_ptr, upem );
}

unsigned int Face::get_upem()
{
    return hb_face_get_upem( (hb_face_t*)m_ptr );
}






Face Face::create(Blob blob, unsigned int index)
{
    return Face(hb_face_create((hb_blob_t*) (blob.get_ptr()), index));
}

Face Face::create_ft(freetype::Face ft_face, destroy_func_t user_destroy)
{
    return Face(hb_ft_face_create((FT_Face)(ft_face.get_ptr()), user_destroy));
}



Face Face::create_ft_cached(freetype::Face ft_face)
{
    return Face(hb_ft_face_create_cached((FT_Face)(ft_face.get_ptr()) )
    );
}



} // namespace harfbuzz 
