int P1=D2;
int P2=D3;
int P3=D4;
int R=D5;

void setup() {
  // put your setup code here, to run once:
//all pins to output
pinMode(P1,OUTPUT);
pinMode(P2,OUTPUT);
pinMode(P3,OUTPUT);
pinMode(R, OUTPUT);

//all pins to low
digitalWrite(P1,LOW);
digitalWrite(P2,LOW);
digitalWrite(P3,LOW);
digitalWrite(R, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  //phasor runs at 70 hz = Every 14 miliseconds (counts to 100 in 1.40 seconds)

  delayMicroseconds(140);
  phasor();  

}


void phasor()
{
  static uint8_t segmentCounter=0;

segmentCounter%100; //keep it going from 0-99

//reset pulse duration: 140uS
  if(segmentCounter==0){
    digitalWrite(R,HIGH);
    delayMicroseconds(140);
    digitalWrite(R,LOW);
  }

  switch (segmentCounter%3){ //Every third count comes back to the same state.
    case 0:
      digitalWrite(P1,HIGH);
      digitalWrite(P3,LOW);
      break;
    case 1:
      digitalWrite(P1,LOW);
      digitalWrite(P2,HIGH);   
      break;
    case 2:
      digitalWrite(P2,LOW);
      digitalWrite(P3,HIGH);
      break;
    default:
      break;
  }
  delayMicroseconds(70);
  segmentCounter++;
}