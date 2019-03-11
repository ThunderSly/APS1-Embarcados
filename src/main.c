/**
 * 5 semestre - Eng. da Computa��o - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define BUT0_PIO           PIOA                  // periferico que controla o LED
#define BUT0_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define BUT0_PIO_IDX       11u                    // ID do LED no PIO
#define BUT0_PIO_IDX_MASK  (1u << BUT0_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define BUT1_PIO           PIOD                  // periferico que controla o LED
#define BUT1_PIO_ID        ID_PIOD                    // ID do periférico PIOC (controla LED)
#define BUT1_PIO_IDX       28u                    // ID do LED no PIO
#define BUT1_PIO_IDX_MASK  (1u << BUT1_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define BUT2_PIO           PIOC                  // periferico que controla o LED
#define BUT2_PIO_ID        ID_PIOC                    // ID do periférico PIOC (controla LED)
#define BUT2_PIO_IDX       31u                    // ID do LED no PIO
#define BUT2_PIO_IDX_MASK  (1u << BUT2_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define BUT3_PIO           PIOA                  // periferico que controla o LED
#define BUT3_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define BUT3_PIO_IDX       19u                    // ID do LED no PIO
#define BUT3_PIO_IDX_MASK  (1u << BUT3_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define BUZZ_PIO		   PIOA
#define BUZZ_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define BUZZ_PIO_IDX       21u                    // ID do LED no PIO
#define BUZZ_PIO_IDX_MASK  (1u << BUZZ_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define LED0_PIO           PIOC                  // periferico que controla o LED
#define LED0_PIO_ID        12                    // ID do periférico PIOC (controla LED)
#define LED0_PIO_IDX       8u                    // ID do LED no PIO
#define LED0_PIO_IDX_MASK  (1u << LED0_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define LED1_PIO           PIOA                  // periferico que controla o LED
#define LED1_PIO_ID        ID_PIOA                    // ID do periférico PIOC (controla LED)
#define LED1_PIO_IDX       0u                    // ID do LED no PIO
#define LED1_PIO_IDX_MASK  (1u << LED1_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define LED2_PIO           PIOC                  // periferico que controla o LED
#define LED2_PIO_ID        ID_PIOC                    // ID do periférico PIOC (controla LED)
#define LED2_PIO_IDX       30u                    // ID do LED no PIO
#define LED2_PIO_IDX_MASK  (1u << LED2_PIO_IDX)  // Mascara para CONTROLARMOS o LED

#define LED3_PIO           PIOB                  // periferico que controla o LED
#define LED3_PIO_ID        ID_PIOB                    // ID do periférico PIOC (controla LED)
#define LED3_PIO_IDX       2u                    // ID do LED no PIO
#define LED3_PIO_IDX_MASK  (1u << LED3_PIO_IDX)  // Mascara para CONTROLARMOS o LED


//Mario main theme melody
int melody[] = {
	NOTE_E7, NOTE_E7, 0, NOTE_E7,
	0, NOTE_C7, NOTE_E7, 0,
	NOTE_G7, 0, 0,  0,
	NOTE_G6, 0, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0,
	
	NOTE_C7, 0, 0, NOTE_G6,
	0, 0, NOTE_E6, 0,
	0, NOTE_A6, 0, NOTE_B6,
	0, NOTE_AS6, NOTE_A6, 0,
	
	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, 0, NOTE_F7, NOTE_G7,
	0, NOTE_E7, 0, NOTE_C7,
	NOTE_D7, NOTE_B6, 0, 0
};

int megalovania[]={
	NOTE_B6, NOTE_B6, NOTE_B7, 0, 
	NOTE_FS6, 0, 0,NOTE_F6,
	0,NOTE_E6, 0,NOTE_D6,
	0,NOTE_B6, NOTE_D6, NOTE_E6,
	
	NOTE_A6, NOTE_A6, NOTE_B7, 0,
	NOTE_FS6, 0, 0,NOTE_F6,
	0,NOTE_E6, 0,NOTE_D6,
	0,NOTE_B6, NOTE_D6, NOTE_E6,
	
	NOTE_GS6, NOTE_GS6, NOTE_B7, 0,
	NOTE_FS6, 0, 0,NOTE_F6,
	0,NOTE_E6, 0,NOTE_D6,
	0,NOTE_B6, NOTE_D6, NOTE_E6,
	
	NOTE_G6, NOTE_G6, NOTE_B7, 0,
	NOTE_FS6, 0, 0,NOTE_F6,
	0,NOTE_E6, 0,NOTE_D6,
	0,NOTE_B6, NOTE_D6, NOTE_E6
	
};
//Mario main them tempo
int tempo_mario[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	
	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

int tempo_mega[] = {
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8,
	8, 8, 8, 8
	
	};

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

// Fun��o de inicializa��o do uC
void init(void)
{
  // Initialize the board clock
  sysclk_init();
  
  // Desativa WatchDog Timer
  WDT->WDT_MR = WDT_MR_WDDIS;

  pmc_enable_periph_clk(BUT1_PIO_ID);
  pmc_enable_periph_clk(BUT2_PIO_ID);
  pmc_enable_periph_clk(BUT3_PIO_ID);
  pmc_enable_periph_clk(LED3_PIO_ID);

  pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(LED0_PIO, LED0_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
  pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);

  pio_set_input(BUT0_PIO, BUT0_PIO_IDX_MASK, PIO_PULLUP);
  pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP);
  pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP);
  pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP);
}

void tone(int frequency, int duration){
	pio_clear(LED0_PIO, LED0_PIO_IDX_MASK);
	int n_modules = frequency * duration/1000;
	int delay = 1000000/(2*frequency);
	for (int i = 0; i<n_modules; i++){
		pio_set(BUZZ_PIO, BUZZ_PIO_IDX_MASK);

		delay_us(delay);

		pio_clear(BUZZ_PIO, BUZZ_PIO_IDX_MASK);

		delay_us(delay);
	}
	pio_set(LED0_PIO, LED0_PIO_IDX_MASK);
}
/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();
  int power = 0;
  int musica = 1;
  // super loop
  // aplicacoes embarcadas n�o devem sair do while(1).
  pio_set(LED0_PIO,LED0_PIO_IDX_MASK);
  pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
  pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
  pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
  while (1)
  {
	if(!pio_get(BUT0_PIO,PIO_INPUT,BUT0_PIO_IDX_MASK)){
		pio_set(LED0_PIO, LED0_PIO_IDX_MASK);
		pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
		power = !power;
		delay_ms(500);
	}
	if(power == 1){
		pio_clear(LED0_PIO,LED0_PIO_IDX_MASK);
		if(musica == 1){
			pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		}
		if(!pio_get(BUT1_PIO,PIO_INPUT,BUT1_PIO_IDX_MASK)){
			pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
			pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
			musica = 1;
		}
		if(!pio_get(BUT2_PIO,PIO_INPUT,BUT2_PIO_IDX_MASK)){
			pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
			pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
			musica = 2;
		}
		if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
			pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
			delay_ms(500);
			if(musica == 1){
				int size = sizeof(megalovania) / sizeof(int);
				for (int thisNote = 0; thisNote < size; thisNote++) {
					int noteDuration = 500 / tempo_mega[thisNote];
					tone(megalovania[thisNote], noteDuration);
					int pauseBetweenNotes = noteDuration * 1.30;
					delay_ms(pauseBetweenNotes);
					tone(0, noteDuration);
					if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
						pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
						delay_ms(500);
						break;
					}
					
				}
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			}
			if(musica == 2){
				int size = sizeof(melody) / sizeof(int);
				for (int thisNote = 0; thisNote < size; thisNote++) {
					int noteDuration = 1000 / tempo_mario[thisNote];
					tone(melody[thisNote], noteDuration);
					int pauseBetweenNotes = noteDuration * 1.30;
					delay_ms(pauseBetweenNotes);
					tone(0, noteDuration);
					if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
						pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
						delay_ms(500);
						break;
					}
				}
				pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
			}
		}
	}

  }
  return 0;
}
