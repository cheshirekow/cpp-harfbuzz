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
 *  \file   Script.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Script.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{

Script::Script()
{
    m_data = (data_t)Tag::NONE;
}


Script::Script(const data_t& data)
{
    m_data = data;
}

Script Script::from_iso15924_tag(const Tag& tag)
{
    return Script( (data_t)hb_script_from_iso15924_tag( tag.get_data() ) );
}

Script Script::from_string(const char* str, int len)
{
    return Script( (data_t)hb_script_from_string(str, len) );
}

Tag Script::to_iso15924_tag()
{
    return Tag( hb_script_to_iso15924_tag( (hb_script_t)m_data) );
}

Direction Script::get_horizontal_direction()
{
    return Direction( (Direction::data_t)hb_script_get_horizontal_direction( (hb_script_t)m_data ) );
}

} // namespace harfbuzz 
