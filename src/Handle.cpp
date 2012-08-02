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
 *  \file   Handle.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "cppharfbuzz/Handle.h"

namespace harfbuzz
{

Handle::Handle(void* ptr):
    m_ptr(ptr)
{
}

void* Handle::get_ptr()
{
    return m_ptr;
}

const void* Handle::get_ptr() const
{
    return m_ptr;
}

bool Handle::is_valid()
{
    return (m_ptr != 0);
}


} // namespace freetype 
