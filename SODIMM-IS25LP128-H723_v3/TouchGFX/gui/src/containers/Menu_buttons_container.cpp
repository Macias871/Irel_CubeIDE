#include <gui/containers/Menu_buttons_container.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>



Menu_buttons_container::Menu_buttons_container()
{

}

void Menu_buttons_container::SetListElemnts(int item)
{

	//image1.invalidate();
	/*
	textarea.invalidate();

	switch (item) {
		case 0:

			image1.setBitmap(Bitmap(BITMAP_BUTTON_IN_MENU_OFF_ID));
			//textarea.setTypedText(TypedText(Menu.Ttext));
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

*/
}
/*
TGFX_Menu_t Get_TGFX_menu(int item)
{

	TGFX_Menu_t Temp_struct_menu;

	return Temp_struct_menu;

}
*/

void Menu_buttons_container::setupListElement(const Bitmap& iconBMP, TEXTS iconTextID, TGFX_Menu_t Menu)
{

	TGFX_menu_elemnt = Menu;
	//image1.setBitmap(iconBMP);
	textarea.setTypedText(TypedText(iconTextID));
	textarea.resizeToCurrentText();
    invalidate();
}

void Menu_buttons_container::initialize()
{
    Menu_buttons_containerBase::initialize();
}

void Menu_buttons_container::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Clicked_butt
        //When button1 clicked call virtual function
        //Call button_menu_clicked
        button_menu_clicked();
    }
}
