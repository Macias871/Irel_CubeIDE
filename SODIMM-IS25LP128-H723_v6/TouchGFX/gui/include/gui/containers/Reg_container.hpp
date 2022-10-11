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

    uint16_t value;
    /*
     * Virtual Action Handlers
     */
    virtual void Fine_up();
    virtual void Fine_dn();
    virtual void Coarse_up();
    virtual void Coarse_dn();

    virtual void initialize();
protected:

    uint16_t step_fine_value;
    uint16_t step_coarse_value;
    uint16_t Min_value;
    uint16_t Max_value;

    static const uint16_t TEXTAREA_SIZE = 20;
    touchgfx::Unicode::UnicodeChar Value_tBuffer[TEXTAREA_SIZE];


};

#endif // REG_CONTAINER_HPP
