#include <gui/menu_9_screen/Menu_9View.hpp>

#include <BitmapDatabase.hpp>

Menu_9View::Menu_9View()
{

}

void Menu_9View::setupScreen()
{
    Menu_9ViewBase::setupScreen();
}

void Menu_9View::tearDownScreen()
{
    Menu_9ViewBase::tearDownScreen();
}



void Menu_9View::scrollListUpdateItem(Menu_buttons_container& item, int16_t itemIndex)
{


	item.SetListElemnts(itemIndex);

}
