// Simple test for Burroughs barGraph on Arduino. 
// Aart, 10-2023
 
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); // Reset kathode
  pinMode(3, OUTPUT); // A kathodes
  pinMode(4, OUTPUT); // B kathodes
  pinMode(5, OUTPUT); // C kathodes
}
 
void loop() {
  // put your main code here, to run repeatedly:
  scan_segments(); 
}
 
void scan_segments() { 
  static int state = 0, segment = 0, count = 0; 
  static unsigned long lastTime = 0; 
  enum state {RESET, A, B, C}; 
 
  // Run once every 70 us
  if ((micros() - lastTime) < 70 ) {
    return; 
  }
  lastTime = micros(); 
 
  switch (state) {
    case RESET: 
      digitalWrite(2, HIGH); 
      digitalWrite(3, LOW); 
      digitalWrite(4, LOW); 
      digitalWrite(5, LOW); 
      state = A; 
    break;
    case A:
      digitalWrite(3, HIGH); 
      digitalWrite(2, LOW); 
      digitalWrite(4, LOW); 
      digitalWrite(5, LOW); 
      state = B; 
      segment++;
    break;
    case B:
      digitalWrite(4, HIGH); 
      digitalWrite(2, LOW); 
      digitalWrite(3, LOW); 
      digitalWrite(5, LOW); 
      state = C; 
      segment++;
    break;
    case C:
      digitalWrite(5, HIGH); 
      digitalWrite(2, LOW); 
      digitalWrite(3, LOW); 
      digitalWrite(4, LOW); 
      segment++; 
      state = A; 
    break; 
  }
 
  if (segment > (count/2)) { // end bar at count
    segment = 0; 
    count++; 
    state = RESET; 
  }
 
  if (count > 400) { 
    count = 0;
  }
 
}

/*int P1=D2;
int P2=D3;
int P3=D4; //Also LED pin :/
int R=D5;

int A1=D7;
int A2=D8;


#define ANODE_ON LOW
#define ANODE_OFF HIGH
#define CATHODE_ON HIGH
#define CATHODE_OFF LOW

void setup() {
  Serial.begin(115200);
//all pins to output
pinMode(P1, OUTPUT);
pinMode(P2, OUTPUT);
pinMode(P3, OUTPUT);
pinMode(R, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);

//all phase pins to low turns on
digitalWrite(P1,CATHODE_OFF);
digitalWrite(P2,CATHODE_OFF);
digitalWrite(P3,CATHODE_OFF);
digitalWrite(R, CATHODE_OFF);

//anodes on!
digitalWrite(A1, ANODE_ON);
digitalWrite(A2, ANODE_ON);
}

#define PHASOR_DELAY_MICROSECONDS 70
#define RESET_DELAY_MICROSECONDS 140

uint8_t segmentCounter = 0; //continuously runing from 0 to 100.
unsigned long nextPhaseAtMicros = 0;

uint8_t target_1=0;
uint8_t target_2=0;

unsigned long nextRetargeting=0;
int delta=1;
void loop() {
// put your main code here, to run repeatedly:

if(millis()>nextRetargeting){
  if(target_1>99) delta=-1;
  if(target_1==0) delta=1;
  target_1+=delta;
  target_2=target_1;
  nextRetargeting=millis()+5;
  }

if ( micros() > nextPhaseAtMicros)  
  {
    phasor();  //phasor runs at 70 hz = Every 14 miliseconds (counts to 100 in 1.40 seconds)
    //segmentCounter=segmentCounter%100; //keep going  from 0 to 99 (1-100)
    if(segmentCounter==100){
      segmentCounter=0;
      reset();
    }
    nextPhaseAtMicros=micros()+PHASOR_DELAY_MICROSECONDS;
  }  
}
 
void phasor()
{
    digitalWrite(A1,ANODE_OFF);
    digitalWrite(A2,ANODE_OFF);

//delayMicroseconds(3);

//Every third count comes back to the same state.
  switch ( segmentCounter%3 ){ 
    case 0:
      digitalWrite(P1, CATHODE_ON);
      digitalWrite(P2, CATHODE_OFF);
      digitalWrite(P3, CATHODE_OFF);
      break;
    case 1:
      digitalWrite(P1, CATHODE_OFF);
      digitalWrite(P2, CATHODE_ON);
      digitalWrite(P3, CATHODE_OFF);
      break;
    case 2:
      digitalWrite(P1, CATHODE_OFF);
      digitalWrite(P2, CATHODE_OFF);
      digitalWrite(P3, CATHODE_ON);
      break;
    default: //should never happen, but here we go anyway... 
      break;
  }
  
  //Pulse the Anodes:
  if( target_1 < segmentCounter) digitalWrite(A1,ANODE_ON);
  if( target_2 < segmentCounter) digitalWrite(A2,ANODE_ON);

  segmentCounter++;
}

void reset(){
 //All phases to 0:
      digitalWrite(P1,CATHODE_OFF);
      digitalWrite(P2,CATHODE_OFF);
      digitalWrite(P3,CATHODE_OFF);

      //Pulse the reset pin:
      digitalWrite(R, CATHODE_ON);
      delayMicroseconds(RESET_DELAY_MICROSECONDS);
      digitalWrite(R, CATHODE_OFF);
}
*/
