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
 * Font.h
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#ifndef CPPHARFBUZZ_FONT_H_
#define CPPHARFBUZZ_FONT_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Direction.h>
#include <cppharfbuzz/Face.h>
#include <cppharfbuzz/GlyphExtents.h>
#include <cppharfbuzz/Handle.h>
#include <cppfreetype/cppfreetype.h>
#include <sigc++/sigc++.h>


namespace harfbuzz
{

class Font;


/// typedefs for font callback functions
namespace font
{
    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< unicode
                codepoint_t,    ///< variation_selector
                codepoint_t*,   ///< glyph
                void*           ///< user_data
                >  get_glyph_sig_t;

    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< glyph
                void*           ///< user_data
                > get_glyph_advance_sig_t;

    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< glyph
                position_t,     ///< x
                position_t,     ///< y
                void*           ///< user_data
                > get_glyph_origin_sig_t;

    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< first_glyph
                codepoint_t,    ///< second_glyph
                void*           ///< user_data
                > get_glyph_kerning_sig_t;

    typedef sigc::signal<
                Font,               ///< font
                void*,              ///< font_data
                codepoint_t,        ///< glyph
                //glyph_extents_t*, ///< extents (out)
                void*               ///< user_data
                > get_glyph_extents_sig_t;

    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< glyph
                unsigned int,   ///< point_index
                position_t*,    ///< x
                position_t*,    ///< y
                void*           ///< user_data
                > get_glyph_contour_point_sig_t;


    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                codepoint_t,    ///< glyph
                char*,          ///< name
                unsigned int,   ///< size
                void*           ///< user_data
                > get_glyph_name_sig_t;

    typedef sigc::signal<
                Font,           ///< font
                void*,          ///< font_data
                const char*,    ///< name
                int,            ///< len
                codepoint_t*,   ///< glyph
                void*           ///< user_data
                > get_glyph_from_name_sig_t;

}




/// A set of signals which are emmited by calls to font queries
/**
 *  As far as I can tell by looking at the examples, the hb_font_funcs_t
 *  structure is an interface for modularity. The callback mechanism is how
 *  harfbuzz implements this interface for different kinds of font files.
 *  It seems that these things are all implemented for opentype so perhaps
 *  this wont ever be useful.
 */
struct FontFuncs
{
     font::get_glyph_sig_t                  sig_get_glyph;
     font::get_glyph_advance_sig_t          sig_get_glyph_advance;
     font::get_glyph_origin_sig_t           sig_get_glyph_origin;
     font::get_glyph_kerning_sig_t          sig_get_glyph_kerning;
     font::get_glyph_extents_sig_t          sig_get_glyph_extents;
     font::get_glyph_contour_point_sig_t    sig_get_glyph_countour_point;
     font::get_glyph_name_sig_t             sig_get_glyph_name;
     font::get_glyph_from_name_sig_t        sig_get_glyph_from_name;
};


/// See detailed description. quote: very light weight objects
/**
 *  I'm not sure exactly what a "font" is in terms of harfbuzz but it appers
 *  to be something pretty small. At the very least, it is a reference
 *  counted object which encapsulates a set of user-defined callbacks.
 *
 *  @note   In the example in src/util the font is created from the face
 *          which is loaded from the file. So I think the font is some
 *          kind of interface object which sits on top of the face
 *
 *  @note   harfbuzz documentation says these are "very lightweight objects"
 *
 *  @note   the c interface to harfbuzz provides a set of queries which
 *          respond not by returning information, but by forwarding it to
 *          a callback. I will attempt to replace that interface with a
 *          signals and slots mechanism
 */
class Font:
    public Handle
{
    private:
        /// increase the reference count by one
        /**
         *  @note reference counting is null-safe. If the Font object is in
         *        fact porting around a null pointer then this method does
         *        nothing
         */
        void reference();

        /// decrease the reference count by one and destroy if necessary
        /**
         *  @note reference counting is null-safe. If the Font object is in
         *        fact porting around a null pointer then this method does
         *        nothing
         */
        void drop();

    public:
        /// construct a new font object which is a handle for the underlying
        /// harfbuzz object
        /**
         *  @param ptr          underlying harfbuzz_font_t*
         *  @param reference    if true, increase the reference count
         */
        Font( void* ptr=0, bool reference=false );

        /// copy constructor, create a new font object handle from a different
        /// font object handle
        /**
         *  @param other    the font object handle to copy
         *
         *  Since font's are reference counted in the c-library, this function
         *  handles dropping any current reference and taking ownerhip of
         *  a reference to the underlying harfbuzz_font_t stored in \p other
         */
        Font( const Font& other );

        /// destructor, handles decrementing reference count
        /**
         *  Since font's are reference counted in the c-library, this function
         *  handles dropping any current reference and taking ownerhip of
         *  a reference to the underlying harfbuzz_font_t stored in \p other
         */
        ~Font();

        /// assignment operator, copy font object pointer from a different
        /// font object handle
        /**
         *  @param other    the font object handle to copy
         *
         *  Since font's are reference counted in the c-library, this function
         *  handles dropping any current reference and taking ownerhip of
         *  a reference to the underlying harfbuzz_font_t stored in \p other
         */
        Font& operator=( const Font& other );

        /// drops the reference to the underlying font object, set's the
        /// stored pointer to null
        void  invalidate();

        bool    get_glyph( codepoint_t  unicode,
                           codepoint_t  variation_selector,
                           codepoint_t& glyph );

        position_t get_h_advance ( codepoint_t glyph);
        position_t get_v_advance ( codepoint_t glyph);

        bool    get_h_origin( codepoint_t glyph,
                              position_t& x,
                              position_t& y );

        bool    get_v_origin( codepoint_t glyph,
                              position_t& x,
                              position_t& y );

        position_t    get_h_kerning( codepoint_t left_glyph,
                                     codepoint_t right_glyph );

        position_t    get_v_kerning( codepoint_t left_glyph,
                                     codepoint_t right_glyph );

        bool    get_extents( codepoint_t     glyph,
                             GlyphExtents    extents );

        bool    get_contour_point( codepoint_t    glyph,
                                   unsigned int  point_index,
                                   position_t&   x,
                                   position_t&   y );

        bool    get_name( codepoint_t   glyph,
                          char*         name,
                          unsigned int  size );

        bool    get_glyph_from_name( const char*    name,
                                     int            len,
                                     codepoint_t&   glyph );

        void get_advance_for_direction( codepoint_t glyph,
                                        Direction   direction,
                                        position_t& x,
                                        position_t& y );

        void get_origin_for_direction(  codepoint_t glyph,
                                        Direction   direction,
                                        position_t& x,
                                        position_t& y );

        void add_origin_for_direction(  codepoint_t glyph,
                                        Direction   direction,
                                        position_t& x,
                                        position_t& y );

        void subtract_origin_for_direction( codepoint_t glyph,
                                            Direction   direction,
                                            position_t& x,
                                            position_t& y );

        void get_kerning_for_direction( codepoint_t first_glyph,
                                        codepoint_t second_glyph,
                                        Direction   direction,
                                        position_t& x,
                                        position_t& y );

        bool get_extents_for_origin( codepoint_t    glyph,
                                     Direction      direction,
                                     GlyphExtents   extents );

        bool get_contour_point_for_origin( codepoint_t  glyph,
                                           unsigned int point_index,
                                           Direction    direction,
                                           position_t&  x,
                                           position_t&  y );

        void set_scale( int x, int y );
        void get_scale( int& x, int& y );

        /// A zero value means "no hinting in that direction"
        void set_ppem( unsigned int x, unsigned int y );
        void get_ppem( unsigned int& x, unsigned int& y );

        /// create a harfbuzz font from a harfbuzz face
        static Font create( Face face );

        /// create a harfbuzz font directly from a freetype face
        static Font create_ft(  freetype::Face  ft_face,
                                destroy_func_t  ft_destroy=0 );

        /// make hb_font use freetype internally to implement font
        /// functions
        void set_ft_funcs();

        Face get_face();
        freetype::Face get_ft_face();




};


} // namespace harfbuzz


#endif // _FONT_H_
