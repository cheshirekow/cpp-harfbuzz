/*
 * Direction.cpp
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#include <cppharfbuzz/Direction.h>
#include <harfbuzz/hb.h>

namespace harfbuzz {

Direction::Direction()
{
    m_data = INVALID;
}


Direction::Direction(const data_t& data)
{
    m_data = data;
}

const char* Direction::to_string()
{
    return hb_direction_to_string( (hb_direction_t)m_data );
}


Direction Direction::reverse()
{
    return Direction( (data_t)HB_DIRECTION_REVERSE(m_data) );
}

Direction Direction::from_string(const char* str, int len)
{
    return Direction( (data_t)hb_direction_from_string(str, len) );
}

bool Direction::is_horizontal()
{
    return HB_DIRECTION_IS_HORIZONTAL(m_data);
}

bool Direction::is_vertical()
{
    return HB_DIRECTION_IS_VERTICAL(m_data);
}

bool Direction::is_forward()
{
    return HB_DIRECTION_IS_FORWARD(m_data);
}

bool Direction::is_backword()
{
    return HB_DIRECTION_IS_BACKWARD(m_data);
}

bool Direction::is_valid()
{
    return HB_DIRECTION_IS_VALID(m_data);
}





} // namespace harfbuzz 
