/*
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

class Tag;

class Script
{
    public:

        /// Enumerates all the languages (actually, I guess "scripts")
        /// that Unicode understands
        enum EData
        {
            // Unicode-1.1 additions
            COMMON              = CTimeTag<'Z','y','y','y'>::value,
            ARABIC              = CTimeTag<'A','r','a','b'>::value,
            ARMENIAN            = CTimeTag<'A','r','m','n'>::value,
            BENGALI             = CTimeTag<'B','e','n','g'>::value,
            BOPOMOFO            = CTimeTag<'B','o','p','o'>::value,
            CANADIAN_ABORIGINAL = CTimeTag<'C','a','n','s'>::value,
            CHEROKEE            = CTimeTag<'C','h','e','r'>::value,
            COPTIC              = CTimeTag<'C','o','p','t'>::value,
            CYRILLIC            = CTimeTag<'C','y','r','l'>::value,
            DEVANAGARI          = CTimeTag<'D','e','v','a'>::value,
            GEORGIAN            = CTimeTag<'G','e','o','r'>::value,
            GREEK               = CTimeTag<'G','r','e','k'>::value,
            GUJARATI            = CTimeTag<'G','u','j','r'>::value,
            GURMUKHI            = CTimeTag<'G','u','r','u'>::value,
            HANGUL              = CTimeTag<'H','a','n','g'>::value,
            HAN                 = CTimeTag<'H','a','n','i'>::value,
            HEBREW              = CTimeTag<'H','e','b','r'>::value,
            HIRAGANA            = CTimeTag<'H','i','r','a'>::value,
            INHERITED           = CTimeTag<'Z','i','n','h'>::value,
            KANNADA             = CTimeTag<'K','n','d','a'>::value,
            KATAKANA            = CTimeTag<'K','a','n','a'>::value,
            LAO                 = CTimeTag<'L','a','o','o'>::value,
            LATIN               = CTimeTag<'L','a','t','n'>::value,
            MALAYALAM           = CTimeTag<'M','l','y','m'>::value,
            MONGOLIAN           = CTimeTag<'M','o','n','g'>::value,
            OGHAM               = CTimeTag<'O','g','a','m'>::value,
            ORIYA               = CTimeTag<'O','r','y','a'>::value,
            RUNIC               = CTimeTag<'R','u','n','r'>::value,
            SYRIAC              = CTimeTag<'S','y','r','c'>::value,
            TAMIL               = CTimeTag<'T','a','m','l'>::value,
            TELUGU              = CTimeTag<'T','e','l','u'>::value,
            THAI                = CTimeTag<'T','h','a','i'>::value,
            YI                  = CTimeTag<'Y','i','i','i'>::value,

            // Unicode-2.0 additions
            TIBETAN         = CTimeTag<'T','i','b','t'>::value,

            // Unicode-3.0 additions
            ETHIOPIC        = CTimeTag<'E','t','h','i'>::value,
            KHMER           = CTimeTag<'K','h','m','r'>::value,
            MYANMAR         = CTimeTag<'M','y','m','r'>::value,
            SINHALA         = CTimeTag<'S','i','n','h'>::value,
            THAANA          = CTimeTag<'T','h','a','a'>::value,

            // Unicode-3.1 additions
            DESERET         = CTimeTag<'D','s','r','t'>::value,
            GOTHIC          = CTimeTag<'G','o','t','h'>::value,
            OLD_ITALIC      = CTimeTag<'I','t','a','l'>::value,

            // Unicode-3.2 additions
            BUHID           = CTimeTag<'B','u','h','d'>::value,
            HANUNOO         = CTimeTag<'H','a','n','o'>::value,
            TAGALOG         = CTimeTag<'T','g','l','g'>::value,
            TAGBANWA        = CTimeTag<'T','a','g','b'>::value,

            // Unicode-4.0 additions
            BRAILLE         = CTimeTag<'B','r','a','i'>::value,
            CYPRIOT         = CTimeTag<'C','p','r','t'>::value,
            LIMBU           = CTimeTag<'L','i','m','b'>::value,
            LINEAR_B        = CTimeTag<'L','i','n','b'>::value,
            OSMANYA         = CTimeTag<'O','s','m','a'>::value,
            SHAVIAN         = CTimeTag<'S','h','a','w'>::value,
            TAI_LE          = CTimeTag<'T','a','l','e'>::value,
            UGARITIC        = CTimeTag<'U','g','a','r'>::value,

            // Unicode-4.1 additions
            BUGINESE        = CTimeTag<'B','u','g','i'>::value,
            GLAGOLITIC      = CTimeTag<'G','l','a','g'>::value,
            KHAROSHTHI      = CTimeTag<'K','h','a','r'>::value,
            NEW_TAI_LUE     = CTimeTag<'T','a','l','u'>::value,
            OLD_PERSIAN     = CTimeTag<'X','p','e','o'>::value,
            SYLOTI_NAGRI    = CTimeTag<'S','y','l','o'>::value,
            TIFINAGH        = CTimeTag<'T','f','n','g'>::value,

            // Unicode-5.0 additions
            BALINESE        = CTimeTag<'B','a','l','i'>::value,
            CUNEIFORM       = CTimeTag<'X','s','u','x'>::value,
            NKO             = CTimeTag<'N','k','o','o'>::value,
            PHAGS_PA        = CTimeTag<'P','h','a','g'>::value,
            PHOENICIAN      = CTimeTag<'P','h','n','x'>::value,
            UNKNOWN         = CTimeTag<'Z','z','z','z'>::value,

            // Unicode-5.1 additions
            CARIAN          = CTimeTag<'C','a','r','i'>::value,
            CHAM            = CTimeTag<'C','h','a','m'>::value,
            KAYAH_LI        = CTimeTag<'K','a','l','i'>::value,
            LEPCHA          = CTimeTag<'L','e','p','c'>::value,
            LYCIAN          = CTimeTag<'L','y','c','i'>::value,
            LYDIAN          = CTimeTag<'L','y','d','i'>::value,
            OL_CHIKI        = CTimeTag<'O','l','c','k'>::value,
            REJANG          = CTimeTag<'R','j','n','g'>::value,
            SAURASHTRA      = CTimeTag<'S','a','u','r'>::value,
            SUNDANESE       = CTimeTag<'S','u','n','d'>::value,
            VAI             = CTimeTag<'V','a','i','i'>::value,

            // Unicode-5.2 additions
            AVESTAN                 = CTimeTag<'A','v','s','t'>::value,
            BAMUM                   = CTimeTag<'B','a','m','u'>::value,
            EGYPTIAN_HIEROGLYPHS    = CTimeTag<'E','g','y','p'>::value,
            IMPERIAL_ARAMAIC        = CTimeTag<'A','r','m','i'>::value,
            INSCRIPTIONAL_PAHLAVI   = CTimeTag<'P','h','l','i'>::value,
            INSCRIPTIONAL_PARTHIAN  = CTimeTag<'P','r','t','i'>::value,
            JAVANESE                = CTimeTag<'J','a','v','a'>::value,
            KAITHI                  = CTimeTag<'K','t','h','i'>::value,
            LISU                    = CTimeTag<'L','i','s','u'>::value,
            MEETEI_MAYEK            = CTimeTag<'M','t','e','i'>::value,
            OLD_SOUTH_ARABIAN       = CTimeTag<'S','a','r','b'>::value,
            OLD_TURKIC              = CTimeTag<'O','r','k','h'>::value,
            SAMARITAN               = CTimeTag<'S','a','m','r'>::value,
            TAI_THAM                = CTimeTag<'L','a','n','a'>::value,
            TAI_VIET                = CTimeTag<'T','a','v','t'>::value,

            // Unicode-6.0 additions
            BATAK                   = CTimeTag<'B','a','t','k'>::value,
            BRAHMI                  = CTimeTag<'B','r','a','h'>::value,
            MANDAIC                 = CTimeTag<'M','a','n','d'>::value,

            // Unicode-6.1 additions
            CHAKMA                  = CTimeTag<'C','a','k','m'>::value,
            MEROITIC_CURSIVE        = CTimeTag<'M','e','r','c'>::value,
            MEROITIC_HIEROGLYPHS    = CTimeTag<'M','e','r','o'>::value,
            MIAO                    = CTimeTag<'P','l','r','d'>::value,
            SHARADA                 = CTimeTag<'S','h','r','d'>::value,
            SORA_SOMPENG            = CTimeTag<'S','o','r','a'>::value,
            TAKRI                   = CTimeTag<'T','a','k','r'>::value,

            // No script set
            INVALID                 = Tag::NONE
        };

        typedef EData data_t;

    private:
        data_t m_data;

        Script();
        Script(const data_t& data);

    public:
        Script from_iso15924_tag( const Tag& tag );

        /// sugar for Tag::from_string() and then Script::from_iso15924_tag()
        /**
         *  @note \p len =-1 means \p str is NULL terminated
         */
        Script from_string( const char *str, int len=-1);

        Tag to_iso15924_tag();
        Direction   get_horizontal_direction();
};

} // namespace harfbuzz 

#endif // SCRIPT_H_
