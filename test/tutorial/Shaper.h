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
 *  \file   Shaper.h
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HB_VIEW_SHAPER_H_
#define HARFBUZZ_HB_VIEW_SHAPER_H_

#include "CommandLine.h"

#include <cppharfbuzz/Buffer.h>
#include <cppharfbuzz/Feature.h>
#include <cppharfbuzz/Font.h>


namespace harfbuzz {
namespace  hb_view {





class Shaper
{
    private:
        Buffer m_buffer;

        Direction       m_direction;
        Script          m_script;
        Language        m_language;
        FeatureArray    m_features;
        bool            m_utf8Clusters;
        char*               m_shapersStorage;
        const char* const*  m_shapers;

        void setup_buffer();

    public:
        Shaper(CommandLine& cmd);
        ~Shaper();

        void populate_buffer( std::string& str );
        bool shape( Font font );
        Buffer get_buffer();
};






} // namespace hb_view 
} // namespace harfbuzz 

#endif // SHAPER_H_
