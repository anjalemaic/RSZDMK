#include "../usart/usart.h"
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

const char samoglasnici[] = {
		'a', 'e', 'i', 'o', 'u'
};

int8_t proveri(char rec1[], int8_t duz1) {

	int8_t broj = 0;
	int8_t duzina = 0;

	for(int8_t i = 0; i < duzina; i++) {

		for(int8_t j = 0; j < 5; j++ ) {

			if(rec1[i] == samoglasnici[j])
				broj++;

		}

	}

	return broj;
}

int main() {

	usartInit(9600);
	char rec[64];
	char tmp[64];
	int8_t duzina = 0;
	int8_t broj = 0;

	while(1) {

		usartPutString_P(PSTR("Unesite rec:\r\n"));
		while(!usartAvailable());
		_delay_ms(100);

		duzina = usartGetString(rec);
		broj = proveri(rec, duzina);

		sprintf(tmp, "Rec ima %d samoglasnika.\r\n", broj);
		usartPutString(tmp);

	}

	return 0;
}
