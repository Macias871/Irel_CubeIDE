#include <gui/containers/Reg_container.hpp>

Reg_container::Reg_container()
{

}

void Reg_container::Coarse_dn()
{

}

void Reg_container::Coarse_up()
{

}

void Reg_container::Fine_dn()
{
	if(value > Min_value && value <= Max_value)
	{
		value--;
	}

	Unicode::snprintf(Value_tBuffer, 3, "%d", value);
	//Unicode::snprintf(Value_tBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_WC1).getText());
	touchgfx_printf("name: %s\n", Value_tBuffer);
	//Value_t.setTypedText(touchgfx::TypedText(T_WC1));
	//Value_t.setWildcard(Value_tBuffer);
	Value_t.resizeToCurrentText();
	Value_t.center();
	//Value_t.invalidate();
	invalidate();

}

void Reg_container::Fine_up()
{
	if(value >= Min_value && value < Max_value)
	{
		value++;
	}

	Unicode::snprintf(Value_tBuffer, 3, "%d", value);
	//Unicode::snprintf(Value_tBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_WC1).getText());
	touchgfx_printf("name: %s\n", Value_tBuffer);
	//Value_t.setTypedText(touchgfx::TypedText(T_WC1));
	//Value_t.setWildcard(Value_tBuffer);
	Value_t.resizeToCurrentText();
	Value_t.center();
	//Value_t.invalidate();
	invalidate();

}



void Reg_container::initialize()
{
    Reg_containerBase::initialize();

	Unicode::snprintf(Value_tBuffer, 3, "%d", 0);
	//touchgfx_printf("name: %s\n", Value_tBuffer);

	//Unicode::snprintf(Value_tBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_WC1).getText());
	Value_t.setTypedText(touchgfx::TypedText(T_WC1));
	Value_t.setWildcard(Value_tBuffer);

	Max_value = 60;
	Min_value = 0;
	step_fine_value = 1;


	Value_t.resizeToCurrentText();
	Value_t.center();
	Value_t.invalidate();

	//invalidate();

}
