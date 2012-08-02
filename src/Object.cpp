/*
 *  \file   Object.cpp
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cppharfbuzz/Object.h>
#include <harfbuzz/hb.h>

namespace harfbuzz
{


Object::Object(data_t data)
{
    m_data = data;
}

Object::Object(const Object& other)
{
    m_data = other.m_data;
}

Object::~Object()
{
}



}
 // namespace harfbuzz 
