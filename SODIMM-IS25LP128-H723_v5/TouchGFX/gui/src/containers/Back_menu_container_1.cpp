#include <gui/containers/Back_menu_container_1.hpp>

Back_menu_container_1::Back_menu_container_1():
BackCallback(0)
{

}


void Back_menu_container_1::Back_clicked()
{
    if (BackCallback->isValid())
    {

    	BackCallback->execute(*this);
    }
}

void Back_menu_container_1::setBack(TGFX_Menu_t Menu_parent,GenericCallback< Back_menu_container_1& >& callback)
{
//	touchgfx_printf("Received callback from: %s\n", element.TGFX_back_elemnt.parent->name);

	TGFX_back_elemnt = Menu_parent;
	BackCallback = &callback;
}


void Back_menu_container_1::initialize()
{
    Back_menu_container_1Base::initialize();
}
