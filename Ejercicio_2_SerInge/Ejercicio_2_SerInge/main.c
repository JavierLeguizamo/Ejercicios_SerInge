#define F_CPU 1e6
#define SECUENCIA_1 (_BV(0)|_BV(2)|_BV(4)|_BV(6))
#define SECUENCIA_2 (_BV(1)|_BV(3)|_BV(5)|_BV(7))
#define CONFIG_SALIDAS_PD(BITS_SALIDAS) DDRD |= BITS_SALIDAS;
#define TODOS_BITS_SALIDAS 0XFF
#define ESCRIBIR_PD(BITS_A_ESCRIBIR) PORTD = BITS_A_ESCRIBIR
#define LEER_BIT_PC(BIT) ((PINC&(1<<BIT))==0)
#define APAGADO 0
#define BOTON PINC0
#define ESPERA_SOLTAR_BOTON(BIT) while(LEER_BIT_PC(BIT) == APAGADO)
#define SIGUIENTE_ESTADO estado++
#define ESPERA 500

#include <avr/io.h>
#include <util/delay.h>

typedef enum{
			estado1,
			estado2,
			estado3
}Estado;
	
void apagado(){
	ESCRIBIR_PD(0);
}
void parpadeo(){
	ESCRIBIR_PD(SECUENCIA_1);
	_delay_ms(ESPERA);
	ESCRIBIR_PD(SECUENCIA_2);
	_delay_ms(ESPERA);
	
} 
void desplazamiento(){
	PORTD = (PORTD!=128)?((PORTD==SECUENCIA_1) || (PORTD==SECUENCIA_2))?1:(PORTD<<1):1;
	_delay_ms(ESPERA);
}
int main(void)
{
    /* Replace with your application code */
	Estado estado = estado1;
	CONFIG_SALIDAS_PD(TODOS_BITS_SALIDAS);
    while (1) 
    {
		if (LEER_BIT_PC(BOTON) == APAGADO)
		{
			ESPERA_SOLTAR_BOTON(BOTON);
			SIGUIENTE_ESTADO;
		}
		switch(estado){
			case estado1:
				apagado();
				break;
			case estado2:
				parpadeo();
				break;
			case estado3:
				desplazamiento();
				break;
			default:
				estado = estado1;
				break;
    }
	}
}

