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
 *  \file   InputReader.cpp
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "InputReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace harfbuzz {
namespace  hb_view {





InputReader::InputReader(CommandLine& cmd)
{
    if(cmd.text.getValue().size() > 1)
    {
        std::istringstream * strStream =
                new std::istringstream( cmd.text.getValue() );
        m_ptrStream = strStream;
        m_inputType = TEXT;
    }
    else if(cmd.textFile.getValue().size() > 1)
    {
        std::ifstream* fileStream =
                new std::ifstream( cmd.textFile.getValue().c_str() );
        m_ptrStream = fileStream;
        m_inputType = FILE;
    }
    else
    {
        m_ptrStream = &std::cin;
        m_inputType = STDIN;
    }

}

InputReader::~InputReader()
{
    switch(m_inputType)
    {
        case TEXT:
        {
            std::istringstream* strStream =
                    static_cast<std::istringstream*>(m_ptrStream);
            delete strStream;
            break;
        }

        case FILE:
        {
            std::ifstream* fileStream =
                    static_cast<std::ifstream*>(m_ptrStream);
            delete fileStream;
            break;
        }

        default:
            break;
    }
}

bool InputReader::getLine( std::string& str )
{
    bool notOK = ( m_ptrStream->eof()
                    || m_ptrStream->fail()
                    || m_ptrStream->bad() );

    if(notOK)
    {
        std::cerr << "No longer reading input:";
        if( m_ptrStream->eof())
            std::cerr << "\n   eofbit";
        if( m_ptrStream->fail())
            std::cerr << "\n   failbit";
        if( m_ptrStream->bad())
            std::cerr << "\n   badbit";
        std::cerr << std::endl;
        return false;
    }

    std::getline( *m_ptrStream, str );
    return true;
}





} // namespace hb_view 
} // namespace harfbuzz 
