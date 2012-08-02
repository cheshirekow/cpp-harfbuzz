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
 *  \file   Tag.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_TAG_H_
#define CPPHARFBUZZ_TAG_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz
{

class Tag
{
    public:
        typedef uint32_t    data_t;
        static const data_t NONE = 0;

    private:
        data_t    m_data;
        Tag();

    public:
        template < typename T1, typename T2, typename T3, typename T4 >
        Tag( const T1& a, const T2& b, const T3& c, const T4& d )
        {
            m_data = (data_t)(
                            ( ((uint8_t)(a) )   << 24   )
                        |   ( ((uint8_t)(b))    << 16   )
                        |   ( ((uint8_t)(c))    << 8    )
                        |   ( ((uint8_t)(d))    << 0    )
                        );
        }

        Tag( const data_t& data );

        data_t get_data() const;

        static Tag none();

        static Tag from_string( const char* str, int len=-1);
};


template < uint8_t a, uint8_t b, uint8_t c, uint8_t d >
struct CTimeTag
{
    static const Tag::data_t value
        = (Tag::data_t)(
                    ( a << 24   )
                |   ( b << 16   )
                |   ( c << 8    )
                |   ( d << 0    )
                );
};



} // namespace harfbuzz 

#endif // TAG_H_
