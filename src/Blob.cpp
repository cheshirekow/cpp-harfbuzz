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
 *  \file   Blob.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Blob.h>
#include <harfbuzz/hb.h>
#include "UserData_Impl.h"

namespace harfbuzz
{



void Blob::reference()
{
    if(m_ptr)
        hb_blob_reference( (hb_blob_t*) m_ptr );
}

void Blob::drop()
{
    if(m_ptr)
        hb_blob_destroy( (hb_blob_t*) m_ptr );
}



Blob::Blob(const Blob& other):
    Handle(other.m_ptr)
{
    reference();
}

Blob::Blob(void* ptr, bool reference):
    Handle(ptr)
{
    m_ptr = ptr;
    if(reference)
        this->reference();
}

Blob::~Blob()
{
    drop();
}

Blob& Blob::operator=( const Blob& other )
{
    m_ptr = other.m_ptr;
    reference();
    return *this;
}

void  Blob::invalidate()
{
    drop();
    m_ptr = 0;
}

Blob Blob::create_sub(unsigned int offset, unsigned int length)
{
    return Blob( (void*)
            hb_blob_create_sub_blob( (hb_blob_t*) m_ptr,
                                    offset,
                                    length )
    );
}

//bool Blob::set_user_data(   UserData::key_t key,
//                            UserData* user_data,
//                            bool replace)
//{
//    return
//        hb_blob_set_user_data(
//                (hb_blob_t*)            m_ptr,
//                (hb_user_data_key_t*)   key,
//                                        user_data,
//                                        harfbuzmm_destroy_user_data,
//                                        replace
//                );
//}

//UserData* Blob::get_user_data(UserData::key_t key)
//{
//    void* hb_data =
//        hb_blob_get_user_data(
//                (hb_blob_t*)            m_ptr,
//                (hb_user_data_key_t*)   key
//                );
//
//    return (UserData*) hb_data;
//}

void Blob::make_immutable()
{
    hb_blob_make_immutable( (hb_blob_t*) m_ptr );
}

bool Blob::is_immutable()
{
    return hb_blob_is_immutable( (hb_blob_t*) m_ptr );
}

unsigned int Blob::get_length()
{
    return hb_blob_get_length( (hb_blob_t*) m_ptr );
}

const char* Blob::get_data(unsigned int* length)
{
    return hb_blob_get_data( (hb_blob_t*) m_ptr, length );
}

char* Blob::get_writable_data(unsigned int* length)
{
    return hb_blob_get_data_writable( (hb_blob_t*) m_ptr, length );
}

Blob Blob::create(
        const char*     data,
        unsigned int    length,
        MemoryMode      mode,
        void*           user_data,
        destroy_func_t  user_destroy)
{
    return Blob(
        hb_blob_create(
                                data,
                                length,
            (hb_memory_mode_t)  mode,
                                user_data,
                                user_destroy
        )
    );
}

Blob Blob::get_empty()
{
    return Blob(
        hb_blob_get_empty()
    );
}




} // namespace harfbuzz
