
#define F_CPU 1000000
#define DELAY_ON 1
#define DELAY 500
#define IGUAL_A ==
#define SEC_1 (1<<0 | 1<<2 | 1<<4 | 1<<6)
#define SEC_2 (1<<1 | 1<<3 | 1<<5 | 1<<7)
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

typedef struct estado 
{
	void (*funcionamiento)(void);
	struct estado *siguiente;
}Estado;

void apagado(void){
	PORTD = 0;
	
}
void parpadeo(){
 	PORTD =SEC_1  ;
	_delay_ms(DELAY);
	PORTD =SEC_2;
	_delay_ms(DELAY);
	
}
void desplazamiento(){
	PORTD = (PORTD!=128)?((PORTD==SEC_1) || (PORTD==SEC_2))?1:(PORTD<<1):1;
	_delay_ms(DELAY);
	
}

int main(void)
{
    /* Replace with your application code */
	Estado *estado1 = NULL;
	Estado *estado2 = NULL;
	Estado *estado3 = NULL;
	Estado *estadoActual = NULL;
	estado1 = (Estado *)malloc(sizeof(Estado));
	estado2 = (Estado *)malloc(sizeof(Estado));
	estado3 = (Estado *)malloc(sizeof(Estado));
	estadoActual = (Estado *)malloc(sizeof(Estado));
	estado1->funcionamiento = apagado;
	estado1->siguiente = estado2;
	estado2->funcionamiento = parpadeo;
	estado2->siguiente = estado3;
	estado3->funcionamiento = desplazamiento;
	estado3->siguiente = estado1;
	estadoActual->funcionamiento = *estado1->funcionamiento;
	estadoActual->siguiente = estado2;
	DDRD |= 0xFF;
	DDRC &= ~(1<<DDC0);
    while (1) 
    {
		estadoActual->funcionamiento();
		if ((PINC&(1<<DDC0)) IGUAL_A 1)
		{
			while(((PINC&(1<<DDC0))!=0) IGUAL_A 1);
			estadoActual = estadoActual->siguiente;
		}
		
    }
}

