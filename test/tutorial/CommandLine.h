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
 *  \file   CommandLine.h
 *
 *  \date   Aug 22, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HB_VIEW_COMMANDLINE_H_
#define HARFBUZZ_HB_VIEW_COMMANDLINE_H_

#include <string>
#include <tclap/CmdLine.h>

namespace harfbuzz {
namespace  hb_view {



class CommandLine
{
    public:
        struct DirectionConstraint :
            TCLAP::Constraint<std::string>
        {
            virtual bool check(const std::string& value);
        };

        struct MarginConstraint :
            TCLAP::Constraint<int>
        {
            virtual bool check(const int& value);
        };


    private:
        TCLAP::CmdLine                  m_cmd;

    public:
        TCLAP::ValueArg<std::string>    fontFile;
        TCLAP::ValueArg<int>            faceIndex;
        TCLAP::ValueArg<std::string>    text;
        TCLAP::ValueArg<std::string>    textFile;
        TCLAP::SwitchArg                listShapers;
        TCLAP::ValueArg<std::string>    shapers;
        TCLAP::ValueArg<std::string>    direction;
        TCLAP::ValueArg<std::string>    language;
        TCLAP::ValueArg<std::string>    script;
        TCLAP::SwitchArg                utf8Clusters;
        TCLAP::SwitchArg                normalizeGlyphs;
        TCLAP::ValueArg<std::string>    features;
        TCLAP::ValueArg<std::string>    outputFilename;
        TCLAP::ValueArg<std::string>    outputFormat;
        TCLAP::SwitchArg                annotate;
        TCLAP::ValueArg<std::string>    background;
        TCLAP::ValueArg<std::string>    foreground;
        TCLAP::ValueArg<int>            linespace;
        TCLAP::ValueArg<std::string>    margin;
        TCLAP::ValueArg<int>            fontSize;



    public:
        CommandLine();
        ~CommandLine();

        bool parse(int argc, char** argv);
};

} // namespace hb_view 
} // namespace harfbuzz 

#endif // COMMANDLINE_H_
