uint16_t stirng_limit_len = 65535;

uint16_t string_get_len(byte_t* text){
	uint16_t size = 0;
	for (uint16_t i = 0; i < stirng_limit_len; i++){
		if (text[0] == '\0'){
			return size;
		}
		size++;
	}
}

byte_t string_get_ascii_from_number(uint16_t number){
	switch (number){
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 0: return '0';

		default: return '\0';
	}
}