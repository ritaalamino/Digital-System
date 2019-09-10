//--------------- MACROS Genericas ---------------//
#define clear_bit(p,b) (p&=~(0b1<<b))
#define seta_bit(p,b) (p|=0b1<<b)
#define inverte_bit(p,b) (p^=0b1<<b)
#define bit(p,b) ((p>>b)&0b1)
//---------------- MACROS PORTAS ----------------//
#define entrada_AI_B(b) clear_bit(DDRB,b); clear_bit(PORTB,b)
#define entrada_PU_B(b) clear_bit(DDRB,b); seta_bit(PORTB,b)
#define saida_B(b) seta_bit(DDRB,b)
#define inverte_B(b) inverte_bit(PORTB,b)
#define eh_um_B(b) bit(PINB,b)
#define eh_zero_B(b) !bit(PINB,b)
//---------------- MACROS TIMERS ----------------//
#define OVF 0                                    // bit habilitacao de interrupcao por OVF de TIMSK1
#define T1A 1                                    // bit habilitacao de interrupcao por T1A de TIMSK1
#define T1B 2                                    // bit habilitacao de interrupcao por T1B de TIMSK1
#define T1_clear TCCR1A = TCCR1B = 0;            // limpa registradores do T1
#define T1_prescaller_8 seta_bit(TCCR1B,CS11)    // prescaller 8 (CS11)
#define T1_prescaller_64 seta_bit(TCCR1B,CS10);seta_bit(TCCR1B,CS11); // prescaller 64 (CS10,CS11)
#define T1_prescaller_256 seta_bit(TCCR1B,CS12)  // prescaller 256 (CS12)
#define T1_prescaller_1024 seta_bit(TCCR1B,CS10);seta_bit(TCCR1B,CS12); // prescaller 64 (CS10,CS11)
#define T1_CTC_OCR1A seta_bit(TCCR1B,WGM12);     // CTC - overflow em OCR1A
#define T1_int(x) seta_bit(TIMSK1,x);            // habilita interrupÃ§Ã£o (OVF/T1A/T1B)
#define T1_nint(x) clear_bit(TIMSK1,x);          // desabilita interrupÃ§Ã£o (OVF/T1A/T1B)
#define T1OVF_v TIMER1_OVF_vect                  // bit habilitar interr OVF em TIMSK1
#define T1A_v TIMER1_COMPA_vect                  // bit habilitar interr T1A em TIMSK1
#define T1B_v TIMER1_COMPB_vect                  // bit habilitar interr T1B em TIMSK1
//---------------- FIM MACROS -------------------//

void setup(){
  Serial.begin(9600);
  saida_B(5);              // define B(5) como saÃ­da(MEGA PB5->pin11)
  T1_clear;                // limpa registradores de configuracao do TIMER1
  T1_CTC_OCR1A;            // modo: CTC - overflow em OCR1A
  T1_prescaller_256;       // prescaller TIMER1 256
  OCR1A = 6249;            // (tempo_s*clock)/prescaller-1 = ( 100ms*16Mhz)/256-1 = 6249
  OCR1A = 62499;           // (tempo_s*clock)/prescaller-1 = (1000ms*16Mhz)/256-1 = 62499
  T1_int(T1A);             // enable interrupt in T1 (OCIEA - TIMER1_COMPA_vect)
//T1_int(T1B);             // enable interrupt in T1 (OCIEB - TIMER1_COMPB_vect)
}

void loop(){}

ISR(T1A_v){                // interrupcao OCR1A match
  inverte_bit(PORTB,5);    // pisca led
  Serial.println(micros());
}

//ISR(T1B_v){              // interrupcao OCR1B match
//  clear_bit(PORTB,5);    // coloca PB5 em 0V
//}
