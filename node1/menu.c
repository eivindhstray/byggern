#include "oled.h"
#include <stdint.h>
#include <string.h>
#include "adc.h"
#include <util/delay.h>
#include "menu.h"
#include <stdlib.h>

// our pages goes from 1-8 instead of 0-7 ??

//todo: Pause by pressing left button!

menu_ptr main_menu_build(void){
    menu_ptr main = malloc(sizeof(menu_t));
    main -> parent = NULL;
    main ->function = write_main_menu;
    for(int i = 0; i<4; i++){
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

    return menu_main;
}

menu_ptr menu_add(menu_ptr parent, void(*function)()){
    menu_ptr child = malloc(sizeof(menu_t));
    child->function = function;
    child->parent = parent;

    int i = 0;
    while(parent->child[i] != NULL){
        i++;
    }

    parent->child[i]= child;
    return child;
}

void menu_init(menu_ptr menu){
    int index = 1;
    

    menu_ptr curr_menu = menu;
    curr_menu->function();
    
    while(1){
        printf("hello world%d\r\n",index);
        oled_select_indicator(index);
        if(index <8 && index>0 && curr_menu->child[index-1] != NULL){
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
    print_string("SETTINGS");
    oled_select_line(2);
    print_string("MUSIC ON/OFF");
    
}

void write_settings_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("BRIGHTNESS");
    oled_select_line(2);
    print_string("FONTSIZE");
    
    

}

void write_music_menu(void){
    oled_reset();
    oled_select_line(1);
    print_string("ON");
    oled_select_line(2);
    print_string("OFF");

}


