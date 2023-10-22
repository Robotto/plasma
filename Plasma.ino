int P1 = D1;
int P2 = D2;
int P3 = D3; //Also LED pin :/
int R  = D0;
int A1 = D7;
int A2 = D8;


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
  pinMode(R,  OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  //all phase pins off
  digitalWrite(P1, CATHODE_OFF);
  digitalWrite(P2, CATHODE_OFF);
  digitalWrite(P3, CATHODE_OFF);
  digitalWrite(R,  CATHODE_OFF);

  //anodes on!
  digitalWrite(A1, ANODE_ON);
  digitalWrite(A2, ANODE_ON);
}

#define PHASOR_DELAY_MICROSECONDS 70
#define RESET_DELAY_MICROSECONDS 140

uint8_t segmentCounter = 0; //continuously runing from 0 to 199.
unsigned long nextPhaseAtMicros = 0;

int target_1=0;
int target_2=0;

 int frq=1;
 int offset = 100;
 int amplitude = 100;

void loop() {

  target_1 = (amplitude * sin(2 * PI * frq * micros() * 0.000001) + offset);
  target_2 = (amplitude * cos(2 * PI * frq * micros() * 0.000001) + offset);

  if ( micros() > nextPhaseAtMicros) phasor();
}
 
void phasor()
{
  if(segmentCounter==200){
      
      segmentCounter=2;

      //All phases to 0:
      digitalWrite(P1, CATHODE_OFF);
      digitalWrite(P2, CATHODE_OFF);
      digitalWrite(P3, CATHODE_OFF);

      //Pulse the reset pin:
      digitalWrite(R, CATHODE_ON);
      delayMicroseconds(PHASOR_DELAY_MICROSECONDS);

      digitalWrite(A1, ANODE_ON);
      digitalWrite(A2, ANODE_ON);
  }
//Every third count comes back to the same state.
else{
  digitalWrite(R, CATHODE_OFF);

  switch ( segmentCounter%3 ){ 
    case 0:
      digitalWrite(P1, CATHODE_ON );
      digitalWrite(P2, CATHODE_OFF);
      digitalWrite(P3, CATHODE_OFF);
      break;
    case 1:
      digitalWrite(P1, CATHODE_OFF);
      digitalWrite(P2, CATHODE_ON );
      digitalWrite(P3, CATHODE_OFF);
      break;
    case 2:
      digitalWrite(P1, CATHODE_OFF);
      digitalWrite(P2, CATHODE_OFF);
      digitalWrite(P3, CATHODE_ON );
      break;
    default: //should never happen, but here we go anyway... 
      break;
  }
  
  if( target_1 < segmentCounter) digitalWrite(A1, ANODE_OFF);
  if( target_2 < segmentCounter) digitalWrite(A2, ANODE_OFF);
}
  segmentCounter++;
  nextPhaseAtMicros = micros() + PHASOR_DELAY_MICROSECONDS;  
}

