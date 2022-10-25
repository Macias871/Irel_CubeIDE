#include <gui/main_screen/MainView.hpp>
#include "../LIB/globals.h"
#include "../LIB/BUS.h"




MainView::MainView()
{
    counter = 0;
    flag = true;

}

uint8_t i_flag =0;

void MainView::handleTickEvent(){

	float ccc= -1.2f;
    counter++;    if(counter%60 == 0) // every 1s    ,
    {
    	//Unicode::snprintfFloat(textArea2Buffer, 5,"%2.1f",ccc);flag = false;
    	//textArea2.setWildcard(textArea2Buffer);
    	//textArea2.resizeToCurrentText();
    	//textArea2.invalidate();

    	i_flag = !i_flag;

    	if(flag == true){

        	Unicode::strncpy(textArea2Buffer,Temperatures.T1,5);
        	textArea2.setWildcard(textArea2Buffer);



        	Unicode::strncpy(textArea2_1Buffer, Temperatures.T2,5);
        	textArea2_1.setWildcard(textArea2_1Buffer);


        	Unicode::strncpy(textArea2_2Buffer, Temperatures.T3,5);
        	textArea2_2.setWildcard(textArea2_2Buffer);


        	Unicode::strncpy(textArea2_3Buffer, Temperatures.T4,5);
        	textArea2_3.setWildcard(textArea2_3Buffer);



        	Unicode::strncpy(textArea2_4Buffer, Temperatures.T5,5);
        	textArea2_4.setWildcard(textArea2_4Buffer);


        	Unicode::strncpy(textArea2_5Buffer, Temperatures.T6,5);
        	textArea2_5.setWildcard(textArea2_5Buffer);



        	Unicode::strncpy(textArea2_6Buffer, Temperatures.T7,5);
        	textArea2_6.setWildcard(textArea2_6Buffer);



        	Unicode::strncpy(textArea2_7Buffer, Temperatures.TZ,5);
        	textArea2_7.setWildcard(textArea2_7Buffer);





        	//Unicode::strncpy(textArea2_8Buffer, PWM1,4);
        	textArea2_8.setWildcard(textArea2_8Buffer);

        	//Unicode::strncpy(textArea2_9Buffer, PWM2,4);
        	textArea2_9.setWildcard(textArea2_9Buffer);

        	flag = false;

    	}

    	if (xSemaphoreTake(refresh_data_mutex, 100) == pdTRUE) {
    	Unicode::strncpy(textArea2_8Buffer, PWM1,4);

    	textArea2_8.resizeToCurrentText();
    	textArea2_8.invalidate();

    	Unicode::strncpy(textArea2_9Buffer, PWM2,4);

    	textArea2_9.resizeToCurrentText();
    	textArea2_9.invalidate();





    	Unicode::strncpy(textArea2Buffer,Temperatures.T1,5);
    	textArea2.resizeToCurrentText();
    	textArea2.invalidate();


    	Unicode::strncpy(textArea2_1Buffer, Temperatures.T2,5);
     	textArea2_1.resizeToCurrentText();
    	textArea2_1.invalidate();


    	Unicode::strncpy(textArea2_2Buffer, Temperatures.T3,5);
    	textArea2_2.resizeToCurrentText();
    	textArea2_2.invalidate();

    	Unicode::strncpy(textArea2_3Buffer, Temperatures.T4,5);
    	textArea2_3.resizeToCurrentText();
    	textArea2_3.invalidate();


    	Unicode::strncpy(textArea2_4Buffer, Temperatures.T5,5);
    	textArea2_4.resizeToCurrentText();
    	textArea2_4.invalidate();


    	Unicode::strncpy(textArea2_5Buffer, Temperatures.T6,5);
    	textArea2_5.resizeToCurrentText();
    	textArea2_5.invalidate();


    	Unicode::strncpy(textArea2_6Buffer, Temperatures.T7,5);
    	textArea2_6.resizeToCurrentText();
    	textArea2_6.invalidate();


    	Unicode::strncpy(textArea2_7Buffer, Temperatures.TZ,5);
    	textArea2_7.resizeToCurrentText();
    	textArea2_7.invalidate();




    	if(S[0].DigitalInputs & 0x01)
    	{
        	toggleButton1_8.forceState(1);
        	toggleButton1_8.invalidate();
    	}
    	else
    	{
        	toggleButton1_8.forceState(0);
        	toggleButton1_8.invalidate();
    	}



    	if(S[0].DigitalInputs & 0x02)
    	{
        	toggleButton1_9.forceState(1);
        	toggleButton1_9.invalidate();
    	}
    	else
    	{
        	toggleButton1_9.forceState(0);
        	toggleButton1_9.invalidate();
    	}



    	if(S[0].DigitalInputs & 0x04)
    	{
        	toggleButton1_10.forceState(1);
        	toggleButton1_10.invalidate();
    	}
    	else
    	{
        	toggleButton1_10.forceState(0);
        	toggleButton1_10.invalidate();
    	}


    	if(S[0].DigitalInputs & 0x08)
    	{
        	toggleButton1_11.forceState(1);
        	toggleButton1_11.invalidate();
    	}
    	else
    	{
        	toggleButton1_11.forceState(0);
        	toggleButton1_11.invalidate();
    	}


    	if(S[0].DigitalInputs & 0x10)
    	{
        	toggleButton1_12.forceState(1);
        	toggleButton1_12.invalidate();
    	}
    	else
    	{
        	toggleButton1_12.forceState(0);
        	toggleButton1_12.invalidate();
    	}


    	if(S[0].DigitalInputs & 0x20)
    	{
        	toggleButton1_13.forceState(1);
        	toggleButton1_13.invalidate();
    	}
    	else
    	{
        	toggleButton1_13.forceState(0);
        	toggleButton1_13.invalidate();
    	}


    	if(S[0].DigitalInputs & 0x40)
    	{
        	toggleButton1_14.forceState(1);
        	toggleButton1_14.invalidate();
    	}
    	else
    	{
        	toggleButton1_14.forceState(0);
        	toggleButton1_14.invalidate();
    	}



    	if(i_flag & 0x01)
    	{
    		toggleButton1_14_1.forceState(1);
    		toggleButton1_14_1.invalidate();
    	}
    	else
    	{
    		toggleButton1_14_1.forceState(0);
    		toggleButton1_14_1.invalidate();
    	}
    	xSemaphoreGive(refresh_data_mutex);
    	}


    //	SPWM[0].PWM1i


       // if(flag){Unicode::snprintf(textAreaBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_STMICROID).getText());flag = false;}
       // else{Unicode::snprintf(textAreaBuffer, TEXTAREA_SIZE, "%s", touchgfx::TypedText(T_TOUCHGFXID).getText());flag = true;}
       // textArea.invalidate();
        counter = 0;
    }




}




void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}


void MainView::SPR()
{


	 if(S[0].Out.SP == 0){
		 S[0].Out.SP = 1;
	 }
	 else
	 {
		 S[0].Out.SP = 0;
	 }


}

void MainView::PDZ()
{


	 if(S[0].Out.PDZ == 0){
		 S[0].Out.PDZ = 1;
	 }
	 else
	 {
		 S[0].Out.PDZ = 0;
	 }
}

void MainView::PCO()
{
	if(S[0].Out.PSG == 0){
		S[0].Out.PSG = 1;
	}
	else
	{
		S[0].Out.PSG = 0;
	}
}

void MainView::PCWU()
{

	if(S[0].Out.PCWU == 0){
		S[0].Out.PCWU  = 1;
	}
	else
	{
		S[0].Out.PCWU  = 0;
	}

}


void MainView::Z3D()
{

	if(S[0].Out.Z3D == 0){
		S[0].Out.Z3D  = 1;
	}
	else
	{
		S[0].Out.Z3D  = 0;
	}

}

void MainView::GR1()
{

	if(S[0].Out.DO1 == 0){
		S[0].Out.DO1  = 1;
	}
	else
	{
		S[0].Out.DO1  = 0;
	}

}

void MainView::GR2()
{

	if(S[0].Out.DO2 == 0){
		S[0].Out.DO2  = 1;
	}
	else
	{
		S[0].Out.DO2  = 0;
	}

}

void MainView::ZEWZRD()
{

	if(S[0].Out.ZZC == 0){
		S[0].Out.ZZC  = 1;
	}
	else
	{
		S[0].Out.ZZC  = 0;
	}

}

