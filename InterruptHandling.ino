#include<TM1637Display.h>
#include<avr/io.h>
#include<avr/interrupt.h>

#define CLK 9
#define DIO 8
#define BUZZER 6

TM1637Display display(CLK,DIO);

volatile unsigned int counter = 0;
volatile bool highEvent = false;
volatile bool mediumEvent = false;

volatile unsigned long triggerTime = 0;
volatile unsigned long isrStartTime = 0;
volatile unsigned long latencyValue = 0;
volatile bool showLatency = false;

volatile unsigned long triggerTimeMedium = 0;
volatile unsigned long isrStartTimeMedium = 0;
volatile unsigned long latencyValueMedium = 0;
volatile bool showLatencyMedium = false;


  enum SystemState{
    NORMAL_MODE,
    MEDIUM_MODE,
    HIGH_MODE
  };

SystemState currentState = NORMAL_MODE;


void setup() {
  display.setBrightness(7);

  pinMode(BUZZER,OUTPUT);

  pinMode(2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),
  highPriorityISR,FALLING);

  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),
  mediumPriorityISR,FALLING);


  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;
  TCCR1B |= (1 <<WGM12);
  TCCR1B |= (1 <<CS12) | (1 <<CS10);
  TIMSK1 |= (1<<OCIE1A);

  sei();

}

ISR(TIMER1_COMPA_vect){ 
    //low priority interrupt
    if(currentState == NORMAL_MODE){
     counter++;
    }
    
}

void mediumPriorityISR(){
  //TIMSK1 &= ~(1 << OCIE1A);
  //sei();
  //display.showNumberDec(5555);
  //for (volatile long i = 0;i<400000;i++);

  isrStartTimeMedium = micros();
  latencyValueMedium = isrStartTimeMedium - triggerTimeMedium;
  showLatencyMedium = true;

  if(currentState != HIGH_MODE){
    mediumEvent = true;
}

  //TIMSK1 |= (1<< OCIE1A);
}

void highPriorityISR(){

  isrStartTime = micros();
  latencyValue = isrStartTime - triggerTime;
  showLatency = true;

  //TIMSK1 &= ~(1 << OCIE1A);

  highEvent = true;
  
  //running = !running;

  //display.showNumberDec(9999);

  //for(volatile long i = 0;i< 500000;i++);
 // TIMSK1 |= (1<<OCIE1A);
  }


void loop() {

  triggerTime = micros();
  triggerTimeMedium = micros();

  if(showLatency){
    display.showNumberDec(latencyValue);
    delay(1500);
    showLatency = false;
  }

  else if(showLatencyMedium){
    display.showNumberDec(latencyValueMedium);
    delay(1500);
    showLatencyMedium = false;
  }

  if(highEvent){
    currentState = HIGH_MODE;

    digitalWrite(BUZZER,HIGH);
    delay(150);
    digitalWrite(BUZZER,LOW);
    delay(150);
    digitalWrite(BUZZER,HIGH);
    delay(150);
    digitalWrite(BUZZER,LOW);


    display.showNumberDec(9999);
    delay(5000);

    highEvent = false;
    currentState = NORMAL_MODE;
   // TIMSK1 |= (1 << OCIE1A);
  }

  else if(mediumEvent){
    currentState = MEDIUM_MODE;
    counter = 0;

    digitalWrite(BUZZER,HIGH);
    delay(600);
    digitalWrite(BUZZER,LOW);

    display.showNumberDec(8888);
    delay(5000);

    mediumEvent = false;
    currentState = NORMAL_MODE;
   // TIMSK1 |= (1 << OCIE1A);
  }

  else{
  display.showNumberDec(counter);
  }

}