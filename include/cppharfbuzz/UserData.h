/*
 *  \file   UserData.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_USERDATA_H_
#define CPPHARFBUZZ_USERDATA_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz
{


/// Empty base class for user data. Derive from this class and implement any
/// nontrivial destructor for your data, and it will be called when the
/// UserData object is destroyed by harfbuzz
class UserData
{
    public:
        /// opaque data structure used to uniquely identify user
        /// data with a memory address
        class Key;

        /// we may want to change key_t to something other than an internal
        /// class
        typedef Key* key_t;

        /// instanciate this to create a key
        /**
         *  So an hb_user_data_key is simply an empty struct which is
         *  instanciated for the life of the program so that it's memory
         *  address can be used as a unique key. I find this a bit odd, but
         *  I suspect that there are reasons for it.
         *
         *  I further suspect that there are plans to do more with this
         *  data structure at a later date. Thus I've implemented this key
         *  holder class. It contains one method to return a key_t* which
         *  is currently used by all the harfbuzz functions.
         *
         *  To use it, instead of declaring a global hb_user_data_key_t object,
         *  declare a UserData::KeyHolder object, and use it's get_key method
         *  wherever a user data key is needed.
         */
        class KeyHolder
        {
            private:
                Key* m_key;

            public:
                KeyHolder();
                ~KeyHolder();
                key_t get_key();
        };

        virtual ~UserData();
};

} // namespace harfbuzz 

#endif // USERDATA_H_
