int val=0;// A variable to store the value calculated based on the binary inputs q1 to q4

void setup()
{
  pinMode(2,INPUT); // Steered delay Pin (INT 0)
  pinMode(3,INPUT); // q1
  pinMode(4,INPUT); // q2
  pinMode(5,INPUT); // q3
  pinMode(6,INPUT); // q4
  attachInterrupt(0,dtmf,RISING); // Enable the Interrupt Pin, associate it with the ISR dtmf and configure it to trigger on a RISING interrupt
  Serial.begin(9600); // Enable Serial Communication
}

void loop()
{
  if(val!=0) // Check if we have received a new value, when a new value is received we print the value and reset it to 0
  {
   Serial.println(val); // print the new value to the serial monitor
   val = 0; // reset the value to 0
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

