/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x53, 0x69, 0x6c, 0x6e, 0x69, 0x6b, 0x20, 0x53, 0x70, 0x72, 0x119, 0x17c, 0x61, 0x72, 0x6b, 0x69, 0x0, // @0 "Silnik Spr??arki"
    0x50, 0x57, 0x4d, 0x31, 0x3a, 0x20, 0x2, 0x0, // @17 "PWM1: <>"
    0x50, 0x57, 0x4d, 0x32, 0x3a, 0x20, 0x2, 0x0, // @25 "PWM2: <>"
    0x57, 0x65, 0x2e, 0x20, 0x64, 0x6f, 0x64, 0x61, 0x74, 0x6b, 0x6f, 0x77, 0x65, 0x0, // @33 "We. dodatkowe"
    0x50, 0x72, 0x65, 0x73, 0x6f, 0x73, 0x74, 0x61, 0x74, 0x20, 0x4e, 0x43, 0x0, // @47 "Presostat NC"
    0x50, 0x72, 0x65, 0x73, 0x6f, 0x73, 0x74, 0x61, 0x74, 0x20, 0x4f, 0x50, 0x0, // @60 "Presostat OP"
    0x50, 0x72, 0x65, 0x73, 0x6f, 0x73, 0x74, 0x61, 0x74, 0x20, 0x57, 0x43, 0x0, // @73 "Presostat WC"
    0x54, 0x31, 0x3a, 0x20, 0x2, 0x0, // @86 "T1: <>"
    0x54, 0x32, 0x3a, 0x20, 0x2, 0x0, // @92 "T2: <>"
    0x54, 0x33, 0x3a, 0x20, 0x2, 0x0, // @98 "T3: <>"
    0x54, 0x34, 0x3a, 0x20, 0x2, 0x0, // @104 "T4: <>"
    0x54, 0x35, 0x3a, 0x20, 0x2, 0x0, // @110 "T5: <>"
    0x54, 0x36, 0x3a, 0x20, 0x2, 0x0, // @116 "T6: <>"
    0x54, 0x37, 0x3a, 0x20, 0x2, 0x0, // @122 "T7: <>"
    0x54, 0x5a, 0x3a, 0x20, 0x2, 0x0, // @128 "TZ: <>"
    0x57, 0x79, 0x142, 0x2e, 0x20, 0x50, 0x72, 0x7a, 0x65, 0x70, 0x2e, 0x0, // @134 "Wy?. Przep."
    0x47, 0x72, 0x7a, 0x61, 0x142, 0x6b, 0x61, 0x20, 0x31, 0x0, // @146 "Grza?ka 1"
    0x47, 0x72, 0x7a, 0x61, 0x142, 0x6b, 0x61, 0x20, 0x32, 0x0, // @156 "Grza?ka 2"
    0x50, 0x6f, 0x6d, 0x70, 0x61, 0x20, 0x43, 0x57, 0x55, 0x0, // @166 "Pompa CWU"
    0x53, 0x70, 0x72, 0x119, 0x17c, 0x61, 0x72, 0x6b, 0x61, 0x0, // @176 "Spr??arka"
    0x5a, 0x61, 0x73, 0x69, 0x6c, 0x61, 0x6e, 0x69, 0x65, 0x0, // @186 "Zasilanie"
    0x5a, 0x65, 0x77, 0x2e, 0x20, 0x7a, 0x72, 0x64, 0x2e, 0x0, // @196 "Zew. zrd."
    0x50, 0x6f, 0x6d, 0x70, 0x61, 0x20, 0x43, 0x4f, 0x0, // @206 "Pompa CO"
    0x50, 0x6f, 0x6d, 0x70, 0x61, 0x20, 0x44, 0x179, 0x0, // @215 "Pompa D?"
    0x5a, 0x61, 0x77, 0x6f, 0x72, 0x20, 0x33, 0x44, 0x0 // @224 "Zawor 3D"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern uint32_t const indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}