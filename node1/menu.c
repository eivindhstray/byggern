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
    for(int i = 0; i<8; i++){
        main -> child[i] = NULL;
    }
    return main;
}

menu_ptr menu_build(){
    
    menu_ptr menu_main = main_menu_build();
    menu_ptr menu_settings = menu_add(menu_main, &write_settings_menu);
    menu_ptr menu_music = menu_add(menu_main, &write_music_menu);
    menu_ptr settings_brightness = menu_add(menu_settings, NULL);
    menu_ptr settings_fontsize = menu_add(menu_settings,NULL);
    menu_ptr music_off = menu_add(menu_music, NULL);
    menu_ptr mucis_on = menu_add(menu_music, NULL);
    //menu_ptr play = menu_add(menu_main, &play_game);

    return menu_main;
}

menu_ptr menu_add(menu_ptr parent, void(*function)()){
    menu_ptr child = malloc(sizeof(menu_t));
    child->function = function;
    child->parent = parent;

    int i = 2;
    while(parent->child[i] != NULL){
        i++;
    }
    printf("menu build %d\n\r", i);

    parent->child[i]= child;
    return child;
}

void menu_init(menu_ptr menu){
    int index = 3;
    

    menu_ptr curr_menu = menu;
    curr_menu->function();
    
    while(1){
        printf("hello world%d\r\n",index);
        oled_select_indicator(index);
        if(index <8 && index>2 && curr_menu->child[index-1] != NULL){
            if(oled_scroll() == 1){
                index +=1;
            }  //DOES THIS BRING THE ARROW UP OR DOWN?
            if(oled_scroll() == -1){
                index -=1;
            }


            
        }
        
        if(oled_select()==1 && curr_menu->child[index-1] != 0){
            curr_menu = menu->child[index-1];
            curr_menu ->function();
            
        }
        if(oled_select() == -1){
            curr_menu = menu->parent;
            curr_menu ->function();
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
    print_string("MUSIC ON/OFF");
    oled_select_line(5);
    print_string("PLAY");
    
}

void write_settings_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("SETTINGS MENU");
    oled_select_line(3);
    print_string("BRIGHTNESS");
    oled_select_line(4);
    print_string("FONTSIZE");
    
    

}

void write_music_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("MUSIC MENU");
    oled_select_line(3);
    print_string("ON");
    oled_select_line(4);
    print_string("OFF");

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
/*
void play_game(void){
    oled_write_c(0xae);  //supposed to turn OLED off.
    
    message_t position;
    position.id = 0b01;
    position.length = 5;

    uint8_t position_before[8];
    joystick_update_details(&position);
    can_should_send(position , &position_before);

    for (i = 0; i < 6; i++){
        position_before[i] = position.data[i];
    }

}*/