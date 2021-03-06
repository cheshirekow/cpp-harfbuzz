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

/// base class handle to a reference counted synchronized object
/**
 *  The underlying data is reference counted so you probably dont want to
 *  pass around Object* pointers
 *
 *  @note   An object in harfbuzz appears to be a base class used to
 *          provide generic reference counting and other things. It is not
 *          my intention to expose this implementation detail through this
 *          class. Rather, it only exists to provide some common functions
 *          used by handles
 *
 *  @note   I *believe* it is safe to reuse this code by allowing the handle
 *          of a class which derives form hb_object_t to derive from the
 *          Object handle. These classes can still override methods, but
 *          can reuse the extra overhead of this class.
 *
 *
 */
class Object
{
    private:
        void* m_ptr;  ///< pointer to the underlying hb_object

        /// increase reference count
        void reference();

        /// decrease reference count
        void drop();

    protected:
        /// wraps the hb_object_t, constructor is protected because it
        /// should only be used by derived types (there are no stand-alone
        /// hb_objects)
        Object(void* ptr);

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

        /// assignment operator, does reference management
        Object& operator=( const Object& other );

        /// DOES NOT decreases the reference count, this is protected so that
        /// no object pointers are destroyed directly
        /**
         *  @note derived objects call hb_object_destroy in their own
         *        destructors, so we don't do it here
         */
        ~Object();

        /// return the underlying hb_object_t pointer
        void* get_ptr();

        /// drops reference and sets pointer to null
        void  invalidate();

        /// returns true if underlying pointer is not null
        bool  is_valid();

    public:
        bool set_user_data( UserData::key_t key,
                            UserData* data,
                            bool replace );

        UserData* get_user_data( UserData::key_t key );




};

} // namespace harfbuzz 

#endif // OBJECT_H_
