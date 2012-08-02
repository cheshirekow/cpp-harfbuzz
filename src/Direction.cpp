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
/*
 * Direction.cpp
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#include <cppharfbuzz/Direction.h>
#include <harfbuzz/hb.h>

namespace harfbuzz {


const char* Direction::to_string()
{
    return hb_direction_to_string( (hb_direction_t)m_value );
}


Direction Direction::reverse()
{
    return (Value)HB_DIRECTION_REVERSE(m_value);
}

Direction Direction::from_string(const char* str, int len)
{
    return (Value)hb_direction_from_string(str, len);
}

bool Direction::is_horizontal()
{
    return HB_DIRECTION_IS_HORIZONTAL(m_value);
}

bool Direction::is_vertical()
{
    return HB_DIRECTION_IS_VERTICAL(m_value);
}

bool Direction::is_forward()
{
    return HB_DIRECTION_IS_FORWARD(m_value);
}

bool Direction::is_backword()
{
    return HB_DIRECTION_IS_BACKWARD(m_value);
}

bool Direction::is_valid()
{
    return HB_DIRECTION_IS_VALID(m_value);
}





} // namespace harfbuzz 
