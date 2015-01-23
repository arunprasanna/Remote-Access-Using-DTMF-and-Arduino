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

  pinMode(9,OUTPUT); // LED for login indication
  pinMode(10,OUTPUT); // LED for Reset indication
  pinMode(11,OUTPUT); // LED for controlling
  pinMode(12,OUTPUT);
}

void loop()

