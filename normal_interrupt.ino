
#define PB_Entradas_AI DDRB = 0; PORTB = 0 // coloca toda a porta B como entrada em alta impedancia
#define Pullup_B(x) PORTB |= 1<<x          // define entrada Bx como pull_UP
#define Saida_B(x) DDRB |= 1<<x            // define Bx como saida
#define eh_Zero_B(x) ~PINB&(1<<x)          // verifica se porta Bx é zero
#define Inverte_B(x) PORTB ^= 1<<x         // inverte porta Bx
#define T1_modo_normal TCCR1A = B00000000  // configura timer1 para operação normal pinos OC1A e OC1B desconectados
#define T1_PRE_256 TCCR1B = B00000100;     // prescaler 256 * 2^16 ~ 16Mhz 
#define T1_Hab_int_OVF TIMSK1 |= B00000001 // habilita a interrupcao de OVF do TIMER1
#define T1_1s_OVF TCNT1 = 3036             // 65536-(16MHz/256) = 3036, inicializa o timer com um valor para que de os exatos x segundos de estouro

void setup(){
   Serial.begin(9600);
   //******* Definicoes das portas I/O *******//
   PB_Entradas_AI;        // coloca todas as portas B como entrada em alta impedancia
   Pullup_B(1);           // pino B1 como entrada com PullUp interno
   Saida_B(5);            // pino B5 como saida
   //*****************************************//
   
   //********* Definicoes dos timers *********//
   T1_modo_normal;        // modo normal do TIMER1
   T1_PRE_256;            // seta prescaler do timer1 em 256
   T1_Hab_int_OVF;        // habilita a interrupcao de overflow do TIMER1
   sei();                 // habilita interrupcoes globais -> sei() = interrupts()
   //*****************************************//
}

void loop(){}

ISR(TIMER1_OVF_vect){     // INTERRUPCAO DE OVERFLOW DO TIMER1
   T1_1s_OVF;             // inicializa Timer1 para overflow de 1s
   Serial.println(micros());
   if(eh_Zero_B(1))       // se botao pressionado
      Inverte_B(5);       // pisca LED
}
