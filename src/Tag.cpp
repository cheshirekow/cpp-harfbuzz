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
 *  \file   Tag.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Tag.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{

Tag::Tag()
{

}

Tag::Tag(const data_t& data):
    m_data(data)
{
}

Tag::data_t Tag::get_data() const
{
    return m_data;
}

Tag Tag::none()
{
    return Tag(0,0,0,0);
}

Tag Tag::from_string(const char* str, int len)
{
    return Tag( hb_tag_from_string(str,len) );
}

} // namespace harfbuzz 
