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
 *  along with cppharfbuzz.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   Handle.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HANDLE_H_
#define HARFBUZZ_HANDLE_H_

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
class Handle
{
    protected:
        void* m_ptr;  ///< pointer to the underlying hb_object

        /// wraps the pointer, constructor is protected because it
        /// should only be used by derived types (there are no stand-alone
        /// hb_objects)
        Handle(void* ptr);

    public:
        /// return the underlying hb_object_t pointer
        void* get_ptr();
        const void* get_ptr() const;

        /// returns true if underlying pointer is not null
        bool  is_valid();


};




} // namespace freetype 

#endif // HANDLE_H_
