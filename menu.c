#include "oled.h"
#include <stdint.h>
#include "fonts.h"
#include <string.h>
#include "adc.h"
#include <util/delay.h>
#include "menu.h"


void menu_build(node_t *mainMenu){



    node_t * head = malloc(sizeof(size_t));

    node_t * current = head;
    node_t * prev = NULL;

    node_t * music = malloc(sizeof(node_t));
    node_t * play = malloc(sizeof(node_t));
    node_t * settings = malloc(sizeof(node_t));

    current = current -> settings;
    current -> prev = head;

    current->prev;

    current = current -> music;
    current -> prev = head;

    current ->prev;

    current = current -> play;
    current -> prev = head;
}