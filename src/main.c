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
#include "notes.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

//Define os PIOs e Pinos

#define BUT0_PIO           PIOA                  
#define BUT0_PIO_ID        ID_PIOA                      
#define BUT0_PIO_IDX       11u                      
#define BUT0_PIO_IDX_MASK  (1u << BUT0_PIO_IDX)   

#define BUT1_PIO           PIOD                  
#define BUT1_PIO_ID        ID_PIOD                      
#define BUT1_PIO_IDX       28u                      
#define BUT1_PIO_IDX_MASK  (1u << BUT1_PIO_IDX)   

#define BUT2_PIO           PIOC                  
#define BUT2_PIO_ID        ID_PIOC                      
#define BUT2_PIO_IDX       31u                      
#define BUT2_PIO_IDX_MASK  (1u << BUT2_PIO_IDX)   

#define BUT3_PIO           PIOA                  
#define BUT3_PIO_ID        ID_PIOA                      
#define BUT3_PIO_IDX       19u                      
#define BUT3_PIO_IDX_MASK  (1u << BUT3_PIO_IDX)   

#define BUZZ_PIO		   PIOA
#define BUZZ_PIO_ID        ID_PIOA                      
#define BUZZ_PIO_IDX       21u                      
#define BUZZ_PIO_IDX_MASK  (1u << BUZZ_PIO_IDX)  

#define LED0_PIO           PIOC                  
#define LED0_PIO_ID        12                      
#define LED0_PIO_IDX       8u                      
#define LED0_PIO_IDX_MASK  (1u << LED0_PIO_IDX)   

#define LED1_PIO           PIOA                  
#define LED1_PIO_ID        ID_PIOA                      
#define LED1_PIO_IDX       0u                      
#define LED1_PIO_IDX_MASK  (1u << LED1_PIO_IDX)   

#define LED2_PIO           PIOC                  
#define LED2_PIO_ID        ID_PIOC                      
#define LED2_PIO_IDX       30u                      
#define LED2_PIO_IDX_MASK  (1u << LED2_PIO_IDX)   

#define LED3_PIO           PIOB                  
#define LED3_PIO_ID        ID_PIOB                      
#define LED3_PIO_IDX       2u                      
#define LED3_PIO_IDX_MASK  (1u << LED3_PIO_IDX)   


//Vetores de Notas
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

//LINK ORIGINAL DA MUSICA MARIO: http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/

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
//Vetores de duração de nota
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



void init(void);


// Fun��o de inicializa��o do uC
void init(void)
{
  // Initialize the board clock
  sysclk_init();
  
  // Desativa WatchDog Timer
  WDT->WDT_MR = WDT_MR_WDDIS;

  //Da enable nos PIOS

  pmc_enable_periph_clk(BUT1_PIO_ID);
  pmc_enable_periph_clk(BUT2_PIO_ID);
  pmc_enable_periph_clk(BUT3_PIO_ID);
  pmc_enable_periph_clk(LED3_PIO_ID);

  //Seta os pinos como saida ou entrada

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

//Funções de Ligar e Desligar LEDs

void led0_set() {
	  pio_set(LED0_PIO,LED0_PIO_IDX_MASK);
}

void led0_clear() {
	pio_clear(LED0_PIO,LED0_PIO_IDX_MASK);
}

void led1_set() {
	pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
}

void led1_clear() {
	pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
}

void led2_set() {
	pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
}

void led2_clear() {
	pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
}

void led3_set() {
	pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
}

void led3_clear() {
	pio_clear(LED3_PIO,LED3_PIO_IDX_MASK);
}

//Função de Tocar nota

void tone(int frequency, int duration, Pio *p_pio, const uint32_t ul_mask){
	led0_clear();
	int n_modules = frequency * duration/1000;
	int delay = 1000000/(2*frequency);
	for (int i = 0; i<n_modules; i++){
		pio_set(p_pio, ul_mask);

		delay_us(delay);

		pio_clear(p_pio, ul_mask);

		delay_us(delay);
	}
	led0_set();
}

//Função para pegar tamanho dos vetores

int getVectorSize(int *p) {
	return sizeof(p) / sizeof(int);
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
  float speed = 1.3;
  
  led0_set();
  led1_set();
  led2_set();
  led3_set();
  while (1)
  {
	
	//Botao de Power
	if(!pio_get(BUT0_PIO,PIO_INPUT,BUT0_PIO_IDX_MASK)){
		led0_set();
		led1_set();
		led2_set();
		power = !power;
		delay_ms(500);
	}
	if(power == 1){
		led0_clear();
		if(musica == 1){
			led1_clear();
		}

		//Selecao de Musica
		if(!pio_get(BUT1_PIO,PIO_INPUT,BUT1_PIO_IDX_MASK)){
			led2_set();
			led1_clear();
			musica = 1;
		}
		if(!pio_get(BUT2_PIO,PIO_INPUT,BUT2_PIO_IDX_MASK)){
			led1_set();
			led2_clear();
			musica = 2;
		}

		//Botao de Play
		if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
			led3_clear();
			delay_ms(500);
			if(musica == 1){
				int size = getVectorSize(megalovania);

				//Loop de notas
				for (int thisNote = 0; thisNote < size; thisNote++) {
					int noteDuration = 500 / tempo_mega[thisNote];
					tone(megalovania[thisNote], noteDuration, BUZZ_PIO, BUZZ_PIO_IDX_MASK);
					int pauseBetweenNotes = noteDuration * speed;
					delay_ms(pauseBetweenNotes);
					tone(0, noteDuration, BUZZ_PIO, BUZZ_PIO_IDX_MASK);
					if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
						led3_set();
						delay_ms(500);
						break;
					}
					
				}
				led3_set();
			}
			if(musica == 2){
				int size = getVectorSize(melody);
				for (int thisNote = 0; thisNote < size; thisNote++) {
					int noteDuration = 1000 / tempo_mario[thisNote];
					tone(melody[thisNote], noteDuration, BUZZ_PIO, BUZZ_PIO_IDX_MASK);
					int pauseBetweenNotes = noteDuration * speed;
					delay_ms(pauseBetweenNotes);
					tone(0, noteDuration, BUZZ_PIO, BUZZ_PIO_IDX_MASK);
					if(!pio_get(BUT3_PIO,PIO_INPUT,BUT3_PIO_IDX_MASK)){
						led3_set();
						delay_ms(500);
						break;
					}
				}
				led3_set();
			}
		}
	}

  }
  return 0;
}
