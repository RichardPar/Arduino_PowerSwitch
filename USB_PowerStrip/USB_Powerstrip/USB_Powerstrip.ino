/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/


#define RELAY1 10
#define RELAY2 16

#define LED_POWER  8
#define LED_RELAY1 9
#define LED_RELAY2 7

#define LED1 9

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
   char inChar;

   while (Serial.available() > 0)
   {
     if (bufptr < 10)
      {
          inChar = Serial.read();
          if ((inChar == 13) || (inChar == 10))
          {

            
            if (bufptr < 5)
                {
                  bufptr=0;
                  break;
                }

            if (memcmp(buffer,"R1_ON",5) == 0)
             {
                digitalWrite(RELAY1, LOW);
                digitalWrite(LED_RELAY1, HIGH);
                Serial.write("OK\r\n");
             }

            if (memcmp(buffer,"R1_OFF",6) == 0)
              {
                digitalWrite(RELAY1, HIGH);
                digitalWrite(LED_RELAY1, LOW);
                Serial.write("OK\r\n");
              }
            
            if (memcmp(buffer,"R2_ON",5) == 0)
               {
                digitalWrite(RELAY2, LOW);
                digitalWrite(LED_RELAY2, HIGH);
                Serial.write("OK\r\n");
               }

            if (memcmp(buffer,"R2_OFF",6) == 0)
               { 
                digitalWrite(RELAY2, HIGH);
                digitalWrite(LED_RELAY2, LOW);
                Serial.write("OK\r\n");    
               }
    
            bufptr=0;
          } else
          {
            buffer[bufptr] = inChar;
            bufptr++;
          }  
      } else
        bufptr=0; // reset to zero as its bigger tgan the buffer


    
   }

      // wait for a second
}
