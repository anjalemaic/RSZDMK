#include "../usart/usart.h"
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include<avr/pgmspace.h>
#include<stdio.h>
#define duzina_ime 7
#define pass 9

int8_t proveri(char str1[], char str2[], int8_t duz1, int8_t duz2) {

	if (duz1 != duz2)
		return 0;

	for(int i = 0; i < duz1; i++) {
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

int main() {

	usartInit(9600);
	char pom [64];
	char ime [duzina_ime] = "MyName";
	char sifra [pass] = "password";
	int8_t provera = 0;
	int8_t duzina = 0;

	while(1) {
		usartPutString_P(PSTR("Unesite korisnicko ime:\r\n"));
		while(!usartAvailable());
		_delay_ms(100);
		duzina = usartGetString(pom);
		pom[duzina] = '\0';

		provera = proveri(ime, pom, duzina+1, duzina_ime);

		if(provera == 1) {

			usartPutString_P(PSTR("Unesite loziku:\r\n"));
			while(!usartAvailable());
			_delay_ms(100);
			duzina = usartGetString(pom);
			pom[duzina] = '\0';

			provera = proveri(sifra, pom, duzina+1, pass);
			if (provera == 1) {

				usartPutString_P(PSTR("Dobrodosao/la"));
				usartPutString(ime);
				usartPutString_P(PSTR("!\r\n"));
			} else
				usartPutString_P(PSTR("Logovanje je neuspesno!"));

		} else
			usartPutString_P(PSTR("Logovanje je neuspesno!"));
	}
	return 0;
}
