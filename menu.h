#ifndef _MENU_H_
#define _MENU_H_
#include <stdlib.h>

#endif

typedef struct node{
    
    struct node_t * prev;
    struct node_t * select;
    
    
}node_t;


node_t menu_build();


void write_main_menu(void);

void write_settings_menu(void);

void write_music_menu(void);

int menu_choice();

void menu_navigate(void);

