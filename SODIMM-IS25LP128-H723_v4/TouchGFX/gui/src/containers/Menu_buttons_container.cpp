#include <gui/containers/Menu_buttons_container.hpp>

Menu_buttons_container::Menu_buttons_container()
{

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
