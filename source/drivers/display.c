#define VIDEO_BUFFER_PTR (0xb8000)

volatile unsigned short display_cursor_pos_x = 0;
volatile unsigned short display_cursor_pos_y = 0;

const char display_limit_y_bottom = 23;

void display_cursor_update(){
    int display_cursor_location = display_cursor_pos_y * 80 + display_cursor_pos_x;
    outb(0x3D4, 14);
    outb(0x3D5, display_cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, display_cursor_location);
}

void display_new_line(){
    if (display_cursor_pos_y == display_limit_y_bottom){
        display_cursor_pos_y = 0;
        display_clear();
    }
    else display_cursor_pos_y++;

    display_cursor_pos_x = 0;
    display_cursor_update();
}

void display_print_symbol(unsigned char symbol, char x, char y, char font_color, char bkgr_color){
	unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * y + x) * 2;
    video_mem[0] = symbol;
    video_mem[1] = font_color;
    bkgr_color = bkgr_color << 4;
    video_mem[1] = video_mem[1] | bkgr_color;
    video_mem += 2;
}

void display_print(unsigned char* string, char x, char y, char font_color, char bkgr_color){
    for (unsigned char* i = string; *i != '\0'; i++){
        if (*i == '\n'){
            y++;
            x = 0;
            display_cursor_pos_x = x;
            display_cursor_pos_y = y;
        }
        else{
            display_print_symbol(*i, x, y, font_color, bkgr_color);
            x++;
        }
    }
}

void display_clear(){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
    for (unsigned short y = 0; y < 25; y++){
        for (unsigned short x = 0; x < 80; x++){
            video_mem[0] = 0;
            video_mem[1] = 7;
            video_mem += 2;
        }
    }

    display_cursor_pos_x = 0;
    display_cursor_pos_y = 0;
    display_cursor_update();
}

unsigned char display_get_current_symbol(short offset){ // offset - смещение, 1 = смещение на единицу вперёд -1 = смещение назад
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * (display_cursor_pos_y) + (display_cursor_pos_x)) * 2;
    video_mem += 2 * offset;
    return video_mem[0];
}

void display_delete_current_symbol(short offset){
    unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * (display_cursor_pos_y) + (display_cursor_pos_x)) * 2;
    video_mem += 2 * offset;
    video_mem[0] = 0;
    video_mem[1] = 7;

    if (display_cursor_pos_x == 0){
        if (display_cursor_pos_y > 0){
            display_cursor_pos_y--;
            display_cursor_pos_x = 79;
            display_cursor_update();
        }
    }
    else{
        display_cursor_pos_x--;
        display_cursor_update();
    }
}
