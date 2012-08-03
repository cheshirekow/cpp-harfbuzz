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
 *  \file   Face.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_FACE_H_
#define HARFBUZZ_FACE_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Blob.h>
#include <cppharfbuzz/Handle.h>
#include <cppharfbuzz/Tag.h>
#include <cppfreetype/cppfreetype.h>

namespace harfbuzz
{

/// a typeface within a fontfile
class Face:
    public Handle
{
    private:
        void reference();
        void drop();

    public:
        Face(void* ptr, bool reference=false);
        Face( const Face& other );
        ~Face();
        Face& operator=( const Face& other );
        void invalidate();



        void make_immutable();
        bool is_immutable();
        Blob reference_table( Tag tag );
        Blob reference_blob( );
        void set_index( unsigned int index );
        unsigned int get_index();
        void set_upem( unsigned int upem );
        unsigned int get_upem();



        /// create a face from a font file which is loaded into memory
        static Face create( Blob blob, unsigned int index );

        /// create a harfbuzz face from a freetype face
        static Face create_ft(  freetype::Face  ft_face,
                                destroy_func_t  user_destroy);

        /// create a harfbuzz face from a chached freetype face
        static Face create_ft_cached( freetype::Face  ft_face );


};

} // namespace harfbuzz 

#endif // FACE_H_
