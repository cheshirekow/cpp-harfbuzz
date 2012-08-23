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
 *  \file   main.cpp
 *
 *  \date   Aug 22, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "CairoOutput.h"
#include "CommandLine.h"
#include "InputReader.h"
#include "FontReader.h"
#include "Shaper.h"

#include <cppfreetype/Library.h>
#include <cppharfbuzz/Buffer.h>



namespace hb=harfbuzz;
namespace ft=freetype;
using namespace harfbuzz::hb_view;

int main( int argc, char** argv )
{
    CommandLine cmd;
    cmd.parse(argc,argv);

    // initialize freetype
    ft::Error_t ft_error;
    ft::Library freetype = ft::init(ft_error);
    if(ft_error)
    {
        std::cerr << "Failed to initialize freetype" << std::endl;
        return -1;
    }

    // artificial scope
    {
        InputReader inputReader(cmd);
        FontReader  fontReader(cmd, freetype);
        Shaper      shaper(cmd);

        std::string lineText;
        hb::Buffer  buffer = hb::Buffer::create();
        hb::Font    font   = fontReader.get_font();

        CairoOutput output(cmd,font);

        // no need to print error message as the font reader will do that
        // when ever it encounters it's error... we just need to bail here
        if( !font.is_valid() ){ return -1; }

        // read lines from the input stream
        while( inputReader.getLine(lineText) )
        {
            shaper.populate_buffer(lineText);

            if( !shaper.shape(font) )
            {
                std::cerr << "Shape failed" << std::endl;
                break;
            }

            output.add_line(shaper.get_buffer(),lineText);
            std::cout << lineText << std::endl;
        }

        output.render();
    }

    ft::done(freetype);
    return 0;
}






