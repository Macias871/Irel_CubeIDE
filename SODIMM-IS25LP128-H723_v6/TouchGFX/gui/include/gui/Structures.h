/*
 * Structures.h
 *
 *  Created on: 5 paź 2022
 *      Author: Irel
 */

#ifndef GUI_INCLUDE_GUI_STRUCTURES_H_
#define GUI_INCLUDE_GUI_STRUCTURES_H_


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


extern TGFX_Menu_t *TGFX_Actual_menu;

#endif /* GUI_INCLUDE_GUI_STRUCTURES_H_ */
