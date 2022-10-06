#include <gui/containers/Menu_tree_title_container.hpp>

Menu_tree_title_container::Menu_tree_title_container()
{

}


void Menu_tree_title_container::Set_Title(TEXTS iconTextID)
{
	textArea1.setTypedText(TypedText(iconTextID));
	textArea1.resizeToCurrentText();
    invalidate();
}

void Menu_tree_title_container::initialize()
{
    Menu_tree_title_containerBase::initialize();
}
