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
 *  \file   GlyphInfo.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_GLYPHINFO_H_
#define HARFBUZZ_GLYPHINFO_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Handle.h>

namespace harfbuzz
{



class GlyphInfo:
    public Handle
{
    public:
        GlyphInfo(void* ptr);

        codepoint_t     codepoint();
        mask_t          mask();
        uint32_t        cluster();
};


class GlyphInfoArray:
    public Handle
{
    private:
        unsigned int m_length;

    public:
        GlyphInfoArray( void* ptr, unsigned int length );

        unsigned int size();

        GlyphInfo operator[](int idx);
};







} // namespace harfbuzz 

#endif // GLYPHINFO_H_
