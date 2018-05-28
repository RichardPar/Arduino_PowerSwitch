

#define RELAY1 10
#define RELAY2 16

#define LED_POWER  8
#define LED_RELAY1 7
#define LED_RELAY2 9

char buffer[10];
char bufptr=0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(19200);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);


  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  
  pinMode(LED_RELAY1, OUTPUT);
  pinMode(LED_RELAY2, OUTPUT);
  pinMode(LED_POWER, OUTPUT);
  
  digitalWrite(LED_POWER, HIGH);
  
}

// the loop function runs over and over again forever
void loop() {


   while (Serial.available() > 0)
   {
     if (bufptr < 10)
      {
          buffer[bufptr] = Serial.read();
          if (buffer[bufptr] == '\n')
          {

            if (memcmp(buffer,"R1_ON\n",6) == 0)
             {
                digitalWrite(RELAY1, LOW);
                digitalWrite(LED_RELAY1, HIGH);
                Serial.write("OK\r\n");
             }

            if (memcmp(buffer,"R1_OFF\n",7) == 0)
              {
                digitalWrite(RELAY1, HIGH);
                digitalWrite(LED_RELAY1, LOW);
                Serial.write("OK\r\n");
              }
            
            if (memcmp(buffer,"R2_ON\n",6) == 0)
               {
                digitalWrite(RELAY2, LOW);
                digitalWrite(LED_RELAY2, HIGH);
                Serial.write("OK\r\n");
               }

            if (memcmp(buffer,"R2_OFF\n",7) == 0)
               { 
                digitalWrite(RELAY2, HIGH);
                digitalWrite(LED_RELAY2, LOW);
                Serial.write("OK\r\n");    
               }
    
            bufptr=0;
          } else
          bufptr++;  
      } else
        bufptr=0; // reset to zero as its bigger tgan the buffer


    
   }

      // wait for a second
}
