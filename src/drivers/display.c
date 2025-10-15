#define VIDEO_BUFFER_PTR (0xb8000)

#include "display.h"
#include "../libs/shared_memory.h"


// Нижний лимит по y
const char display_limit_x_bottom = 79;
const char display_limit_y_bottom = 24;


// Обновить курсор
void display_cursor_update(){
    int display_cursor_location = DISPLAY_CURSOR_POS_Y * 80 + DISPLAY_CURSOR_POS_X;
    outb(0x3D4, 14);
    outb(0x3D5, display_cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, display_cursor_location);
}


// Переход на новую (следующую) строку
void display_new_line(){
    if (DISPLAY_CURSOR_POS_Y >= display_limit_y_bottom){
        DISPLAY_CURSOR_POS_Y = 0;
        display_clear();
    }
    else DISPLAY_CURSOR_POS_Y++;

    DISPLAY_CURSOR_POS_X = 0;
    display_cursor_update();
}


// Вывести символ на экран
void display_print_symbol(unsigned char symbol, unsigned short x, unsigned short y, char font_color, char bkgr_color){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
    video_mem += (80 * y + x) * 2;
    video_mem[0] = symbol;
    video_mem[1] = font_color;
    bkgr_color = bkgr_color << 4;
    video_mem[1] = video_mem[1] | bkgr_color;
    video_mem += 2;

    if ((x + 1) > display_limit_x_bottom){
        DISPLAY_CURSOR_POS_Y = y+1;
        DISPLAY_CURSOR_POS_X = 0;
    }
    else{
        DISPLAY_CURSOR_POS_X = x+1;
        DISPLAY_CURSOR_POS_Y = y;
    }

}


// Очистить весь экран
void display_clear(){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
    for (unsigned short y = 0; y < 25; y++){
        for (unsigned short x = 0; x < 80; x++){
            video_mem[0] = 0;
            video_mem[1] = 7;
            video_mem += 2;
        }
    }

    DISPLAY_CURSOR_POS_X = 0;
    DISPLAY_CURSOR_POS_Y = 0;
    display_cursor_update();
}


// Получить текущий символ (можно со смещением)
unsigned char display_get_current_symbol(short offset){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * (DISPLAY_CURSOR_POS_Y) + (DISPLAY_CURSOR_POS_X)) * 2;
    video_mem += 2 * offset;
    return video_mem[0];
}


// Удалить текущий символ (можно со смещением)
void display_delete_current_symbol(short offset){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * (DISPLAY_CURSOR_POS_Y) + (DISPLAY_CURSOR_POS_X)) * 2;
    video_mem += 2 * offset;
    video_mem[0] = 0;
    video_mem[1] = 7;

    if (DISPLAY_CURSOR_POS_X == 0){
        if (DISPLAY_CURSOR_POS_Y > 0){
            DISPLAY_CURSOR_POS_Y--;
            DISPLAY_CURSOR_POS_X = 79;
            display_cursor_update();
        }
    }
    else{
        DISPLAY_CURSOR_POS_X--;
        display_cursor_update();
    }
}
