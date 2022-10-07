#include <gui/containers/Back_menu_container.hpp>

Back_menu_container::Back_menu_container():
BackCallback(0)
{

}


void Back_menu_container::Back_clicked()
{
	//touchgfx_printf("Back clicked  %s\n", TGFX_back_elemnt.name);

    if (BackCallback->isValid())
    {

    	//touchgfx_printf("Back valid", TGFX_back_elemnt.name);
    	BackCallback->execute(*this);
    }
}

void Back_menu_container::setBack(TGFX_Menu_t Menu_parent,GenericCallback< Back_menu_container& >& callback)
{

	//touchgfx_printf("set callback %s\n", callback);

	TGFX_back_elemnt = Menu_parent;

	//touchgfx_printf("set back %s\n", TGFX_back_elemnt.name);


	BackCallback = &callback;
}


void Back_menu_container::initialize()
{
    Back_menu_containerBase::initialize();
}
