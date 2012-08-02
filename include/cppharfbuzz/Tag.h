/*
 *  \file   Tag.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_TAG_H_
#define CPPHARFBUZZ_TAG_H_

#include <cppharfbuzz/common.h>

namespace harfbuzz
{

class Tag
{
    public:
        typedef uint32_t    data_t;
        static const data_t NONE = 0;

    private:
        data_t    m_data;
        Tag();

    public:
        template < typename T1, typename T2, typename T3, typename T4 >
        Tag( const T1& a, const T2& b, const T3& c, const T4& d )
        {
            m_data = (data_t)(
                            ( ((uint8_t)(a) )   << 24   )
                        |   ( ((uint8_t)(b))    << 16   )
                        |   ( ((uint8_t)(c))    << 8    )
                        |   ( ((uint8_t)(d))    << 0    )
                        );
        }

        Tag( const data_t& data );

        data_t get_data() const;

        static Tag none();

        static Tag from_string( const char* str, int len=-1);
};


template < uint8_t a, uint8_t b, uint8_t c, uint8_t d >
struct CTimeTag
{
    static const Tag::data_t value
        = (Tag::data_t)(
                    ( a << 24   )
                |   ( b << 16   )
                |   ( c << 8    )
                |   ( d << 0    )
                );
};



} // namespace harfbuzz 

#endif // TAG_H_
