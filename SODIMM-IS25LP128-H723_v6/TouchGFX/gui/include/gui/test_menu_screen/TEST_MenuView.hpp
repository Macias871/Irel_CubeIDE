#ifndef TEST_MENUVIEW_HPP
#define TEST_MENUVIEW_HPP

#include <gui_generated/test_menu_screen/TEST_MenuViewBase.hpp>
#include <gui/test_menu_screen/TEST_MenuPresenter.hpp>
#include <gui/menu_9_screen/Menu_9Presenter.hpp>
#include <gui/containers/Menu_buttons_container.hpp>
#include <touchgfx/Utils.hpp>
#include "../Structures.h"

class TEST_MenuView : public TEST_MenuViewBase
{
public:
    TEST_MenuView();
    virtual ~TEST_MenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    TGFX_Menu_t TGFX_menu_elemnt;
    void BackClicked(Back_menu_container& element);


    /*
     * Virtual Action Handlers
     */

    /*
     * Virtual Action Handlers
     */
    virtual void btn_spr_clicked();

    virtual void btn_pdz_clicked();

    virtual void btn_pco_clicked();

    virtual void btn_pcwu_clicked();

    virtual void btn_3d_clicked();

    virtual void btn_gr1_clicked();

    virtual void btn_gr2_clicked();

    virtual void btn_zz_clicked();

protected:

    Callback<TEST_MenuView, Back_menu_container&> BackClickedCallback;

};

#endif // TEST_MENUVIEW_HPP
