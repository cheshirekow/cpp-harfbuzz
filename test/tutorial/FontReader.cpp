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
 *  \file   FontReader.cpp
 *
 *  \date   Aug 23, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "FontReader.h"

#include <cerrno>
#include <cppharfbuzz/Blob.h>
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


namespace harfbuzz {
namespace  hb_view {



FontReader::FontReader(CommandLine& cmd, freetype::Library freetype)
{
    // we'll use freetype to get the font, instead of the harfbuzz
    // example, which is inaccessible code below
    if( cmd.fontFile.getValue().size() > 0 )
    {
        freetype::Error_t ft_error;
        m_ft_face = freetype.new_face(
                            cmd.fontFile.getValue().c_str(),
                            cmd.faceIndex.getValue(),
                            ft_error);
        if(ft_error)
        {
            std::cerr << "Freetype failed to load the font file: "
                      << cmd.fontFile.getValue()
                      << std::endl;
            return;
        }

        m_font = Font::create_ft(m_ft_face,0);
    }

    return;

//-----------------------------------------------------------------------------
//         Inaccessible: This is how the harfbuzz library does it
//-----------------------------------------------------------------------------
    if( cmd.fontFile.getValue().size() > 0 )
    {
        // the c-libraries hb_view code allows a fontfile on stdin, we
        // could do the same but for now lets just keep things simple and
        // accept only a file

        // open the file
        m_fd = open( cmd.fontFile.getValue().c_str(), O_RDONLY );
        if( m_fd < 0 )
        {
            std::cerr << "Failed to open file: "
                      << cmd.fontFile.getValue()
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            return;
        }

        // stat the file to get it's size
        struct stat fs;
        int result = fstat(m_fd,&fs);
        if( result < 0 )
        {
            std::cerr << "Failed to open file: "
                      << cmd.fontFile.getValue()
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            close(m_fd);
            return;
        }

        // map the file into memory
        // offset for mmap must be page aligned ??
        // off_t offset = fs.st_size & ~( sysconf(_SC_PAGE_SIZE) -1);
        off_t offset = 0;
        m_mapLength   = fs.st_size;

        m_mapAddr = mmap( NULL, m_mapLength, PROT_READ, MAP_PRIVATE, m_fd, offset );
        if( m_mapAddr == MAP_FAILED )
        {
            std::cerr << "Failed to map file: "
                      << cmd.fontFile.getValue()
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            close(m_fd);
            return;
        }

        // Create the harfbuzz blob
        char*               font_data = (char*)m_mapAddr;
        unsigned int        data_len  = m_mapLength;
        Blob::MemoryMode    mm        = Blob::READONLY;
        void*               user_data = m_mapAddr;
        destroy_func_t      destroy   = 0;

        Blob blob = Blob::create(font_data,data_len,mm,user_data,destroy);
        Face face = Face::create(blob, cmd.faceIndex.getValue() );
        m_font = Font::create(face);
    }
}

FontReader::~FontReader()
{
    munmap(m_mapAddr,m_mapLength);
    close(m_fd);
}

Font FontReader::get_font()
{
    return m_font;
}





} // namespace hb_view 
} // namespace harfbuzz 
