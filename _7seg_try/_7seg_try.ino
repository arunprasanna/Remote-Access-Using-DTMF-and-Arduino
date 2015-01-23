int val[]={B00000000,B11111111};

void setup()
{
  DDRD = B11111111;
}

void loop()
{
  for(int i=0; i<2;i++)
  {
    PORTD = val[i];
    delay(1000);
  }
}

