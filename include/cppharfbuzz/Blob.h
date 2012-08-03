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
 *  \file   Blob.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_BLOB_H_
#define CPPHARFBUZZ_BLOB_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/UserData.h>
#include <cppharfbuzz/Handle.h>

namespace harfbuzz
{


/// I suspect that in hb a blob is a "Binary Large OBject" and it seems to be
/// used mostly by the internals of harfbuzz. I've attempted to implement this
/// wrapper object to allow for c++ objects as user data, however I suspect
/// that these parts of the interface will never be used and that a Blob will
///  never be created in user code
/**
 *  An hb_blob extends from an hb_object using plain-old-data
 *  polymorphism (i.e. the first bytes are the same as hb_object). This
 *  appears to provide reference counting and access to an array of "user_data".
 *  The hb_blob structure also contains it's own user_data in addition to
 *  the array inherited from hb_object. I will refer to this as the
 *  "priviledged" user data. It does not appear that this data is accessible
 *  after creation, and it is destroyed when the blob is destroyed
 *
 *  The harfbuzmm version of Blob contains a pointer to a hb_blob_t. When the
 *  Blob object is created the reference count of the hb_blob_t is incremented,
 *  and when the Blob object is destroyed (i.e. in it's destructor) the
 *  hb_blob_t is reference-destroyed (i.e. reference count decreases, and the
 *  object is destroyed if reference count becomes zero).
 *
 *  @note Because of the Blob wraps a reference-counted c-object
 *        it's probably a bad idea to use Blob-pointers.
 */
class Blob :
    public Handle
{
    public:
        enum MemoryMode
        {
            DUPLICATE,
            READONLY,
            WRITABLE,
            READONLY_MAY_MAKE_WRITABLE
        };

    private:
        /// increase reference count
        void reference();

        /// decrease reference count (and possibly destroy)
        void drop();

    public:
        /// the wrap constructor wraps the hb_blob_t object with a Blob, and
        /// does not increase the reference count, however the reference will
        /// be destroyed when the Blob is destroyed, so throw away the original
        /// pointer when using this constructor
        Blob( void* ptr, bool reference=false );

        /// we need a copy constructor because blobs are reference counted, the
        /// copy constructor increases the reference count of the underlying
        /// hb_blob_t
        Blob( const Blob& other );

        /// calls hb_blob_destroy which decreases the reference count and
        /// takes care of actual destruction when the last reference is
        /// dropped
        ~Blob();

        /// assignment operator, needed because blobs are reference counted
        Blob& operator=( const Blob& other );

        /// drop underlying reference and pointer
        void  invalidate();

        /// creates a new sub-blob pointing to a subset of data within this
        /// blob
        Blob create_sub( unsigned int   offset,
                         unsigned int   length );

        // assign new user data to the blob, inserting it into the base
        // class's user data array
        // bool set_user_data( UserData::key_t     key,
        //                    UserData*           user_data,
        //                    bool                replace );

        // return the user data associated with the specified key
        /*
         *  @note   be careful as this function uses an unsafe cast from a
         *          void pointer returned by hb_blob_get_user_data. If the
         *          data was inserted using the raw hg_blob_set_user_data, then
         *          this cast is invalid, so only retrieve objects using
         *          this method if you inserted them using this method.
         */
        //UserData* get_user_data( UserData::key_t key );

        void  make_immutable();
        bool  is_immutable();
        unsigned int get_length();
        const char* get_data(unsigned int *length);
        char * get_writable_data(unsigned int *length);

        /// creates a new blob and optionally assigns the priviledged user
        /// data
        /**
         *  @param data         binary data to store
         *  @param length       length of data
         *  @param mode         @see MemoryMode
         *  @param user_data    optional user data (may be null)
         *  @param destroy      pointer to function that destroys \p user_data,
         *                      must be null if \p user_data is null
         *  @return
         */
        static Blob create(
                        const char*         data,
                        unsigned int        length,
                        MemoryMode          mode,
                        void*               user_data,
                        destroy_func_t      user_destroy );

        /// not sure what an empty blob is... maybe one with zero size?
        static Blob get_empty();


};




} // namespace harfbuzz 

#endif // BLOB_H_
