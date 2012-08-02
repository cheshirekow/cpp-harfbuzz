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
 *  \file   Language.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Language.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{


Language::Language()
{
    m_data = 0;
}

Language::Language(const data_t& data)
{
    m_data = data;
}

const char* Language::to_string()
{
    return hb_language_to_string( (hb_language_t)m_data );
}

Language Language::from_string(const char* str, int len)
{
    return Language( hb_language_from_string(str,len) );
}

Language Language::get_default()
{
    return Language( hb_language_get_default() );
}

Language Language::invalid()
{
    return Language( 0 );
}




} // namespace harfbuzz
