/**
 * SerInge_Ejercicio_1.c
 *
 * Created: 24/03/2021 04:01:55 p. m.
 * Author : jimmy
 */ 
#define F_CPU 1e6
#define STATUS_BIT PORTD7
#define BIT_INICIO PORTD3
#define BIT_FIN	PORTD6
#define MODO_PUERTO(PUERTO,MASCARA)	PUERTO |= MASCARA
#define DIRECCION_PUERTO_D DDRD
#define PUERTO_LEDS PORTD
#define TODOS_BITS_SALIDAS 0XFF
#define ENCENDER_LED(PUERTO,BIT) PUERTO |=  _BV(BIT)
#define APAGAR_LED(PUERTO,BIT)  PUERTO &= ~_BV(BIT)
#define FIN_DE_SECUENCIA (_BV(STATUS_BIT) | _BV(BIT_FIN))
#define RECORRER_BIT(PUERTO) PUERTO = (PUERTO_LEDS!=FIN_DE_SECUENCIA)?\
                             PUERTO<<1 | _BV(STATUS_BIT):\
                             _BV(PORTD0) | _BV(STATUS_BIT)

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	MODO_PUERTO(DIRECCION_PUERTO_D,TODOS_BITS_SALIDAS);
	ENCENDER_LED(PUERTO_LEDS,STATUS_BIT);
	ENCENDER_LED(PUERTO_LEDS,BIT_INICIO);
    while (1) 
    {
		RECORRER_BIT(PUERTO_LEDS);
//		_delay_ms(500);
    }
}

