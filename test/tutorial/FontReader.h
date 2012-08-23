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
 *  \file   FontReader.h
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HB_VIEW_FONTREADER_H_
#define HARFBUZZ_HB_VIEW_FONTREADER_H_

#include "CommandLine.h"

#include <cppfreetype/cppfreetype.h>
#include <cppharfbuzz/Font.h>
#include <cstddef>

namespace harfbuzz {
namespace  hb_view {




class FontReader
{
    private:
        freetype::Face m_ft_face;
        Font    m_font;
        int     m_fd;
        off_t   m_mapLength;
        void*   m_mapAddr;

    public:
        FontReader(CommandLine& cmd, freetype::Library freetype);
        ~FontReader();

        Font get_font();
};





} // namespace hb_view 
} // namespace harfbuzz 

#endif // FONTREADER_H_
