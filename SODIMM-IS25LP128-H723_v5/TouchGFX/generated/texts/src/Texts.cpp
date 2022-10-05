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
    0x39, 0x2e, 0x31, 0x2e, 0x32, 0x2e, 0x20, 0x5a, 0x61, 0x142, 0x105, 0x63, 0x7a, 0x65, 0x6e, 0x69, 0x65, 0x20, 0x6f, 0x67, 0x72, 0x7a, 0x65, 0x77, 0x61, 0x6e, 0x69, 0x61, 0x0, // @0 "9.1.2. Za??czenie ogrzewania"
    0x39, 0x2e, 0x31, 0x2e, 0x34, 0x2e, 0x20, 0x55, 0x73, 0x74, 0x61, 0x77, 0x69, 0x65, 0x6e, 0x69, 0x61, 0x20, 0x72, 0x6f, 0x7a, 0x73, 0x7a, 0x65, 0x72, 0x7a, 0x65, 0x144, 0x0, // @29 "9.1.4. Ustawienia rozszerze?"
    0x39, 0x2e, 0x31, 0x2e, 0x33, 0x2e, 0x20, 0x55, 0x73, 0x74, 0x61, 0x77, 0x69, 0x6e, 0x69, 0x61, 0x20, 0x66, 0x61, 0x62, 0x72, 0x79, 0x63, 0x7a, 0x6e, 0x65, 0x0, // @58 "9.1.3. Ustawinia fabryczne"
    0x39, 0x2e, 0x34, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x65, 0x72, 0x61, 0x74, 0x75, 0x72, 0x61, 0x20, 0x7a, 0x65, 0x77, 0x6e, 0x119, 0x74, 0x72, 0x7a, 0x6e, 0x61, 0x0, // @85 "9.4 Temperatura zewn?trzna"
    0x39, 0x2e, 0x31, 0x2e, 0x20, 0x4e, 0x61, 0x73, 0x74, 0x61, 0x77, 0x79, 0x20, 0x70, 0x6f, 0x64, 0x73, 0x74, 0x61, 0x77, 0x6f, 0x77, 0x65, 0x0, // @112 "9.1. Nastawy podstawowe"
    0x39, 0x2e, 0x34, 0x20, 0x4f, 0x75, 0x74, 0x73, 0x69, 0x64, 0x65, 0x20, 0x54, 0x65, 0x6d, 0x70, 0x65, 0x72, 0x61, 0x74, 0x75, 0x72, 0x65, 0x0, // @136 "9.4 Outside Temperature"
    0x39, 0x2e, 0x31, 0x20, 0x4e, 0x61, 0x73, 0x74, 0x61, 0x77, 0x79, 0x20, 0x70, 0x6f, 0x64, 0x73, 0x74, 0x61, 0x77, 0x6f, 0x77, 0x65, 0x0, // @160 "9.1 Nastawy podstawowe"
    0x39, 0x2e, 0x31, 0x2e, 0x20, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x20, 0x53, 0x65, 0x74, 0x74, 0x69, 0x6e, 0x67, 0x73, 0x0, // @183 "9.1. Default Settings"
    0x39, 0x2e, 0x31, 0x20, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x20, 0x53, 0x65, 0x74, 0x74, 0x69, 0x6e, 0x67, 0x73, 0x0, // @205 "9.1 Default Settings"
    0x39, 0x2e, 0x36, 0x20, 0x43, 0x68, 0x61, 0x6e, 0x67, 0x65, 0x20, 0x50, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x6d, 0x0, // @226 "9.6 Change Programm"
    0x39, 0x2e, 0x31, 0x2e, 0x32, 0x2e, 0x20, 0x53, 0x65, 0x74, 0x20, 0x48, 0x65, 0x61, 0x74, 0x69, 0x6e, 0x67, 0x0, // @246 "9.1.2. Set Heating"
    0x39, 0x2e, 0x31, 0x2e, 0x34, 0x2e, 0x20, 0x45, 0x78, 0x74, 0x2e, 0x20, 0x63, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x0, // @265 "9.1.4. Ext. config"
    0x39, 0x2e, 0x36, 0x20, 0x57, 0x79, 0x62, 0xf3, 0x72, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x75, 0x0, // @284 "9.6 Wyb?r programu"
    0x6e, 0x61, 0x70, 0x69, 0x73, 0x5f, 0x6e, 0x75, 0x6d, 0x65, 0x75, 0x5f, 0x6d, 0x65, 0x6e, 0x75, 0x0, // @303 "napis_numeu_menu"
    0x39, 0x2e, 0x31, 0x2e, 0x31, 0x2e, 0x20, 0x4c, 0x61, 0x6e, 0x67, 0x75, 0x61, 0x67, 0x65, 0x0, // @320 "9.1.1. Language"
    0x39, 0x2e, 0x31, 0x2e, 0x33, 0x2e, 0x20, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x73, 0x0, // @336 "9.1.3. Defaults"
    0x39, 0x2e, 0x33, 0x20, 0x44, 0x69, 0x61, 0x67, 0x6e, 0x6f, 0x73, 0x74, 0x79, 0x6b, 0x61, 0x0, // @352 "9.3 Diagnostyka"
    0x6d, 0x65, 0x6e, 0x75, 0x5f, 0x74, 0x72, 0x65, 0x65, 0x5f, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x0, // @368 "menu_tree_title"
    0x39, 0x2e, 0x33, 0x20, 0x44, 0x69, 0x61, 0x67, 0x6e, 0x6f, 0x73, 0x74, 0x69, 0x63, 0x0, // @384 "9.3 Diagnostic"
    0x39, 0x2e, 0x35, 0x20, 0x43, 0x7a, 0x61, 0x73, 0x20, 0x70, 0x72, 0x61, 0x63, 0x79, 0x0, // @399 "9.5 Czas pracy"
    0x6e, 0x61, 0x70, 0x69, 0x73, 0x5f, 0x6b, 0x6c, 0x61, 0x77, 0x69, 0x73, 0x7a, 0x61, 0x0, // @414 "napis_klawisza"
    0x39, 0x2e, 0x35, 0x20, 0x57, 0x6f, 0x72, 0x6b, 0x20, 0x54, 0x69, 0x6d, 0x65, 0x0, // @429 "9.5 Work Time"
    0x39, 0x2e, 0x31, 0x2e, 0x31, 0x2e, 0x20, 0x4a, 0x119, 0x7a, 0x79, 0x6b, 0x0, // @443 "9.1.1. J?zyk"
    0x42, 0x75, 0x74, 0x74, 0x6f, 0x6e, 0x5f, 0x74, 0x69, 0x74, 0x6c, 0x65, 0x0, // @456 "Button_title"
    0x39, 0x2e, 0x32, 0x20, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x0, // @469 "9.2 Service"
    0x54, 0x72, 0x79, 0x62, 0x20, 0x70, 0x72, 0x61, 0x63, 0x79, 0x3a, 0x0, // @481 "Tryb pracy:"
    0x39, 0x2e, 0x32, 0x20, 0x53, 0x65, 0x72, 0x77, 0x69, 0x73, 0x0, // @493 "9.2 Serwis"
    0x57, 0x6f, 0x72, 0x6b, 0x20, 0x6d, 0x6f, 0x64, 0x65, 0x0, // @504 "Work mode"
    0x4d, 0x65, 0x6e, 0x75, 0x20, 0x39, 0x2e, 0x31, 0x0, // @514 "Menu 9.1"
    0x4e, 0x65, 0x77, 0x20, 0x54, 0x65, 0x78, 0x74, 0x0, // @523 "New Text"
    0x39, 0x2e, 0x20, 0x4d, 0x65, 0x6e, 0x75, 0x0, // @532 "9. Menu"
    0x57, 0x73, 0x74, 0x65, 0x63, 0x7a, 0x0, // @540 "Wstecz"
    0x42, 0x61, 0x63, 0x6b, 0x0, // @547 "Back"
    0x2, 0x0, // @552 "<>"
    0x32, 0x0 // @554 "2"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern uint32_t const indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern uint32_t const indicesPl[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[2] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb,
    indicesPl
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 2)
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
