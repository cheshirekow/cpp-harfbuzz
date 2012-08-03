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
 *  \file   GlyphExtents.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_GLYPHEXTENTS_H_
#define HARFBUZZ_GLYPHEXTENTS_H_

#include <cppharfbuzz/Handle.h>

namespace harfbuzz
{

class GlyphExtents :
    public Handle
{
    public:
        GlyphExtents(void* ptr);

        position_t& x_bearing();
        const position_t& x_bearing() const;

        position_t& y_bearing();
        const position_t& y_bearing() const;

        position_t& width();
        const position_t& width() const;

        position_t& height();
        const position_t& height() const;
};

} // namespace freetype 

#endif // GLYPHEXTENTS_H_
