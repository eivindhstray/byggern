#ifndef _MENU_H_
#define _MENU_H_
#include <stdlib.h>

#endif


typedef struct Menu {
    void (*function)() ;     //funksjon for å enten skrive til meny eller starte en prosess
    struct Menu * parent;   //en gitt meny
    struct Menu * child[8]; //max 8 undermenyer
    int exit;
    
}menu_t, *menu_ptr;

char int_to_score(int integer);

void get_score(int goals);

menu_ptr main_menu_build(void);

menu_ptr menu_build();

menu_ptr menu_add(menu_ptr parent, void(*function)(), int exit);

void menu_run(menu_ptr menu);

void write_main_menu(void);

void write_settings_menu(void);

void write_music_menu(void);

//Additional after Stray left the lab
void write_open_message(void);

void play_game(void);

void menu_pause(void);

void menu_brightness_high();

void menu_brightness_low();

void play_draw(void);

void write_win_menu(void);

void write_lost_menu(void);
