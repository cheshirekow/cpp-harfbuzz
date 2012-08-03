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
 *  \file   Feature.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/Feature.h"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <harfbuzz/hb.h>




namespace harfbuzz
{

Feature::Feature(void* ptr):
    Handle(ptr)
{

}

Tag Feature::tag()
{
    return Tag( ((hb_feature_t*)m_ptr)->tag );
}

void Feature::tag(Tag tag)
{
    ((hb_feature_t*)m_ptr)->tag = (hb_tag_t)tag.value();
}

uint32_t Feature::value()
{
    return ((hb_feature_t*)m_ptr)->value;
}

void Feature::value(uint32_t value)
{
    ((hb_feature_t*)m_ptr)->value = value;
}

unsigned int Feature::start()
{
    return ((hb_feature_t*)m_ptr)->start;
}

void Feature::start(unsigned int start)
{
    ((hb_feature_t*)m_ptr)->start = start;
}

unsigned int Feature::end()
{
    return ((hb_feature_t*)m_ptr)->end;
}

void Feature::end(unsigned int end)
{
    ((hb_feature_t*)m_ptr)->end = end;
}

FeatureArray::FeatureArray( const FeatureArray& other ):
    Handle(0)
{
    assert( false /*FeatureArray should never be copied*/ );
}

FeatureArray::FeatureArray(unsigned int size):
    Handle(0)
{
    if(size > 0)
        m_ptr = calloc( size, sizeof(hb_feature_t) );

    m_allocSize = size;
    m_size      = 0;
}

FeatureArray::~FeatureArray()
{
    if(m_ptr)
        free(m_ptr);
}

void FeatureArray::reserve(unsigned int size)
{
    if(m_ptr)
        free( m_ptr );

    m_allocSize = size;
    m_size      = 0;
}

void FeatureArray::reset()
{
    m_size = 0;
    memset(m_ptr,0, m_allocSize*sizeof(hb_feature_t) );
}

unsigned int FeatureArray::size() const
{
    return m_size;
}

Feature FeatureArray::operator [](int idx)
{
    return Feature( ((hb_feature_t*)m_ptr) +idx );
}

void FeatureArray::push_back(
        Tag tag,
        uint32_t value,
        unsigned int start,
        unsigned int end)
{
    hb_feature_t* ptr = ((hb_feature_t*)m_ptr) + m_size;
    ptr->tag    = (hb_tag_t)tag.value();
    ptr->value  = value;
    ptr->start  = start;
    ptr->end    = end;
    m_size++;
}




}


 // namespace harfbuzz 
