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
 *  \file   shape.h
 *
 *  \date   Aug 2, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_SHAPE_H_
#define HARFBUZZ_SHAPE_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Buffer.h>
#include <cppharfbuzz/Feature.h>
#include <cppharfbuzz/Font.h>

namespace harfbuzz
{

    void shape( Font                    font,
                Buffer                  buffer,
                const FeatureArray&     features );

    bool shape_full( Font                   font,
                     Buffer                 buffer,
                     const FeatureArray&    features,
                     const char* const*     shaper_list );

    const char** list_shapers();
}















#endif // SHAPE_H_
