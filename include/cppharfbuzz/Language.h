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
 *  \file   Language.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_LANGUAGE_H_
#define CPPHARFBUZZ_LANGUAGE_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Handle.h>

namespace harfbuzz
{

class Language:
    public Handle
{
    private:
        void *m_ptr;

    public:
        /// wrapper constructor wraps an hb language pointer
        Language(void* ptr);

        /// returns a string representation of this language
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
