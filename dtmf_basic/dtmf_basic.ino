int val=0;// A variable to store the value calculated based on the binary inputs q1 to q4

void setup()
{
  pinMode(2,INPUT); // Steered delay Pin (INT 0)
  pinMode(3,INPUT); // q1
  pinMode(4,INPUT); // q2
  pinMode(5,INPUT); // q3
  pinMode(6,INPUT); // q4
  //attachInterrupt(0,dtmf,RISING); // Enable the Interrupt Pin, associate it with the ISR dtmf and configure it to trigger on a RISING interrupt
  Serial.begin(9600); // Enable Serial Communication
}

void loop()
{                         

  {
   Serial.print(val); // print the new value to the serial monitor
   delay(1000);
   val = val + 1; // reset tvoid dtmf() // the ISR - this function is called everytime a RISING interrupt occurs on PIN 2 (INT 0)
  }
}
