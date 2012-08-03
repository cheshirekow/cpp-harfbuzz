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
 *  \file   Buffer.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_BUFFER_H_
#define HARFBUZZ_BUFFER_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Direction.h>
#include <cppharfbuzz/Handle.h>
#include <cppharfbuzz/GlyphInfo.h>
#include <cppharfbuzz/GlyphPosition.h>
#include <cppharfbuzz/Language.h>
#include <cppharfbuzz/Script.h>

namespace harfbuzz
{

/// A buffer holds a string of unshaped text.
/**
 *  A general use case (taken from hb-view) is something like this
 *
 *  # call reset() to clear
 *  # use add, add_utf8, add_utf16, add_utf32 to fill it
 *  # then call shape( font, buffer, features... )
 *  # potentially normalize glyphs in the buffer
 *  # get the direction from the buffer
 *  # ask the shaper if there were clusters
 *  # get the number of glyphs with Buffer::get_length
 *  # get an array of glyph info with Buffer::get_glyph_infos
 *  # get an array of glyph positions with Buffer::get_glyph_positions
 *  # use glyph index from glyph info and draw it at the corresponding
 *    glyph position
 */
class Buffer:
    public Handle
{
    private:
        void reference();
        void drop();

    public:
        Buffer(void* ptr, bool reference=false);
        Buffer( const Buffer& other );
        ~Buffer();
        Buffer& operator=( const Buffer& other );
        void invalidate();

        static Buffer create();
        static Buffer get_empty();

        void set_direction( Direction direction );
        Direction get_direction();
        void set_script( Script script );
        Script get_script();
        void set_language( Language language );
        Language get_language();
        void reset();
        bool pre_allocate( unsigned int size );
        bool allocation_successful();
        void reverse();
        void reverse_clusters();
        void guess_properties();

        /// add a specific codepoint to the end of the buffer
        void add( codepoint_t   codepoint,
                  mask_t        mask,
                  unsigned int  cluster );

        /// add a string of utf8 encoded text to the buffer
        void add_utf8( const char*  text,
                       int          text_length,
                       unsigned int item_offset,
                       int          item_length );

        /// add a string of utf16 encoded text to the buffer
        void add_utf16( const char*  text,
                        int          text_length,
                        unsigned int item_offset,
                        int          item_length );

        /// add a string of utf32 encoded text to the buffer
        void add_utf32( const char*  text,
                        int          text_length,
                        unsigned int item_offset,
                        int          item_length );

        bool set_length( unsigned int length );
        unsigned int get_length();

        /// return the glyph info after shaping
        GlyphInfoArray      get_glyph_info();

        /// return the glyph positions after shaping
        GlyphPositionArray  get_glyph_position();

        void normalize_glyphs();




};

} // namespace harfbuzz 

#endif // BUFFER_H_
