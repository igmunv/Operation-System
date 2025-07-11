int cursor_y = 0, cursor_x = 0;

void print_string(byte_t* string, int x, int y, int color){
	unsigned char* video_mem = (unsigned char*)VIDEO_BUFFER_PTR;
	video_mem += (80 * y + x) * 2; // 80 - number symbols in length, 2 - bytes (16 bits)
	while(*string){
		video_mem[0] = (unsigned char)*string;
		video_mem[1] = color;
		video_mem += 2;
		string++;
	}
}

void cursor_update(){
   int cursor_location = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Сообщаем плате VGA о том, что мы посылаем старший байт курсора.
   outb(0x3D5, cursor_location >> 8); // Посылаем старший байт курсора.
   outb(0x3D4, 15);                  // Сообщаем плате VGA о том, что мы посылаем младший байт курсора.
   outb(0x3D5, cursor_location);      // Посылаем младший байт курсора.
}

void clear(){

}

void colorland(){

	int symbol = 33;
	int x = 5, y = 5, c = 0;
	while(symbol < 127){
		
		print_string((char*)&symbol, x, y, c);

		if (x == 79) {x=0;y++;}
		else x++;

		if (c == 15) c=0;
		else c++;

		symbol++;
		sleep(400000);
	}
}

void welcome(){
	byte_t* message = "Welcome to OS!";
	int horiz_line = 45;

	for (int i = 0; i < 20; i++){
		print_string((char*)&horiz_line, 30+i, 0, 2);
		print_string((char*)&horiz_line, 30+i, 2, 2);
	}

	print_string(message, 33, 1, 2);
}

void main_text(int x, int y){
	byte_t* text = ">>> ";
	print_string(text, x, y, 2);
}

void terminal_init(){
	welcome();

	cursor_x = 4;
	cursor_y = 5;
	cursor_update();
	colorland();
	main_text(0,5);
	while (1){

		byte_t* str = "abcd\0";
		uint16_t size1 = string_get_len(str);
		byte_t size1_ascii = string_get_ascii_from_number(size1);
		print_string(&size1_ascii, 4, 4, 2);

		byte_t scan_code = keyboard_get_scancode();
		if ((scan_code >= 2 && scan_code <= 11) || (scan_code >= 16 && scan_code <= 25) || 
			(scan_code >= 30 && scan_code <= 38) || (scan_code >= 44 && scan_code <= 50) || scan_code == 57) { // цифры и буквы
			byte_t symbol = keyboard_translate_scancodes_in_ascii(scan_code);
			print_string(&symbol, cursor_x, cursor_y, 2);
			cursor_x += 1;
			if (cursor_x > 70){
				cursor_y += 1;
				cursor_x = 1;
			}
			cursor_update();
			sleep(500000);

			// засыпать на подольше если клавиша не отжата
			// если же клавишу отжали то засыпать на поменьше
			// это чтобы не было случайного ввода одного и того же символа
		}
	}
}