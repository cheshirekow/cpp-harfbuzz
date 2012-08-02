/*
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
