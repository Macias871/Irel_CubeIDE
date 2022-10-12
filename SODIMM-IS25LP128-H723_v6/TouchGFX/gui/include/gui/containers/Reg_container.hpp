#ifndef REG_CONTAINER_HPP
#define REG_CONTAINER_HPP

#include <gui_generated/containers/Reg_containerBase.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Utils.hpp>

class Reg_container : public Reg_containerBase
{
public:
    Reg_container();
    virtual ~Reg_container() {}

    int32_t value;
    int32_t step_fine_value;
    int32_t step_coarse_value;
    int32_t Min_value;
    int32_t Max_value;

    /*
     * Virtual Action Handlers
     */
    virtual void Fine_up();
    virtual void Fine_dn();
    virtual void Coarse_up();
    virtual void Coarse_dn();

    virtual void Refresh_value(int32_t value);

    virtual void initialize();

private:


protected:



    static const uint16_t TEXTAREA_SIZE = 20;
    touchgfx::Unicode::UnicodeChar Value_tBuffer[TEXTAREA_SIZE];


};

#endif // REG_CONTAINER_HPP
