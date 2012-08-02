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
 * Direction.h
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#ifndef CPPHARFBUZZ_DIRECTION_H_
#define CPPHARFBUZZ_DIRECTION_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz {



/// encapsulates an hb_direction_t object, which is a member of an anonymous
/// enumeration for directions in which the script is rendered
/**
 *  FIXME:  We shouldn't cast enums this way, we should provide a compile-time
 *          constant mapping that can be optimized out... this way if the
 *          harfbuzz enum changes, our enum will still support any values which
 *          haven't changed, and the compiler will alert us to values which
 *          have disappeared
 */
class Direction
{
    public:
        /// enumerates directions in which a script is rendered, the two
        /// least significant bits are reserved to indicate validity (they
        /// must be zero for a valid direction)
        enum Value
        {
            INVALID = 0,    /// invalid direction
            LTR     = 4,    ///< left to right
            RTL,            ///< right to left
            TTB,            ///< top to bottom
            BTT,            ///< bottom to top
        };

    private:
        Value   m_value;

    public:
        /// create a direction from a value, (note, you should probably use
        /// the predefined constants in the direction:: namespace
        Direction( Value value );

        /// return a direction which is opposite to this one
        Direction reverse();

        /// return the human readable name for this direction
        const char* to_string();

        bool is_horizontal();
        bool is_vertical();
        bool is_forward();
        bool is_backword();
        bool is_valid();

        static Direction from_string( const char* str, int len);
};


namespace direction
{
    const Direction INVALID = Direction::INVALID;
    const Direction LTR     = Direction::LTR;
    const Direction RTL     = Direction::RTL;
    const Direction TTB     = Direction::TTB;
    const Direction BTT     = Direction::BTT;
}



} // namespace harfbuzz 

#endif // DIRECTION_H_
