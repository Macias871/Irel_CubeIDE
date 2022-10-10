/*
 * Structures.h
 *
 *  Created on: 5 paź 2022
 *      Author: Irel
 */

#ifndef GUI_INCLUDE_GUI_STRUCTURES_H_
#define GUI_INCLUDE_GUI_STRUCTURES_H_

#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#define GO_TO_SUBROUTINE 1



typedef struct TGFX_menu_struct TGFX_Menu_t;

struct TGFX_menu_struct {

	const char * name;
	TEXTS  Ttext;
	TGFX_Menu_t * next;
	TGFX_Menu_t * prev;
	TGFX_Menu_t * child;
	TGFX_Menu_t * parent;
	void (*menu_function)(void);


};




#define Menu_items 30



extern TGFX_Menu_t menu_9;
extern TGFX_Menu_t sub_menu_9_1;
	extern TGFX_Menu_t sub_menu_9_1_1;
	extern TGFX_Menu_t sub_menu_9_1_2;

extern TGFX_Menu_t sub_menu_9_2;
	extern TGFX_Menu_t sub_menu_9_2_1 ;
		extern TGFX_Menu_t sub_menu_9_2_1_1 ;
		extern TGFX_Menu_t sub_menu_9_2_1_2 ;
		extern TGFX_Menu_t sub_menu_9_2_1_3 ;
			extern TGFX_Menu_t sub_menu_9_2_1_3_1;
			extern TGFX_Menu_t sub_menu_9_2_1_3_2;
			extern TGFX_Menu_t sub_menu_9_2_1_3_3;
			extern TGFX_Menu_t sub_menu_9_2_1_3_4;
			extern TGFX_Menu_t sub_menu_9_2_1_3_5;
			extern TGFX_Menu_t sub_menu_9_2_1_3_6;
			extern TGFX_Menu_t sub_menu_9_2_1_3_7;
			extern TGFX_Menu_t sub_menu_9_2_1_3_8;
			extern TGFX_Menu_t sub_menu_9_2_1_3_9;
			extern TGFX_Menu_t sub_menu_9_2_1_3_10;
			extern TGFX_Menu_t sub_menu_9_2_1_3_11;
			extern TGFX_Menu_t sub_menu_9_2_1_3_12;
			extern TGFX_Menu_t sub_menu_9_2_1_3_13;
		extern TGFX_Menu_t sub_menu_9_2_1_4 ;
	extern TGFX_Menu_t sub_menu_9_2_2;


	extern TGFX_Menu_t sub_menu_9_1_3;
	extern TGFX_Menu_t sub_menu_9_1_4;


extern TGFX_Menu_t sub_menu_9_3;
	extern TGFX_Menu_t sub_menu_9_3_1;
	extern TGFX_Menu_t sub_menu_9_3_2;
	extern TGFX_Menu_t sub_menu_9_3_3;
	extern TGFX_Menu_t sub_menu_9_3_4;
	extern TGFX_Menu_t sub_menu_9_3_5;
	extern TGFX_Menu_t sub_menu_9_3_6;




extern TGFX_Menu_t sub_menu_9_4;
extern TGFX_Menu_t sub_menu_9_5;
extern TGFX_Menu_t sub_menu_9_6;
	extern TGFX_Menu_t sub_menu_9_6_1;
	extern TGFX_Menu_t sub_menu_9_6_2;
	extern TGFX_Menu_t sub_menu_9_6_3;
	extern TGFX_Menu_t sub_menu_9_6_4;
	extern TGFX_Menu_t sub_menu_9_6_5;
	extern TGFX_Menu_t sub_menu_9_6_6;

extern TGFX_Menu_t *Sub_menu;
extern TGFX_Menu_t Temp_menu;
extern TGFX_Menu_t TGFX_Actual_menu;
extern TGFX_Menu_t TGFX_Sub_menu;


#endif /* GUI_INCLUDE_GUI_STRUCTURES_H_ */
