#ifndef _MENU_H_
#define _MENU_H_
#include <stdlib.h>

#endif



typedef struct Menu {
    void (*function)() ;     //funksjon for å enten skrive til meny eller starte en prosess
    struct Menu * parent;   //en gitt meny
    struct Menu * child[4]; //max 4 undermenyer
    
}menu_t, *menu_ptr;



menu_ptr main_menu_build(void);

menu_ptr menu_build();

menu_ptr menu_add(menu_ptr parent, void(*function)());

void menu_init(menu_ptr menu);

void write_main_menu(void);

void write_settings_menu(void);

void write_music_menu(void);




