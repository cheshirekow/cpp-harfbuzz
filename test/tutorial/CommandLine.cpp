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
 *  \file   CommandLine.cpp
 *
 *  \date   Aug 22, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "CommandLine.h"
#include <iostream>

namespace harfbuzz {
namespace  hb_view {


static const char* g_featureInfo = "Harfbuzz demonstration viewer"
"\n    Features can be enabled or disabled, either globally or limited to "
"\n    specific character ranges."
"\n"
"\n    The range indices refer to the positions between Unicode characters,"
"\n    unless the --utf8-clusters is provided, in which case range indices"
"\n    refer to UTF-8 byte indices. The position before the first character"
"\n    is always 0."
"\n"
"\n    The format is Python-esque.  Here is how it all works:"
"\n"
"\n      Syntax:       Value:    Start:    End:"
"\n"
"\n    Setting value:"
"\n      \"kern\"        1         0         ∞         # Turn feature on"
"\n      \"+kern\"       1         0         ∞         # Turn feature on"
"\n      \"-kern\"       0         0         ∞         # Turn feature off"
"\n      \"kern=0\"      0         0         ∞         # Turn feature off"
"\n      \"kern=1\"      1         0         ∞         # Turn feature on"
"\n      \"aalt=2\"      2         0         ∞         # Choose 2nd alternate"
"\n"
"\n    Setting index:"
"\n      \"kern[]\"      1         0         ∞         # Turn feature on"
"\n      \"kern[:]\"     1         0         ∞         # Turn feature on"
"\n      \"kern[5:]\"    1         5         ∞         # Turn feature on, partial"
"\n      \"kern[:5]\"    1         0         5         # Turn feature on, partial"
"\n      \"kern[3:5]\"   1         3         5         # Turn feature on, range"
"\n      \"kern[3]\"     1         3         3+1       # Turn feature on, single char"
"\n"
"\n    Mixing it all:"
"\n"
"\n      \"kern[3:5]=0\" 1         3         5         # Turn feature off for range"
"\n";


bool CommandLine::DirectionConstraint::check(const std::string& value)
{
    if( value == "ltr" || value == "rtl" || value == "ttb" || value=="btt" )
        return true;
    else
        return false;
}

bool CommandLine::MarginConstraint::check(const int& value)
{
    return ( value < 10000 );
}

CommandLine::CommandLine():
    m_cmd("Harfbuzz demonstration viewer",' ',"-0.0"),
    fontFile("",                            // short name
             "font-file",                   // long name
              "Font file-name",             // description
              true,                         // required
              "no_font_file_specified",     // default value
              "string"                      // user readable type
            ),
    faceIndex("",
            "face-index",
            "Face index (default: 0)",
            false,
            0,
            "integer" ),
    text("",
            "text",
            "Set input text",
            false,
            "",
            "string" ),
    textFile("",
            "text-file",
            "Set input text file-name",
            false,
            "",
            "string" ),
    listShapers("l",                            // short name
            "list-shapers",                     // long name
            "List available shapers and quit",  // description
            false                               // default value
            ),
    shapers("",
            "shapers",
            "Comma-separated list of shapers to try",
            false,
            "",
            "string" ),
    direction("",
            "direction",
            "Set text direction (default: auto) ",
            false,
            "auto",
            "ltr/rtl/ttb/btt" ),
    language("",
            "language",
            "Set text language (default: $LANG)",
            false,
            "",
            "langstr" ),
    script("",
            "script",
            "Set text script (default: auto)",
            false,
            "",
            "ISO-15924 tag" ),
    utf8Clusters("",
            "utf8-clusters",
            "Use UTF8 byte indices, not char indices",
            false ),
    normalizeGlyphs("",
            "normalize-glyphs",
            "Rearrange glyph clusters in normal order",
            false ),
    features("",
            "features",
            "Comma-separated list of font features",
            false,
            "",
            "(see below)"),
    outputFilename("",
            "output-filename",
            "Set output file-name (default: stdout)",
            false,
            "",
            "string"),
    outputFormat("",
            "output-format",
            "Set output format",
            false,
            "",
            "string"),
    annotate("",
            "annotate",
            "Annotate output rendering",
            false ),
    background("",
            "background",
            "Set background color (default: #FFFFFF)",
            false,
            "#FFFFFF",
            "[name]/#rrggbb/#rrggbbaa"),
    foreground("",
            "foreground",
            "Set foreground color (default: #000000)",
            false,
            "#FFFFFF",
            "[name]/#rrggbb/#rrggbbaa"),
    linespace("",
            "linespace",
            "Set space between lines (default: 0)",
            false,
            0,
            "units"),
    margin("",
            "margin",
            "Margin around ouptput (default: 16)",
            false,
            "0 0 0 0",
            "one to four numbers"),
    fontSize("",
            "font-size",
            "Font size (default: 256)",
            false,
            256,
            "size" )
{
    m_cmd.add(fontFile);
    m_cmd.add(faceIndex);
    m_cmd.add(text);
    m_cmd.add(textFile);
    m_cmd.add(listShapers);
    m_cmd.add(shapers);
    m_cmd.add(direction);
    m_cmd.add(language);
    m_cmd.add(script);
    m_cmd.add(utf8Clusters);
    m_cmd.add(normalizeGlyphs);
    m_cmd.add(features);
    m_cmd.add(outputFilename);
    m_cmd.add(outputFormat);
    m_cmd.add(annotate);
    m_cmd.add(background);
    m_cmd.add(foreground);
    m_cmd.add(linespace);
    m_cmd.add(margin);
    m_cmd.add(fontSize);

    std::string& str = m_cmd.getMessage();
    str += g_featureInfo;
}

CommandLine::~CommandLine()
{

}

bool CommandLine::parse(int argc, char** argv)
{
    try
    {
        m_cmd.parse(argc,argv);
    }
    catch( TCLAP::ArgException &e )
    {
        std::cerr << "Error parsing command line: " << e.error()
                  << " for arg " << e.argId() << std::endl;
        return false;
    }

    return true;
}



} // namespace hb_view 
} // namespace harfbuzz 
