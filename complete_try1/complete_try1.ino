byte seven_seg_digits[13][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                                           { 0,1,1,0,0,0,0 },  // = 1
                                                           { 1,1,0,1,1,0,1 },  // = 2
                                                           { 1,1,1,1,0,0,1 },  // = 3
                                                           { 0,1,1,0,0,1,1 },  // = 4
                                                           { 1,0,1,1,0,1,1 },  // = 5
                                                           { 1,0,1,1,1,1,1 },  // = 6
                                                           { 1,1,1,0,0,0,0 },  // = 7
                                                           { 1,1,1,1,1,1,1 },  // = 8
                                                           { 1,1,1,0,0,1,1 },  //9
                                                            { 1,1,1,1,1,1,0 }, //0
                                                           { 1,1,1,0,1,1,1 }, //asterix
                                                           { 0,1,1,0,1,1,1 }, //hash
                                                           };
byte val = 0;
void setup() {                
  pinMode(7, OUTPUT);   
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(2,INPUT); // Steered delay Pin (INT 0)
  pinMode(3,INPUT); // q1
  pinMode(4,INPUT); // q2
  pinMode(5,INPUT); // q3
  pinMode(1,INPUT); // q4
  attachInterrupt(0,dtmf,RISING);
 
}


    
void sevenSegWrite(byte digit) {
  byte pin = 7;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  {
   val=0;
   
  }
  
}

void dtmf() // the ISR - this function is called everytime a RISING interrupt occurs on PIN 2 (INT 0)
  {
    
    for(int i=0;i<3;i++) // Once we receive an Interrupt, we need to read each of q1 to q4, with q1 being the LSB and q4 the MSB
    {
      if(digitalRead(i+3)==1)// check if the pin is 1 or 0, if 1 then we need to process for binary to decimal conversion
      {
        val = val + (1<<i); // Binary to decimal conversion
      }
    
   }
   
   int i=3;
   if(digitalRead(1)==1) // Pin Number 6 is not working on the microcontroller. The fourth bit has been given as input to pin number 1.
   {
     val = val + (1<<i);
   }
    sevenSegWrite(val); 
  }
