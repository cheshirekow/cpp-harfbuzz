/*
 *  \file   Tag.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Tag.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{

Tag::Tag()
{

}

Tag::Tag(const data_t& data):
    m_data(data)
{
}

Tag::data_t Tag::get_data() const
{
    return m_data;
}

Tag Tag::none()
{
    return Tag(0,0,0,0);
}

Tag Tag::from_string(const char* str, int len)
{
    return Tag( hb_tag_from_string(str,len) );
}

} // namespace harfbuzz 
