#include <gui/containers/Menu_buttons_container.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>


Menu_buttons_container::Menu_buttons_container():
viewCallback(0)
{

}


void Menu_buttons_container::setAction(GenericCallback< Menu_buttons_container& >& callback)
{
    viewCallback = &callback;
}

void Menu_buttons_container::clickAction()
{
    if (viewCallback->isValid())
    {

        viewCallback->execute(*this);
    }
}

void Menu_buttons_container::initialize()
{
    Menu_buttons_containerBase::initialize();
}


void Menu_buttons_container::setupListElement( TEXTS iconTextID, TGFX_Menu_t Menu)
{

	TGFX_menu_elemnt = Menu;
	//image1.setBitmap(iconBMP);
	textarea.setTypedText(TypedText(iconTextID));
	textarea.resizeToCurrentText();
    invalidate();
}
