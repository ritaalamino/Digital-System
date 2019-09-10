#define PB_Entradas_AI DDRB = 0; PORTB = 0  // coloca toda a porta B como entrada em alta impedancia
#define Pullup_B(x) PORTB |= 1<<x           // define entrada Bx como pull_UP
#define Saida_B(x) DDRB |= 1<<x             // define Bx como saida
#define eh_Zero_B(x) ~PINB&(1<<x)           // verifica se porta Bx é zero
#define Inverte_B(x) PORTB ^= 1<<x          // inverte porta Bx
#define T1_modo_normal TCCR1A = TCCR1B = 0; // limpa modo / modo normal Timer1
#define T1_Hab_int_OVF TIMSK1 |= B00000001  // habilita interrupcao do Timer1

void setup(){
   Serial.begin(9600);
   //******* Definicoes das portas I/O *******//
   PB_Entradas_AI;               // coloca todas as portas B como entrada em alta impedancia
   Pullup_B(1);                  // pino B1 como entrada com PullUp interno
   Saida_B(5);                   // pino B5 como saida
   //*****************************************//

   //********* Definicoes dos Timers *********//
   TCCR1A = TCCR1B = 0;          // limpa_modo/modo_normal Timer1
   TCCR1B |= 1 << CS12;          // prescaler 256
   //*****************************************//
}

void loop(){
   if(eh_Zero_B(1)&(TIFR1^B1)){  // se botao pressionado e flag ativa
      TCNT1 = 3036;              // inicializa contador para 1s, 65536-(16MHz/256) = 3036
      Serial.println(millis());  // imprime tempo do timer 0 na serial
      Inverte_B(5);              // pisca LED
      TIFR1 ^= B11111110;        // resseta flag
   }
}
