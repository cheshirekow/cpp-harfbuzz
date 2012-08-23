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
 *  along with cppharfbuzz.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   Feature.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_FEATURE_H_
#define HARFBUZZ_FEATURE_H_


#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Handle.h>
#include <cppharfbuzz/Tag.h>

namespace harfbuzz
{

/// a font-feature and a range of indices or clusters on which that
/// feature should be applied
/**
 *  Here are a list of all feature tags, however I do not know what they mean,
 *  perhaps this information can be found in documentation about different
 *  font formats
 *
 *  Some of this information came from
 *  * http://www.microsoft.com/typography/otfntdev/standot/features.aspx
 *  * http://www.microsoft.com/typography/otspec/features_ae.htm
 *  * http://www.microsoft.com/typography/otspec/features_ko.htm
 *  * http://www.microsoft.com/typography/otspec/features_pt.htm
 *  * http://www.microsoft.com/typography/otspec/features_uz.htm#valt
 *
 *  * common
 *  ** \p ccmp Character composition/decomposition substitution
 *  ** \p liga Standard ligature substitution
 *  ** \p locl Localized Forms
 *  ** \p mark Mark to base positioning
 *  ** \p mkmk Mark to mark positioning
 *  ** \p rlig Required Ligatures
 *
 *  * horizontal
 *  ** \p calt Contextual Alternates
 *  ** \p clig contextual ligature substitution
 *  ** \p curs Cursive Positioning
 *  ** \p kern Pair kerning
 *
 *  * vertical
 *  ** \p valt Alternate Vertical Metrics
 *  ** \p vert Vertical Alternates
 *  ** \p vkrn Vertical Kerning
 *  ** \p vpal Proportional Alternate Vertical Metrics
 *  ** \p vrt2 Vertical Alternates and Rotation
 */
class Feature :
    public Handle
{
    public:
        Feature( void* ptr=0 );

        Tag             tag();
        void            tag(Tag tag);

        uint32_t        value();
        void            value(uint32_t value);

        unsigned int    start();
        void            start(unsigned int start );

        unsigned int    end();
        void            end(unsigned int end);
};



class FeatureArray:
    public Handle
{
    private:
        unsigned int m_allocSize;
        unsigned int m_size;

        /// private so that it isn't used (don't copy one of these)
        FeatureArray( const FeatureArray& other );

        /// private so that it isn't used (don't copy one of these)
        template <typename T>
        FeatureArray& operator=( T );

    public:
        FeatureArray( unsigned int prealloc=0 );
        ~FeatureArray();
        void reserve( unsigned int size );
        void reset();
        unsigned int size() const;
        Feature operator[](int idx );

        void push_back( Tag             tag,
                        uint32_t        value,
                        unsigned int    start,
                        unsigned int    end );
};




} // namespace harfbuzz 

#endif // FEATURE_H_
