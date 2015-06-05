#include <12f675.h>
//3420 ultimo numero del pic
#FUSES NOWDT, INTRC_IO, NOCPD, NOPROTECT, NOMCLR, NOPUT, NOBROWNOUT, BANDGAP_HIGH
#use delay(clock=4000000)

#define maximo	3						//---CANTIDAD DE MODOS-----
				
void enciendo_led(void);	//Modo rormal
void bl_ahorro(void);		//Modo ahorro			
void inicio(void);						
void modo_sel(void);
void modo_apago(void);


int modo=1,i=0;

void main()
{	
	#byte OSCCAL = 0x80;
	set_tris_a(0b11010001);
	setup_comparator( NC_NC_NC_NC );
	setup_adc_ports( NO_ANALOGS );
	setup_adc( ADC_OFF );
	
		
	#define GP0 PIN_A0
	#define GP1 PIN_A1
	#define GP2 PIN_A2
	#define GP3 PIN_A3
	#define GP4 PIN_A4
	#define GP5 PIN_A5
	
	output_low(GP5);				
	output_high(GP2);		//Transistor
	
	for(;;){				//Bucle infinito
		
		modo_sel();
		
		switch (modo)
		{	case 0:
			modo_apago();
			break;
			
			case 1:
			inicio();
			break;	

			case 2:
			enciendo_led();
			break;
			
			case 3:	
			bl_ahorro();

			break;

			default:
			//delay_ms(500);
			//output_high(GP5);
			//delay_ms(500);
			//output_low(GP5);
			break;


		}

	}
}


//_________FUNCIONES_______

void modo_sel()						//SELECCION DE MODO
{
if(input(GP4)==1)
		{


		if(modo<maximo)
		modo++;
		else
		modo=1;

		i=0;
		do{
		i++;
		delay_ms(100);
		}while(input(GP4)==1);
		}
		if(i>10)					//si aprieto mas de 1 segundo se resetea el modo
		modo=0;
		
return;
}

void modo_apago()				
{
		output_low(GP2);
		output_low(GP5);
return;
}

void inicio(void){
		output_high(GP2);
		output_low(GP5);
return;
}

void enciendo_led(void){
output_high(GP5);
return;
}

void bl_ahorro(void)				//AHORRO
{	output_high(GP5);
	delay_ms(3);
	output_low(GP5);
	delay_ms(12);
return;
}