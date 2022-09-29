#include <gui/containers/Menu_buttons_container.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>


TGFX_Menu_t sub_menu_9_1 = { "9.1. Nastawy podstawowe", T_DEFAULT_SETTINGS , &sub_menu_9_2, NULL, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_2 = { "9.2. Serwis"            , T_SERVICE          ,NULL          , &sub_menu_9_1, NULL, NULL, NULL};



Menu_buttons_container::Menu_buttons_container()
{

}

void Menu_buttons_container::SetListElemnts(int item)
{

	image1.invalidate();
	textarea.invalidate();

	switch (item) {
		case 0:
			image1.setBitmap(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID));
			textarea.setTypedText(TypedText(T_DEFAULT_SETTINGS));
			textarea.resizeToCurrentText();
			break;

		case 1:
			image1.setBitmap(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID));
			textarea.setTypedText(TypedText(T_SERVICE));
			textarea.resizeToCurrentText();
			break;
		case 2:
			image1.setBitmap(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID));
			textarea.setTypedText(TypedText(T_DIAGNSTIC));
			textarea.resizeToCurrentText();
			break;
		default:
			break;
	}


}

void Menu_buttons_container::initialize()
{
    Menu_buttons_containerBase::initialize();
}
