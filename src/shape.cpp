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
 *  \file   shape.cpp
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/shape.h>
#include <harfbuzz/hb.h>


namespace harfbuzz
{
    void shape( Font                    font,
                Buffer                  buffer,
                const FeatureArray&     features )
    {
        hb_shape(
                (hb_font_t*)            font.get_ptr(),
                (hb_buffer_t*)          buffer.get_ptr(),
                (const hb_feature_t*)   features.get_ptr(),
                                        features.size()
                );
    }

    bool shape_full( Font                   font,
                     Buffer                 buffer,
                     const FeatureArray&    features,
                     const char* const*     shaper_list )
    {
        return hb_shape_full(
                (hb_font_t*)            font.get_ptr(),
                (hb_buffer_t*)          buffer.get_ptr(),
                (const hb_feature_t*)   features.get_ptr(),
                                        features.size(),
                                        shaper_list
                );

    }

    const char** list_shapers()
    {
        return hb_shape_list_shapers();
    }
}









