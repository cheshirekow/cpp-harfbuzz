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
 *  \file   UserData.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/UserData.h>
#include "UserData_Impl.h"
#include <harfbuzz/hb.h>

namespace harfbuzz
{

// I *think* this ensures that UserData::Key is a POD which is interchangable
// with hb_user_data_key_t
class UserData::Key
{
    hb_user_data_key_t  base;
};


UserData::KeyHolder::KeyHolder()
{
    m_key = new UserData::Key;
}

UserData::KeyHolder::~KeyHolder()
{
    delete m_key;
}

UserData::key_t UserData::KeyHolder::get_key()
{
    return m_key;
}


UserData::~UserData()
{
}


void harfbuzmm_destroy_user_data(void* data)
{
    UserData* casted = static_cast<UserData*>(data);
    delete casted;
}

} // namespace harfbuzz 
