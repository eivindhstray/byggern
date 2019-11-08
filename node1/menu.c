#include "oled.h"
#include <stdint.h>
#include <string.h>
#include "adc.h"
#include <util/delay.h>
#include "menu.h"
#include "can.h"
#include "joystick.h"
#include <stdlib.h>

// our pages goes from 1-8 instead of 0-7 ??

//todo: Pause by pressing left button!



menu_ptr main_menu_build(void){
    menu_ptr main = malloc(sizeof(menu_t));
    main -> parent = NULL;
    main ->function = write_main_menu;
    main ->exit = 0;
    for(int i = 0; i<8; i++){
        main -> child[i] = NULL;
    }
    
    return main;
}

menu_ptr menu_build(){
    
    menu_ptr menu_main = main_menu_build();
    menu_ptr menu_settings = menu_add(menu_main, &write_settings_menu,0);
    menu_ptr play = menu_add(menu_main, &play_game,1);
    menu_ptr settings_brightness_high = menu_add(menu_settings, &menu_brightness_high,0);
    menu_ptr settings_brightness_low = menu_add(menu_settings, &menu_brightness_low,0);
     
    

    return menu_main;
}

menu_ptr menu_add(menu_ptr parent, void(*function)(), int exit){
    menu_ptr sub_menu = malloc(sizeof(menu_t));
    sub_menu->function = function;
    sub_menu->parent = parent;
    sub_menu->exit = exit;

    

    //for(int i = 0; i<8; i++){
    //    sub_menu->child[i] = NULL;
    //}

    int i = 3;

    while(parent->child[i] != NULL){
        i++;
    }

    parent->child[i]= sub_menu;
    return sub_menu;
    
}

void menu_init(menu_ptr menu){
    int index = 3;
    

    menu_ptr curr_menu = menu;
    curr_menu->function();
    
    while( curr_menu->exit !=1){
        
        oled_select_indicator(index);
        if(curr_menu->child[index+1] != NULL){
            if(oled_scroll() == 1){
                index +=1;
            }  
        }
        if(curr_menu->child[index-1] != NULL){
            if(oled_scroll() == -1){
                index -=1;
            }
        }


        
        if(oled_select() == 1 && curr_menu->child[index] != NULL){
            curr_menu = curr_menu->child[index];
            curr_menu ->function();
            
        }
        if(oled_select() == -1 && curr_menu->parent != NULL){
            curr_menu = curr_menu->parent;
            curr_menu ->function();
            index = 3;

        }
    }
}


void write_main_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("WELCOME");
    oled_select_line(3);
    print_string("SETTINGS");
    oled_select_line(4);
    print_string("PLAY");
    printf("main menu");
    
}

void write_settings_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("SETTINGS MENU");
    oled_select_line(3);
    print_string("BRIGHTNESS HIGH");
    oled_select_line(4);
    print_string("BRIGHTNESS LOW");
    printf("settings");
    

}

void write_music_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("MUSIC MENU");
    oled_select_line(3);
    print_string("ON");
    oled_select_line(4);
    print_string("OFF");
    printf("music");
}

void write_open_message(void){
    oled_reset();
    oled_select_line(2);
    print_string("HELLO THERE");
    oled_select_line(3);
    print_string("TRAVELLER");
    oled_select_line(5);
    print_string("WELCOME TO OUR");
    oled_select_line(6);
    print_string("ARCADE GAME!");
}

void play_game(void){
    oled_reset();
    print_string("playing game");
    printf("playing...");
}


void menu_pause(void){

    if(l_button()){
        oled_reset();
        print_string("pause");
        oled_select_line(2);
        print_string("press right");
        oled_select_line(3);
        print_string("button");
        oled_select_line(4);
        print_string("to continue");
        while(!r_button()){
            if(r_button()){
                oled_reset();
                print_string("playing...");
            }
        }
    }
}


void menu_brightness_high(){
    oled_reset();
    
    oled_bright_high();
    print_string("high brightness");
    oled_select_line(3);
    print_string("left to return");
}

void menu_brightness_low(){
    oled_reset();
    
    oled_bright_low();
    print_string("low brightness");
    oled_select_line(3);
    print_string("left to return");
}