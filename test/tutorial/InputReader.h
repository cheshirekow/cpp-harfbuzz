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
 *  \file   InputReader.h
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef HARFBUZZ_HB_VIEW_INPUTREADER_H_
#define HARFBUZZ_HB_VIEW_INPUTREADER_H_

#include "CommandLine.h"
#include <istream>

namespace harfbuzz {
namespace  hb_view {


class InputReader
{
    private:
        enum InputType{ TEXT, FILE, STDIN };

        std::istream*       m_ptrStream;
        InputType           m_inputType;

    public:
        InputReader(CommandLine& cmd);
        ~InputReader();
        bool getLine(std::string& str);
};






} // namespace hb_view 
} // namespace harfbuzz 

#endif // INPUTREADER_H_
