int val=0;// A variable to store the value calculated based on the binary inputs q1 to q4

const int set_pass[]={1,11,10,2}; // The DTMF Value for 4 Digits of Password [Remember in DTMF Values 0 => 10, * =>11 & #=> 12]

int recvd_pass[4]; // a variable to store the password received

boolean login_flag = 0; // a flag variable to store the log in status of the user

int count = 0; // a variable to count the number of digits entered

long int first_press_time = 0; // a variable to store the time from the first button press

void setup()
{
  pinMode(2,INPUT); // Steered delay Pin (INT 0)
  pinMode(3,INPUT); // q1
  pinMode(4,INPUT); // q2
  pinMode(5,INPUT); // q3
  pinMode(6,INPUT); // q4
  attachInterrupt(0,dtmf,RISING); // Enable the Interrupt Pin, associate it with the ISR dtmf and configure it to trigger on a RISING interrupt
  Serial.begin(9600); // Enable Serial Communication for debugging

  pinMode(11,OUTPUT); // LED for login indication
  pinMode(12,OUTPUT); // LED for Reset indication
  pinMode(13,OUTPUT); // LED for controlling
}

void loop()
{
  // If there is a new value received print it to serial monitor for debugging
  if(val>0)
  {
    Serial.println(val);
  }
  
  // Check for Reset Conditions - Either time from first press is more than 5 seconds or the user has pressed the '#' key in the logged out mode
  
  if((count>0 && (millis()-first_press_time)>5000)||(login_flag==0 && val==12))
  {
    count = 0; // reset count
    Serial.println("RESET"); // print reset message
    val = 0; // reset val to '0' as so that we can distinguish when a new value is received.
    digitalWrite(12,HIGH); // led indication for reset
    delay(1000);
    digitalWrite(12,LOW);
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
    Serial.print("Count : ");Serial.println(count); // print count value for debug
    if(count==4) // if count is 4, then we need to match the password received to the passwors stored
    {
      if(recvd_pass[0]==set_pass[0] && recvd_pass[1]==set_pass[1] && recvd_pass[2]==set_pass[2] && recvd_pass[3]==set_pass[3]) // check if passwords match
      {
        login_flag = 1; // if matched set the login flag
        digitalWrite(11,HIGH); // and turn on the indication led
      }
      else
      {
        digitalWrite(12,HIGH); // if passwords dont match, show the reset indication
        delay(1000);
        digitalWrite(12,LOW);
      }
      count = 0;// on reaching 4, count has to be reset to 0
    }
  }



// logged in activities
  if(login_flag==1) // if the user is logged in then the keys pressed are treated differently
  {
    switch(val) // check which key is pressed
    {
      case 1: digitalWrite(13,HIGH); break; // turn on the 13th pin led when '1' is pressed
      case 10: digitalWrite(13,LOW); break;// turn off the 13th pin led when '0' is pressed
      case 12: digitalWrite(11,LOW); login_flag=0; break; // Log out the user, set the login flag to false and turn off the login status led
    }
    val = 0; // reset val to '0'
  }

  }

  void dtmf() // the ISR - this function is called everytime a RISING interrupt occurs on PIN 2 (INT 0)
  {
    
    for(int i=0;i<4;i++) // Once we receive an Interrupt, we need to read each of q1 to q4, with q1 being the LSB and q4 the MSB
    {
      if(digitalRead(i+3)==1)// check if the pin is 1 or 0, if 1 then we need to process for binary to decimal conversion
      {
        val = val + (1<<i); // Binary to decimal conversion
      }
    } 
  }
