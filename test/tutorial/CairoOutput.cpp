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
 *  \file   CairoOutput.cpp
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "CairoOutput.h"

#include <cassert>
#include <cppfreetype/cppfreetype.h>

namespace harfbuzz {
namespace  hb_view {


static const char utf8_mask[6] =
{
    0x80,    // 1000 0000
    0xE0,    // 1110 0000
    0xF0,    // 1111 0000
    0xF8,    // 1111 1000
    0xFC,    // 1111 1100
    0xFE     // 1111 1110
};

static const char utf8_check[6] =
{
    0x00,   // 0xxx xxxx
    0xC0,   // 110x xxxx
    0xE0,   // 1110 xxxx
    0xF0,   // 1111 0xxx
    0xF8,   // 1111 10xx
    0xFC,   // 1111 110x
};


static const char* utf8_offset_to_pointer(const char* str, off_t offset)
{
    for (int i = 0; i < offset; i++)
    {
        char c = *str;
        for (int j = 0; j < 6; j++)
        {
            if ((c & utf8_mask[j]) == utf8_check[j])
            {
                str += j + 1;
                break;
            }
        }

    }

    return str;
}

CairoLine::CairoLine(Buffer buffer, std::string& text, double scale,
        bool utf8Clusters)
{
    GlyphInfoArray glyphInfos = buffer.get_glyph_info();
    GlyphPositionArray glyphPositions = buffer.get_glyph_position();
    unsigned int num_glyphs = buffer.get_length();
    assert(glyphInfos.size() == num_glyphs);
    assert(glyphPositions.size() == num_glyphs);
    Cairo::Glyph defaultGlyph =
    { 0, 0, 0 };
    m_glyphs.resize(num_glyphs + 1, defaultGlyph);
    m_utf8 = text;
    unsigned int num_clusters = num_glyphs ? 1 : 0;
    for (unsigned int i = 1; i < num_glyphs; i++)
    {
        if (glyphInfos[i].cluster() != glyphInfos[i].cluster())
            num_clusters++;
    }
    position_t x = 0;
    position_t y = 0;
    Cairo::TextCluster defaultCluster =
    { 0, 0 };
    m_clusters.resize(num_clusters, defaultCluster);
    for (unsigned int i = 0; i < glyphInfos.size(); i++)
    {
        m_glyphs[i].index = glyphInfos[i].codepoint();
        m_glyphs[i].x = (glyphPositions[i].x_offset() + x) * scale;
        m_glyphs[i].y = (-glyphPositions[i].y_offset() + y) * scale;
        x += glyphPositions[i].x_advance();
        y += -glyphPositions[i].y_advance();
    }
    m_glyphs.back().index = -1;
    m_glyphs.back().x = x * scale;
    m_glyphs.back().y = y * scale;
    if (num_clusters)
    {
        bool backward = buffer.get_direction().is_backword();
        m_flags =
                backward ? Cairo::TEXT_CLUSTER_FLAG_BACKWARD :
                        (Cairo::TextClusterFlags) 0;

        unsigned int cluster = 0;
        const char* start = m_utf8.c_str();
        const char* end;

        m_clusters[cluster].num_glyphs++;

        if (backward)
        {
            for (int i = num_glyphs - 2; i >= 0; i--)
            {
                if (glyphInfos[i].cluster() != glyphInfos[i + 1].cluster())
                {
                    assert(
                            glyphInfos[i].cluster()
                                    > glyphInfos[i + 1].cluster());
                    if (utf8Clusters)
                    {
                        end = start + glyphInfos[i].cluster()
                                - glyphInfos[i + 1].cluster();
                    }
                    else
                    {
                        end = utf8_offset_to_pointer(start,
                                glyphInfos[i].cluster()
                                        - glyphInfos[i + 1].cluster());
                    }

                    m_clusters[cluster].num_bytes = end - start;
                    start = end;
                    cluster++;
                }

                m_clusters[cluster].num_glyphs++;
            }

            m_clusters[cluster].num_bytes = m_utf8.c_str() + m_utf8.size()
                    - start;
        }
        else
        {
            for (int i = 1; i < num_glyphs; i++)
            {
                if (glyphInfos[i].cluster() != glyphInfos[i - 1].cluster())
                {
                    assert(
                            glyphInfos[i].cluster()
                                    > glyphInfos[i - 1].cluster());
                    if (utf8Clusters)
                    {
                        end = start + glyphInfos[i].cluster()
                                - glyphInfos[i - 1].cluster();
                    }
                    else
                    {
                        end = utf8_offset_to_pointer(start,
                                glyphInfos[i].cluster()
                                        - glyphInfos[i + 1].cluster());
                    }

                    m_clusters[cluster].num_bytes = end - start;
                    start = end;
                    cluster++;
                }

                m_clusters[cluster].num_glyphs++;
            }

            m_clusters[cluster].num_bytes = m_utf8.c_str() + m_utf8.size()
                    - start;
        }
    }
}

void CairoLine::get_advance(double& x, double& y)
{
    m_glyphs.back().x;
    m_glyphs.back().y;
}

CairoOutput::CairoOutput(CommandLine& cmd, Font font)
{
    m_scale         = cmd.fontSize.getValue() / font.get_face().get_upem();
    m_lineSpace     = cmd.linespace.getValue();
    m_utf8Clusters  = cmd.utf8Clusters.getValue();
    parse_margin( cmd.margin.getValue() );


    freetype::Face ft_face = font.get_ft_face();
    Cairo::RefPtr < Cairo::FontFace > cairo_face = Cairo::FtFontFace::create(
            (FT_Face)(ft_face.get_ptr()), 0);
    Cairo::Matrix ctm = Cairo::identity_matrix();
    Cairo::Matrix font_matrix = Cairo::scaling_matrix(m_scale, m_scale);
    Cairo::FontOptions font_options;
    font_options.set_hint_style(Cairo::HINT_STYLE_NONE);
    font_options.set_hint_metrics(Cairo::HINT_METRICS_OFF);
    m_font = Cairo::ScaledFont::create(cairo_face, font_matrix, ctm,
            font_options);
}

CairoOutput::~CairoOutput()
{
    m_font.clear();
    for (std::list<CairoLine*>::iterator ipLine = m_lines.begin();
            ipLine != m_lines.end(); ipLine++)
    {
        delete *ipLine;
    }
}

void CairoOutput::get_surface_size(double& w, double& h)
{
    Cairo::FontExtents ext;
    m_font->extents(ext);

    h = m_lines.size() * ( ext.height + m_lineSpace ) - m_lineSpace;
    w = 0;

    for(std::list<CairoLine*>::iterator ipLine = m_lines.begin();
            ipLine != m_lines.end(); ipLine++ )
    {
        CairoLine* pLine = *ipLine;
        double x_advance, y_advance;
        pLine->get_advance(x_advance, y_advance);
        w = std::max(w,x_advance);
    }

    w += m_margin[1] + m_margin[3];
    h += m_margin[0] + m_margin[2];
}

void CairoOutput::parse_margin( std::string& value )
{
    int nFound = sscanf( value.c_str(), "%lf %lf %lf %lf",
                        m_margin, m_margin+1, m_margin+2, m_margin+3 );

    if(!nFound)
        m_margin[0] = 0;

    for(int i=nFound; i < 4; i++)
        m_margin[i] = m_margin[i-1];
}

void CairoOutput::add_line(Buffer buffer, std::string& text)
{
    CairoLine* pLine = new CairoLine(buffer,text,m_scale,m_utf8Clusters);
    m_lines.push_back(pLine);
}








} // namespace hb_view 
} // namespace harfbuzz 