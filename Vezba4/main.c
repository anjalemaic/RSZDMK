/**
 * @file main.c
 * @brief Aplikacija koja implementira ogranicen broj treptanja diode
 * @author Anja Lemaic
 * @date 22-03-2021
 * @version 1.0
 */

#include "../pin_driver/pin.h"
#include "../timer0_driver/timer0.h"

/**
 * pinPulse - Funkcija koja implementiran podizanje i spustanje vrednosti na pinu
 * odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - Port na kojem je potrebno implementirati funkcionalnost
 * @param pin - ulaz tipa unsigned char - Pin na kojem je potrebno implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - Perioda promene vrednosti na pinu
 * @return Nema povratnu vrednost
 */
void pinPulse(unsigned char port, unsigned char pin, unsigned long period);

/**
 * main - funkcija koja implementiran glavni deo aplikacije
 * @return Nema povratnu vrednost
 */
int main()
{
	unsigned long period = 1000; // Period jednog treptaja
	unsigned char repetitions = 5; // Broj treptaja
	int i;
	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();
	// Glavna petlja
	while (1)
	{
		// Treptanje
		for(i = 0; i < repetitions; i++)
			pinPulse(PORT_B, DIODE_PIN, period);
		// Kraj
		while(1)
			;
	}
	return 0;
}

/******************************************************************************************/
void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
	// Poluperioda u kojoj pin ima visoku vrednost
	pinSetValue(port, pin, HIGH);
	timer0DelayMs(period/2);
	// Poluperioda u kojoj pin ima nisku vrednost
	pinSetValue(port, pin, LOW);
	timer0DelayMs(period/2);
}
