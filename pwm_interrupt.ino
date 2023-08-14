byte last_ch[7];
int rx_ch[7];
unsigned long timer[7];
void setup() {
  PCICR|=(1<<PCIE0);// pin change interrupt for DIGITAL PINS ON MEGA 50-53 10-13
 // PCICR|=(1<<PCIE1);// pin change interrupt for DIGITAL PINS ON MEGA
  PCMSK0=0b11110011;//enables interrupt for digital pins 10 11 12 13 52 53
  //PCMSK1=0b00000110;//enables interrupt for digital pins 14 15
  Serial.begin(9600);
}

void loop() {
  Serial.print(rx_ch[1]);
  Serial.print("  ");
  Serial.print(rx_ch[2]);
  Serial.print("  ");
  Serial.print(rx_ch[3]);
  Serial.print("  ");
  Serial.println(rx_ch[4]);
  /*Serial.print("  ");
  Serial.print(rx_ch[5]);
  Serial.print("  ");
  Serial.println(rx_ch[6]);/**/}
ISR(PCINT0_vect){
  ///////////////////channel 1 /////////////////////
  if(last_ch[1]==0 && (PINB & 0b10000000))           //checking state of digital pin 13
  {
    last_ch[1]=1;
    timer[1]=micros();
    }
 else if(last_ch[1]==1 && !(PINB & 0b10000000))
  {
    last_ch[1]=0;
    rx_ch[1]=micros()-timer[1];
   }
   ///////////////////channel 2 ////////////////////
  if(last_ch[2]==0 && (PINB & 0b01000000))           //checking state of digital pin 14
  {
    last_ch[2]=1;
    timer[2]=micros();
    }
  else if(last_ch[2]==1 && !(PINB & 0b01000000))
  {
    last_ch[2]=0;
    rx_ch[2]=micros()-timer[2];
   }
    ///////////////////channel 3 /////////////////////
  if(last_ch[3]==0 && (PINB & 0b00100000))           //checking state of digital pin 11
  {
    last_ch[3]=1;
    timer[3]=micros();
    }
  else if(last_ch[3]==1 && !(PINB & 0b00100000))
  {
    last_ch[3]=0;
    rx_ch[3]=micros()-timer[3];
   }
    ///////////////////channel 4 /////////////////////
  if(last_ch[4]==0 && (PINB & 0b00010000))           //checking state of digital pin 10
  {
    last_ch[4]=1;
    timer[4]=micros();
    }
  else if(last_ch[4]==1 && !(PINB & 0b00010000))
  {
    last_ch[4]=0;
    rx_ch[4]=micros()-timer[4];
   }
    ///////////////////channel 5 /////////////////////
  if(last_ch[5]==0 && (PINB & 0b00000010))           //checking state of digital pin 52
  {
    last_ch[5]=1;
    timer[5]=micros();
    }
 else if(last_ch[5]==1 && !(PINB & 0b00000010))
  {
    last_ch[5]=0;
    rx_ch[5]=micros()-timer[5];
   }
    ///////////////////channel 6 /////////////////////
  if(last_ch[6]==0 && (PINB & 0b00000001))           //checking state of digital pin 53
  {
    last_ch[6]=1;
    timer[6]=micros();
    }
  else if(last_ch[6]==1 && !(PINB & 0b00000001))
  {
    last_ch[6]=0;
    rx_ch[6]=micros()-timer[6];
   }
   
  }
  
