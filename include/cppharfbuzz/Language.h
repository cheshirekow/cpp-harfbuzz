/*
 *  \file   Language.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_LANGUAGE_H_
#define CPPHARFBUZZ_LANGUAGE_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz
{

class Language
{
    public:
        typedef void* data_t;

    private:
        data_t m_data;

        /// default constructor initializes data to a null pointer
        Language();

        /// wrapper constructor wraps an hb language pointer
        Language(const data_t& data);

    public:
        const char* to_string();

        /// creates a language from a string and returns
        /**
         *  @note \p len = -1 means \p str is NUL-terminated
         */
        static Language from_string( const char *str, int len=-1 );

        /// returns the default language (of the current locale?)
        static Language get_default();

        /// returns a null pointer of type Language
        static Language invalid();
};

} // namespace harfbuzz 

#endif // LANGUAGE_H_
