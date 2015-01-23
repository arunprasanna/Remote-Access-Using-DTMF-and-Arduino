int val[]={B00111111,B00000110,B01011011,B01001111,B01100110, B01101101,B01111101, B00000111, B01111111, B01101111};

void setup()
{
  DDRD = B11111111;
}

void loop()
{
  for(int i=0; i<10;i++)
  {
    PORTD = val[i];
    delay(1000);
  }
}
