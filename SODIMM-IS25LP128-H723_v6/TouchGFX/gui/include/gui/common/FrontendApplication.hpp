#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>



class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    // Menu_9
        void Test_menu_ScreenNoTransition();
        touchgfx::Callback<FrontendApplication> transitionCallback;
        void Test_menu_ScreenNoTransitionImpl();

        void Set_Date_ScreenNoTransition();
        void Set_Date_ScreenNoTransitionImpl();

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
private:


};

#endif // FRONTENDAPPLICATION_HPP
