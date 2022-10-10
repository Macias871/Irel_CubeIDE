#include <gui/main_screen_screen/Main_screenView.hpp>

TGFX_Menu_t menu_ = { NULL, T_MENU_TITLE,NULL, NULL, NULL, NULL, NULL};
//TGFX_menu_struct   {const char * name;TEXTS  Ttext;TGFX_Menu_t * next;TGFX_Menu_t * prev;TGFX_Menu_t * child;TGFX_Menu_t * parent;void (*menu_function)(void);};
TGFX_Menu_t menu_9 = { "9. Menu", T_MENU_TITLE,NULL, NULL, &sub_menu_9_1, NULL, NULL};

TGFX_Menu_t sub_menu_9_1 = { "9.1. Nastawy podstawowe", T_DEFAULT_SETTINGS , &sub_menu_9_2, NULL, &sub_menu_9_1_1, &menu_9, NULL};

	TGFX_Menu_t sub_menu_9_1_1 = { "9.1.1 Język"            , T_LANGUAGE     , &sub_menu_9_1_2, NULL, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_2 = { "9.1.2 Zał ogrz"         , T_SET_HEAT     , &sub_menu_9_1_3, &sub_menu_9_1_2, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_3 = { "9.1.3 Ust. Fab."        , T_SET_DEFAULTS , &sub_menu_9_1_4, &sub_menu_9_1_3, NULL, &sub_menu_9_1, NULL};
	TGFX_Menu_t sub_menu_9_1_4 = { "9.1.4 Ust. Roz."        , T_SET_EXTERNALS, NULL, &sub_menu_9_1_3, NULL, &sub_menu_9_1, NULL};



TGFX_Menu_t sub_menu_9_2 = { "9.2. Serwis"            , T_SERVICE          , &sub_menu_9_3, &sub_menu_9_1, &sub_menu_9_2_1, &menu_9, NULL};

	TGFX_Menu_t sub_menu_9_2_1 = { "9.2.1. Menu ser"   , T_MENU_SERVICE  , &sub_menu_9_2_2, NULL, &sub_menu_9_2_1_1, &sub_menu_9_2, NULL};

		TGFX_Menu_t sub_menu_9_2_1_1 = { "9.2.1.1 Integral"   , T_INTEGRAL         , &sub_menu_9_2_1_2, NULL, NULL, &sub_menu_9_2_1, NULL};
		TGFX_Menu_t sub_menu_9_2_1_2 = { "9.2.1.2 Test recz." , T_MANUAL_TEST      , &sub_menu_9_2_1_3, &sub_menu_9_2_1_1, NULL, &sub_menu_9_2, Change_screen};
		TGFX_Menu_t sub_menu_9_2_1_3 = { "9.2.1.3 Instalacja" , T_INSTALLATION     , &sub_menu_9_2_1_4, &sub_menu_9_2_1_2, &sub_menu_9_2_1_3_1, &sub_menu_9_2, NULL};

			TGFX_Menu_t sub_menu_9_2_1_3_1 = {"9.2.1.3.1 Nastawy",T_DEFAULT_VALUES   , &sub_menu_9_2_1_3_2, NULL, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_2 = {"9.2.1.3.2 Czas prz",T_CHECK_TIME      , &sub_menu_9_2_1_3_3, &sub_menu_9_2_1_3_1, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_3 = {"9.2.1.3.3 Res. cza",T_WORK_TIME_RESET , &sub_menu_9_2_1_3_4, &sub_menu_9_2_1_3_2, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_4 = {"9.2.1.3.4 Cza.prac",T_WORK_TIME_INSTALL, &sub_menu_9_2_1_3_5, &sub_menu_9_2_1_3_3, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_5 = {"9.2.1.3.5 Temperat",T_TEMPERATURE     , &sub_menu_9_2_1_3_6, &sub_menu_9_2_1_3_4, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_6 = {"9.2.1.3.6 Czas zl",T_DELAY_INPUT_TIMES, &sub_menu_9_2_1_3_7, &sub_menu_9_2_1_3_5, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_7 = {"9.2.1.3.7 Czas z",T_DELAY_DEVICES_TIME, &sub_menu_9_2_1_3_8, &sub_menu_9_2_1_3_6, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_8 = {"9.2.1.3.8 Stany ",T_NORMAL_INPUT_STATES,&sub_menu_9_2_1_3_9, &sub_menu_9_2_1_3_7, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_9 = {"9.2.1.3.9 Kalib ",T_TEMP_SENSOR_CALIBRATION,&sub_menu_9_2_1_3_10, &sub_menu_9_2_1_3_8, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_10 = {"9.2.1.3.10 Reset logow ",T_LOG_RESET ,&sub_menu_9_2_1_3_11, &sub_menu_9_2_1_3_9, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_11 = {"9.2.1.3.11 Ust.kg ",T_CURVE_CORRECTION,&sub_menu_9_2_1_3_12, &sub_menu_9_2_1_3_10, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_12 = {"9.2.1.3.12 Mod sl ",T_SLAVE_MODULES   ,&sub_menu_9_2_1_3_13, &sub_menu_9_2_1_3_11, NULL, &sub_menu_9_2_1_3, NULL};
			TGFX_Menu_t sub_menu_9_2_1_3_13 = {"9.2.1.3.13 PWM ",T_PWM_PARAMETERS   ,NULL					, &sub_menu_9_2_1_3_12, NULL, &sub_menu_9_2_1_3, NULL};



		TGFX_Menu_t sub_menu_9_2_1_4 = { "9.2.1.4 Zmien haslo", T_PASSWORD_CHANGE  , NULL			  , &sub_menu_9_2_1_3, NULL, &sub_menu_9_2, NULL};

	TGFX_Menu_t sub_menu_9_2_2 = { "9.2.2. Wezwij serwis"   , T_CALL_SERVICE  , NULL, &sub_menu_9_2_1, NULL, &sub_menu_9_2, NULL};


TGFX_Menu_t sub_menu_9_3 = { "9.3. Diagnostyka"       , T_DIAGNSTIC        , &sub_menu_9_4, &sub_menu_9_2, NULL, NULL, NULL};


TGFX_Menu_t sub_menu_9_4 = { "9.4. Temp. zew."        , T_OUT_TEMPERATURE  , &sub_menu_9_5, &sub_menu_9_3, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_5 = { "9.5. Czas pracy"        , T_WORK_TIME        , &sub_menu_9_6, &sub_menu_9_4, NULL, NULL, NULL};
TGFX_Menu_t sub_menu_9_6 = { "9.6. Wybór programu"    , T_SET_PROGRAMM     , NULL         , &sub_menu_9_5, NULL, NULL, NULL};


TGFX_Menu_t *Sub_menu;
TGFX_Menu_t Temp_menu;
TGFX_Menu_t TGFX_Actual_menu;
TGFX_Menu_t TGFX_Sub_menu;

void Change_screen()
{

}

void Main_screenView::shortcut_goto_test()
{

	TGFX_Actual_menu = menu_;
	application().Test_menu_ScreenNoTransition();
}

Main_screenView::Main_screenView()
{

}

void Main_screenView::setupScreen()
{
    Main_screenViewBase::setupScreen();
    TGFX_Actual_menu = menu_9;
}

void Main_screenView::tearDownScreen()
{
    Main_screenViewBase::tearDownScreen();
}
