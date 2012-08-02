/*
 * Direction.h
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#ifndef HARFBUZZMM_DIRECTION_H_
#define HARFBUZZMM_DIRECTION_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz {

/// encapsulates an hb_direction_t object, which is a member of an anonymous
/// enumeration for directions in which the script is rendered
/**
 *
 */
class Direction
{
    public:
        /// enumerates directions in which a script is rendered, the two
        /// least significant bits are reserved to indicate validity (they
        /// must be zero for a valid direction)
        enum EData
        {
            INVALID = 0,    /// invalid direction
            LTR     = 4,    ///< left to right
            RTL,            ///< right to left
            TTB,            ///< top to bottom
            BTT             ///< bottom to top
        };

        typedef EData data_t;

    private:
        Direction();
        data_t  m_data;

    public:
        Direction(const data_t& data);

        Direction reverse();
        const char* to_string();

        bool is_horizontal();
        bool is_vertical();
        bool is_forward();
        bool is_backword();
        bool is_valid();

        static Direction from_string( const char* str, int len);

};

} // namespace harfbuzz 

#endif // DIRECTION_H_
