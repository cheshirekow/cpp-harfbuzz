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
 *  \file   Script.h
 *
 *  \date   Jul 19, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPHARFBUZZ_SCRIPT_H_
#define CPPHARFBUZZ_SCRIPT_H_

#include <cppharfbuzz/common.h>
#include <cppharfbuzz/Tag.h>
#include <cppharfbuzz/Direction.h>

namespace harfbuzz
{

class Script
{
    private:
        uint32_t m_value;

    public:
        /// create a new script object which is just an unsigned 32 bit
        /// number with some methods attached
        Script(uint32_t value);

        /// return the stored integer value
        uint32_t value();

        /// return a script object with the same value as the given tag
        /// (note, this does not validate the tag)
        static Script from_iso15924_tag( const Tag& tag );

        /// sugar for Tag::from_string() and then Script::from_iso15924_tag()
        /**
         *  @note \p len =-1 means \p str is NULL terminated
         */
        static Script from_string( const char *str, int len=-1);

        /// returns a Tag with the same value
        Tag         to_iso15924_tag();

        /// get the horizontal direction of this language/script
        Direction   get_horizontal_direction();
};



namespace script
{

// Unicode-1.1 additions
const Script COMMON              = CTimeTag<'Z','y','y','y'>::value;
const Script ARABIC              = CTimeTag<'A','r','a','b'>::value;
const Script ARMENIAN            = CTimeTag<'A','r','m','n'>::value;
const Script BENGALI             = CTimeTag<'B','e','n','g'>::value;
const Script BOPOMOFO            = CTimeTag<'B','o','p','o'>::value;
const Script CANADIAN_ABORIGINAL = CTimeTag<'C','a','n','s'>::value;
const Script CHEROKEE            = CTimeTag<'C','h','e','r'>::value;
const Script COPTIC              = CTimeTag<'C','o','p','t'>::value;
const Script CYRILLIC            = CTimeTag<'C','y','r','l'>::value;
const Script DEVANAGARI          = CTimeTag<'D','e','v','a'>::value;
const Script GEORGIAN            = CTimeTag<'G','e','o','r'>::value;
const Script GREEK               = CTimeTag<'G','r','e','k'>::value;
const Script GUJARATI            = CTimeTag<'G','u','j','r'>::value;
const Script GURMUKHI            = CTimeTag<'G','u','r','u'>::value;
const Script HANGUL              = CTimeTag<'H','a','n','g'>::value;
const Script HAN                 = CTimeTag<'H','a','n','i'>::value;
const Script HEBREW              = CTimeTag<'H','e','b','r'>::value;
const Script HIRAGANA            = CTimeTag<'H','i','r','a'>::value;
const Script INHERITED           = CTimeTag<'Z','i','n','h'>::value;
const Script KANNADA             = CTimeTag<'K','n','d','a'>::value;
const Script KATAKANA            = CTimeTag<'K','a','n','a'>::value;
const Script LAO                 = CTimeTag<'L','a','o','o'>::value;
const Script LATIN               = CTimeTag<'L','a','t','n'>::value;
const Script MALAYALAM           = CTimeTag<'M','l','y','m'>::value;
const Script MONGOLIAN           = CTimeTag<'M','o','n','g'>::value;
const Script OGHAM               = CTimeTag<'O','g','a','m'>::value;
const Script ORIYA               = CTimeTag<'O','r','y','a'>::value;
const Script RUNIC               = CTimeTag<'R','u','n','r'>::value;
const Script SYRIAC              = CTimeTag<'S','y','r','c'>::value;
const Script TAMIL               = CTimeTag<'T','a','m','l'>::value;
const Script TELUGU              = CTimeTag<'T','e','l','u'>::value;
const Script THAI                = CTimeTag<'T','h','a','i'>::value;
const Script YI                  = CTimeTag<'Y','i','i','i'>::value;

// Unicode-2.0 additions
const Script TIBETAN         = CTimeTag<'T','i','b','t'>::value;


// Unicode-3.0 additions
const Script ETHIOPIC        = CTimeTag<'E','t','h','i'>::value;
const Script KHMER           = CTimeTag<'K','h','m','r'>::value;
const Script MYANMAR         = CTimeTag<'M','y','m','r'>::value;
const Script SINHALA         = CTimeTag<'S','i','n','h'>::value;
const Script THAANA          = CTimeTag<'T','h','a','a'>::value;


// Unicode-3.1 additions
const Script DESERET         = CTimeTag<'D','s','r','t'>::value;
const Script GOTHIC          = CTimeTag<'G','o','t','h'>::value;
const Script OLD_ITALIC      = CTimeTag<'I','t','a','l'>::value;


// Unicode-3.2 additions
const Script BUHID           = CTimeTag<'B','u','h','d'>::value;
const Script HANUNOO         = CTimeTag<'H','a','n','o'>::value;
const Script TAGALOG         = CTimeTag<'T','g','l','g'>::value;
const Script TAGBANWA        = CTimeTag<'T','a','g','b'>::value;


// Unicode-4.0 additions
const Script BRAILLE         = CTimeTag<'B','r','a','i'>::value;
const Script CYPRIOT         = CTimeTag<'C','p','r','t'>::value;
const Script LIMBU           = CTimeTag<'L','i','m','b'>::value;
const Script LINEAR_B        = CTimeTag<'L','i','n','b'>::value;
const Script OSMANYA         = CTimeTag<'O','s','m','a'>::value;
const Script SHAVIAN         = CTimeTag<'S','h','a','w'>::value;
const Script TAI_LE          = CTimeTag<'T','a','l','e'>::value;
const Script UGARITIC        = CTimeTag<'U','g','a','r'>::value;


// Unicode-4.1 additions
const Script BUGINESE        = CTimeTag<'B','u','g','i'>::value;
const Script GLAGOLITIC      = CTimeTag<'G','l','a','g'>::value;
const Script KHAROSHTHI      = CTimeTag<'K','h','a','r'>::value;
const Script NEW_TAI_LUE     = CTimeTag<'T','a','l','u'>::value;
const Script OLD_PERSIAN     = CTimeTag<'X','p','e','o'>::value;
const Script SYLOTI_NAGRI    = CTimeTag<'S','y','l','o'>::value;
const Script TIFINAGH        = CTimeTag<'T','f','n','g'>::value;


// Unicode-5.0 additions
const Script BALINESE        = CTimeTag<'B','a','l','i'>::value;
const Script CUNEIFORM       = CTimeTag<'X','s','u','x'>::value;
const Script NKO             = CTimeTag<'N','k','o','o'>::value;
const Script PHAGS_PA        = CTimeTag<'P','h','a','g'>::value;
const Script PHOENICIAN      = CTimeTag<'P','h','n','x'>::value;
const Script UNKNOWN         = CTimeTag<'Z','z','z','z'>::value;

// Unicode-5.1 additions
const Script CARIAN          = CTimeTag<'C','a','r','i'>::value;
const Script CHAM            = CTimeTag<'C','h','a','m'>::value;
const Script KAYAH_LI        = CTimeTag<'K','a','l','i'>::value;
const Script LEPCHA          = CTimeTag<'L','e','p','c'>::value;
const Script LYCIAN          = CTimeTag<'L','y','c','i'>::value;
const Script LYDIAN          = CTimeTag<'L','y','d','i'>::value;
const Script OL_CHIKI        = CTimeTag<'O','l','c','k'>::value;
const Script REJANG          = CTimeTag<'R','j','n','g'>::value;
const Script SAURASHTRA      = CTimeTag<'S','a','u','r'>::value;
const Script SUNDANESE       = CTimeTag<'S','u','n','d'>::value;
const Script VAI             = CTimeTag<'V','a','i','i'>::value;

// Unicode-5.2 additions
const Script AVESTAN                 = CTimeTag<'A','v','s','t'>::value;
const Script BAMUM                   = CTimeTag<'B','a','m','u'>::value;
const Script EGYPTIAN_HIEROGLYPHS    = CTimeTag<'E','g','y','p'>::value;
const Script IMPERIAL_ARAMAIC        = CTimeTag<'A','r','m','i'>::value;
const Script INSCRIPTIONAL_PAHLAVI   = CTimeTag<'P','h','l','i'>::value;
const Script INSCRIPTIONAL_PARTHIAN  = CTimeTag<'P','r','t','i'>::value;
const Script JAVANESE                = CTimeTag<'J','a','v','a'>::value;
const Script KAITHI                  = CTimeTag<'K','t','h','i'>::value;
const Script LISU                    = CTimeTag<'L','i','s','u'>::value;
const Script MEETEI_MAYEK            = CTimeTag<'M','t','e','i'>::value;
const Script OLD_SOUTH_ARABIAN       = CTimeTag<'S','a','r','b'>::value;
const Script OLD_TURKIC              = CTimeTag<'O','r','k','h'>::value;
const Script SAMARITAN               = CTimeTag<'S','a','m','r'>::value;
const Script TAI_THAM                = CTimeTag<'L','a','n','a'>::value;
const Script TAI_VIET                = CTimeTag<'T','a','v','t'>::value;

// Unicode-6.0 additions
const Script BATAK                   = CTimeTag<'B','a','t','k'>::value;
const Script BRAHMI                  = CTimeTag<'B','r','a','h'>::value;
const Script MANDAIC                 = CTimeTag<'M','a','n','d'>::value;

// Unicode-6.1 additions
const Script CHAKMA                  = CTimeTag<'C','a','k','m'>::value;
const Script MEROITIC_CURSIVE        = CTimeTag<'M','e','r','c'>::value;
const Script MEROITIC_HIEROGLYPHS    = CTimeTag<'M','e','r','o'>::value;
const Script MIAO                    = CTimeTag<'P','l','r','d'>::value;
const Script SHARADA                 = CTimeTag<'S','h','r','d'>::value;
const Script SORA_SOMPENG            = CTimeTag<'S','o','r','a'>::value;
const Script TAKRI                   = CTimeTag<'T','a','k','r'>::value;

// No script set
const Script INVALID                 = Tag::NONE;



}



} // namespace harfbuzz 

#endif // SCRIPT_H_
