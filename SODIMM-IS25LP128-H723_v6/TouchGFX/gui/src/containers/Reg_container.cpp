#include <gui/containers/Reg_container.hpp>

Reg_container::Reg_container()
{

}

void Reg_container::Coarse_dn()
{
	if(value == Min_value)
	{
		value = Max_value;
	}
	else
	{
		if(value > Min_value)
		{
			value = value - step_coarse_value;
		}
	}


	if(value < Min_value){value = Min_value;}



	Refresh_value(value);
}

void Reg_container::Coarse_up()
{
	if(value == Max_value)
	{
		value = Min_value;
	}
	else
	{
		if(value < Max_value)
		{
			value = value + step_coarse_value;
		}
	}

	if(value > Max_value){value = Max_value;}

	Refresh_value(value);
}

void Reg_container::Fine_dn()
{

	if(value == Min_value)
	{
		value = Max_value;
	}
	else
	{
		if(value > Min_value)
		{
			value = value - step_fine_value;
		}
	}

	if(value < Min_value){value = Min_value;}

	Refresh_value(value);





}

void Reg_container::Fine_up()
{

	if(value == Max_value)
	{
		value = Min_value;
	}
	else
	{
		if(value < Max_value)
		{
			value = value + step_fine_value;
		}
	}

	if(value > Max_value){value = Max_value;}

	Refresh_value(value);



}

void Reg_container::Refresh_value(int32_t value)
{
	Unicode::snprintf(Value_tBuffer, 8, "%d", value);
	//Unicode::snprintf(Value_tBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_WC1).getText());
	//touchgfx_printf("name: %s\n", Value_tBuffer);
	//Value_t.setTypedText(touchgfx::TypedText(T_WC1));
	//Value_t.setWildcard(Value_tBuffer);
	Value_t.resizeToCurrentText();
	Value_t.center();
	//Value_t.invalidate();
	invalidate();
}

void Reg_container::initialize()
{
	//touchgfx_printf("name: %d\n", value);

    Reg_containerBase::initialize();

	Unicode::snprintf(Value_tBuffer, 8, "%d", value);
	//touchgfx_printf("name: %s\n", Value_tBuffer);

	//Unicode::snprintf(Value_tBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_WC1).getText());



	Value_t.setTypedText(touchgfx::TypedText(T_WC1));
	Value_t.setWildcard(Value_tBuffer);

	//Max_value = 60;
	//Min_value = 0;
	//step_fine_value = 1;


	Value_t.resizeToCurrentText();
	Value_t.center();
	Value_t.invalidate();

	//invalidate();

}
