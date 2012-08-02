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
 *  \file   Object.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_OBJECT_H_
#define CPPHARFBUZZ_OBJECT_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz
{

/// base class for reference counted, synchronized data structures
/**
 *  Note, object's are not virtual so don't try to destroy an Object pointer.
 *  In fact, the underlying data is reference counted so you shouldn't really
 *  use an Object pointer in the first place.
 */
class Object
{
    public:
        typedef void* data_t;

    private:
        data_t m_data;  ///< pointer to the underlying hb_object

    protected:
        /// wraps the hb_object_t, constructor is protected because it
        /// should only be used by derived types (there are no stand-alone
        /// hb_objects)
        Object(data_t data);

        /// copies the pointer to the underlying object
        /**
         *  @note   derived objects call hb_object_reference when they are
         *          referenced so the copy constructor does not do this,
         *          however it is made protected to ensure that it is only used
         *          in derived classes and to remind you to make sure
         *          that the reference count is incremented in the derived
         *          object copy constructor
         */
        Object( const Object& other );

        /// DOES NOT decreases the reference count, this is protected so that
        /// no object pointers are destroyed directly
        /**
         *  @note derived objects call hb_object_destroy in their own
         *        destructors, so we don't do it here
         */
        ~Object();

    public:
        bool set_user_data( UserData::key_t key,
                            UserData* data,
                            bool replace );

        UserData* get_user_data( UserData::key_t key );




};

} // namespace harfbuzz 

#endif // OBJECT_H_
