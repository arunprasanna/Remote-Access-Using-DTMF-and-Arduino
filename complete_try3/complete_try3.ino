const byte set_pass[]={1,2,3,4}; // The DTMF Value for 4 Digits of Password [Remember in DTMF Values 0 => 10, * =>11 & #=> 12]

byte recvd_pass[4]; // a variable to store the password received

boolean login_flag = 0; // a flag variable to store the log in status of the user

int count = 0; // a variable to count the number of digits entered

long int first_press_time = 0; // a variable to store the time from the first button press

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
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
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

void loop() 
  {
  
  // Check for Reset Conditions - Either time from first press is more than 5 seconds or the user has pressed the '#' key in the logged out mode
  
   if((count>0 && (millis()-first_press_time)>5000)||(val==12))
   {
     count = 0; // reset count
     val = 0; // reset val to '0' as so that we can distinguish when a new value is received.
     sevenSegWrite(val);  // led indication for reset
     login_flag=0;
   }
  
   //Get four digit input to check for login, ensure that the user is not already logged in and that 4 digits have not been input already.
   if(login_flag==0 && count< 4 && val>0)
   {
     recvd_pass[count] = val; // store the value into an array for comparing once all the 4 digits are received
     val = 0; // reset val to '0' as so that we can distinguish when a new value is received.
     if(count==0) // if this is the first key press then store the time for calculating time out
     {
       first_press_time = millis();
     }
     count++; // increment count 
     if(count==4) // if count is 4, then we need to match the password received to the passwors stored
     {
       if(recvd_pass[0]==set_pass[0] && recvd_pass[1]==set_pass[1] && recvd_pass[2]==set_pass[2] && recvd_pass[3]==set_pass[3]) // check if passwords match
       {
         login_flag = 1; // if matched set the login flag
       }
       else
       {
         val = 0; // reset val to '0' as so that we can distinguish when a new value is received.
         sevenSegWrite(val);  // led indication for reset
       }
       count = 0;// on reaching 4, count has to be reset to 0
     }
  }

 if(login_flag==1) // if the user is logged in then the keys pressed are treated differently
   {
     {
       sevenSegWrite(val);
       { 
         switch(val) // check which key is pressed
          {
           case 1: digitalWrite(A0,HIGH);digitalWrite(A1,HIGH);digitalWrite(A3,HIGH);digitalWrite(A4,HIGH); break; 
           case 2: digitalWrite(A0,HIGH);digitalWrite(A1,HIGH);digitalWrite(A3,HIGH); break;
           case 3: digitalWrite(A1,HIGH);digitalWrite(A3,HIGH);digitalWrite(A4,HIGH); break;
           case 4: digitalWrite(13,LOW); login_flag=2; break ;
           case 5: digitalWrite(13,LOW); login_flag=2; break ;
           case 6: digitalWrite(13,LOW); login_flag=2; break ;
           case 7: digitalWrite(13,LOW); login_flag=2; break; 
           //case 12: digitalWrite(11,LOW); login_flag=0; break; 
          }
       }
   
   }
 }
}


void dtmf() // the ISR - this function is called everytime a RISING interrupt occurs on PIN 2 (INT 0)
  { val=0;
    
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
    
  }
