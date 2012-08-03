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
 *  \file   GlyphPosition.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_GLYPHPOSITION_H_
#define HARFBUZZ_GLYPHPOSITION_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Handle.h>

namespace harfbuzz
{

class GlyphPosition :
    public Handle
{
    public:
        GlyphPosition( void* ptr );

        position_t x_advance();
        position_t y_advance();
        position_t x_offset();
        position_t y_offset();
};


class GlyphPositionArray :
    public Handle
{
    private:
        unsigned int m_length;

    public:
        GlyphPositionArray( void* ptr, unsigned int length );

        unsigned int size();

        GlyphPosition operator[](int idx );
};


} // namespace harfbuzz 

#endif // GLYPHPOSITION_H_
