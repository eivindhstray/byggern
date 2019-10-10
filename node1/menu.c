#include "oled.h"
#include <stdint.h>
#include <string.h>
#include "adc.h"
#include <util/delay.h>
#include "menu.h"
#include <stdlib.h>





node_t menu_build(){

    
    node_t * mainMenu = malloc(sizeof(node_t));
    mainMenu->prev = NULL;
    mainMenu->select = NULL;



    node_t * brightness = malloc(sizeof(node_t));
    brightness->select = NULL; //some function (scroll for brightness)
    brightness->prev = &mainMenu;

    node_t * music = malloc(sizeof(node_t));
    music->prev = &mainMenu;
    music->select = NULL; //some function that turns music on and off 
    

    node_t * play = malloc(sizeof(node_t));
    play->select = NULL; //some function to initiate game
    play->prev = NULL;
    

    return *mainMenu;
}

void write_main_menu(void){
    oled_reset();
    oled_select_indicator(1);
    oled_select_line(1);
    print_string("WELCOME CUNT");
    oled_select_line(3);
    print_string("PLAY");
    oled_select_line(4);
    print_string("SETTINGS");
    oled_select_line(5);
    print_string("MUSIC ON/OFF");
    oled_select_indicator(OLED.line);
}

void write_settings_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("SETTINGS");
    oled_select_line(3);
    print_string("BRIGHTNESS");
    oled_select_line(4);
    print_string("FONTSIZE");
    oled_select_indicator(OLED.line);
    

}

void write_music_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("MUSIC");
    oled_select_line(3);
    print_string("ON");
    oled_select_line(4);
    print_string("OFF");
    oled_select_indicator(OLED.line);
    

}


int menu_choice(){
    if (x_pos() <= 40){
       return 1; 
    } 
    if (x_pos() >= 245){
        return 2;
    }
    return 0 ;
}


void menu_navigate(void){

    if (OLED.screen == MAIN && OLED.line == 4 && menu_choice() == 2){
        write_settings_menu();
        OLED.screen = SETTINGS;
    }
    if (OLED.screen == MAIN && OLED.line == 5 && menu_choice() == 2){
        write_music_menu();
        OLED.screen = MUSIC;
    }
    if(menu_choice() == 1){
        write_main_menu();
        OLED.screen = MAIN;
    }
}