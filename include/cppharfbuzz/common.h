/*
 * common.h
 *
 *  Created on: Jul 18, 2012
 *      Author: josh
 */

#ifndef HARFBUZZMM_COMMON_H_
#define HARFBUZZMM_COMMON_H_

#if !defined (HB_DONT_DEFINE_STDINT)

#if defined (_SVR4) || defined (SVR4) || defined (__OpenBSD__) || \
    defined (_sgi) || defined (__sun) || defined (sun) || \
    defined (__digital__) || defined (__HP_cc)
#  include <inttypes.h>
#elif defined (_AIX)
#  include <sys/inttypes.h>
/* VS 2010 (_MSC_VER 1600) has stdint.h */
#elif defined (_MSC_VER) && _MSC_VER < 1600
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#  include <stdint.h>
#endif

#endif





namespace harfbuzz
{


typedef uint32_t    codepoint_t;
typedef int32_t     position_t;
typedef uint32_t    mask_t;

/// opaque data structure used to uniquely identify user data
struct user_data_key_t;

/// function to destroy "user data" within a blob
typedef void (*destroy_func_t)(void *);

namespace unicode_general_category
{

enum Category
{
    CONTROL,              /* Cc */
    FORMAT,               /* Cf */
    UNASSIGNED,           /* Cn */
    PRIVATE_USE,          /* Co */
    SURROGATE,            /* Cs */
    LOWERCASE_LETTER,     /* Ll */
    MODIFIER_LETTER,      /* Lm */
    OTHER_LETTER,         /* Lo */
    TITLECASE_LETTER,     /* Lt */
    UPPERCASE_LETTER,     /* Lu */
    SPACING_MARK,         /* Mc */
    ENCLOSING_MARK,       /* Me */
    NON_SPACING_MARK,     /* Mn */
    DECIMAL_NUMBER,       /* Nd */
    LETTER_NUMBER,        /* Nl */
    OTHER_NUMBER,         /* No */
    CONNECT_PUNCTUATION,  /* Pc */
    DASH_PUNCTUATION,     /* Pd */
    CLOSE_PUNCTUATION,    /* Pe */
    FINAL_PUNCTUATION,    /* Pf */
    INITIAL_PUNCTUATION,  /* Pi */
    OTHER_PUNCTUATION,    /* Po */
    OPEN_PUNCTUATION,     /* Ps */
    CURRENCY_SYMBOL,      /* Sc */
    MODIFIER_SYMBOL,      /* Sk */
    MATH_SYMBOL,          /* Sm */
    OTHER_SYMBOL,         /* So */
    LINE_SEPARATOR,       /* Zl */
    PARAGRAPH_SEPARATOR,  /* Zp */
    SPACE_SEPARATOR       /* Zs */
};


}





}












#endif // COMMON_H_
