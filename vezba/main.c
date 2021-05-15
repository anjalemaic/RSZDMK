#include "../usart/usart.h"
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include<string.h>
#define br_korisnika 5

char korisnici[br_korisnika][32] = {
		"Sundjer Bob",
		"Dijego Armando",
		"Dzejms Bond",
		"Zoran Kostic Cane",
		"Kim Dzong Un"
};

char pin[br_korisnika][32] = {
		"5346", "2133", "7445", "8756", "7435"
};

int8_t proveri(char str1[], char str2[], int8_t duz1, int8_t duz2) {

	int8_t tacno = 1;

	if(duz1 != duz2)
		tacno = 0;
	for(int8_t i = 0; i < duz1; i++) {

		if(str1[i] != str2[i])
			tacno = 0;
	}
	return tacno;
}

int8_t proveri_ime(char str[], int8_t duz) {

	for (int8_t i = 0; i < br_korisnika; i++) {

		if(proveri(str, korisnici[i], duz, strlen(korisnici[i]) == 1))

				return i;
	}

	return 6;
}

int8_t proveri_sifru(char pass[], int8_t br) {

	for (int8_t i = 0; i < 4; i++) {

		if(pass[i] != pin[br][i])
			return 0;

	}
	return 1;

}

int8_t unesi(char ime[], int8_t br) {

	char sifra[4];
	char string[128];
	int8_t i = 0;

	usartPutString_P(PSTR("Unesite pin:\r\n"));
	while(!usartAvailable());
	_delay_ms(100);
	usartGetString(ime);

	while(i < 4) {

		while(!usartAvailable());
		_delay_ms(100);

		sifra[i] = usartGetChar();
		sprintf(string, "*");
		usartPutString(string);
		i++;
	}

	i = proveri_sifru(ime, br);

	return i;
}

int main() {

	usartInit(9600);
	char unos[64];
	char ispis[64];
	int8_t duzina = 0;
	int8_t tacno = 1;
	int8_t tacno1 = 1;

	while (1) {

		usartPutString_P(PSTR("Unesite ime i prezime:\r\n"));
		while(!usartAvailable());
		_delay_ms(100);
		duzina = usartGetString(unos);

		tacno = proveri_ime(unos, duzina);

		if(tacno == 6) {
			usartPutString_P(PSTR("Korisnik se ne nalazi u bazi podataka!\r\n"));
		}
		else
		{
			tacno1 = unesi(unos, tacno);

			if(tacno1 == 0)
				usartPutString_P(PSTR("Logovanje nije uspesno!\r\n"));
			else
				sprintf(ispis, "%s je uspesno ulogovan!'r'n", korisnici[tacno]);
				usartPutString(ispis);
		}

	}

	return 0;
}
