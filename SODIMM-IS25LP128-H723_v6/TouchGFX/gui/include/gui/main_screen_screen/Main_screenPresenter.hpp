#ifndef MAIN_SCREENPRESENTER_HPP
#define MAIN_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Main_screenView;

class Main_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Main_screenPresenter(Main_screenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Main_screenPresenter() {};

private:
    Main_screenPresenter();

    Main_screenView& view;
};

#endif // MAIN_SCREENPRESENTER_HPP
