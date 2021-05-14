#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include "../usart/usart.h"

int main() {

	usartInit(9600);
	char tekst[64];
	int duzina;
	char jeste = 1;

	while(1) {

		usartPutString("Unesite rec:\r\n");
		while(!usartAvailable());
		_delay_ms(100);
		usartGetString(tekst);

		usartPutString_P(PSTR("Unesena rec"));
		usartPutString(tekst);

		for(duzina=0; tekst[duzina] != '/0'; duzina++);
		for(int i=0; i < (duzina/2); i++) {
			if(tekst[i] == tekst[duzina-1-i])
				jeste = 1;
		}
		if (jeste ==1)
			usartPutString_P(PSTR("jeste palindrom.\r\n"));
		else
			usartPutString_P(PSTR("nije palindrom.\r\n"));

	}
	return 0;
}
