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
 *  \file   CairoOutput.h
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HB_VIEW_CAIROOUTPUT_H_
#define HARFBUZZ_HB_VIEW_CAIROOUTPUT_H_

#include "CommandLine.h"

#include <cairomm/cairomm.h>
#include <cppharfbuzz/Buffer.h>
#include <cppharfbuzz/Font.h>
#include <vector>

namespace harfbuzz {
namespace  hb_view {


struct CairoLine
{
    std::vector< Cairo::Glyph >         m_glyphs;
    std::vector< Cairo::TextCluster >   m_clusters;
    Cairo::TextClusterFlags             m_flags;
    std::string                         m_utf8;

    CairoLine( Buffer buffer, std::string& text,
                    double scale, bool utf8Clusters );
    void get_advance( double& x, double& y );
};


class CairoOutput
{
    private:
        Cairo::RefPtr<Cairo::ScaledFont>    m_font;
        std::list< CairoLine* >             m_lines;

        std::string     m_filename;
        std::string     m_format;

        double m_lineSpace;
        double m_scale;
        double m_margin[4];
        bool   m_utf8Clusters;
        bool   m_annotate;

        void get_surface_size( double& w, double& h);
        void parse_margin( std::string& value );

    public:
        CairoOutput(CommandLine& cmd, Font font);
        ~CairoOutput();

        void add_line( Buffer buffer, std::string& text);
        void render();
};





} // namespace hb_view 
} // namespace harfbuzz 

#endif // CAIROOUTPUT_H_
