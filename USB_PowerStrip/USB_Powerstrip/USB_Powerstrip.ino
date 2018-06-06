#include "MillisTimer.h"


#define RELAY1 10
#define RELAY2 16

#define LED_POWER  8
#define LED_RELAY1 9
#define LED_RELAY2 7

#define LED1 9

char buffer[10];
char bufptr=0;

MillisTimer timer1 = MillisTimer(10);
int commTimer=0;
int powerblink=0;
char lastChar=0xff;
char checkserial=1;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(19200);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);


  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  
  pinMode(LED_RELAY1, OUTPUT);
  pinMode(LED_RELAY2, OUTPUT);
  pinMode(LED_POWER, OUTPUT);
  
  digitalWrite(LED_POWER, HIGH);
  timer1.setInterval(10);
  timer1.expiredHandler(resetComms);
  timer1.start();
  
}

// the loop function runs over and over again forever
void loop() {

   timer1.run();


}


void do_serial()
{
   int rxCount;
   int inChar;
  
   rxCount = Serial.available();
   if (rxCount > 0)
   {
          inChar = Serial.read();
          
          if (inChar == -1)
          {
            digitalWrite(LED_POWER, LOW);
            return;
          }
            
          lastChar=inChar;
          
          blink();
          commTimer=10;
          if ((inChar == 13) || (inChar == 10))
          {

            if (bufptr < 5)
                {
                  bufptr=0;
                  return;
                }

            if (memcmp(buffer,"R1_ON",5) == 0)
             {
                digitalWrite(RELAY1, LOW);
                digitalWrite(LED_RELAY1, HIGH);
                Serial.write("\r\nOK\r\n");
                commTimer=-1;
             }

            if (memcmp(buffer,"R1_OF",5) == 0)
              {
                digitalWrite(RELAY1, HIGH);
                digitalWrite(LED_RELAY1, LOW);
                Serial.write("\r\nOK\r\n");
                commTimer=-1;
              }
            
            if (memcmp(buffer,"R2_ON",5) == 0)
               {
                digitalWrite(RELAY2, LOW);
                digitalWrite(LED_RELAY2, HIGH);
                Serial.write("\r\nOK\r\n");
                commTimer=-1;
               }

            if (memcmp(buffer,"R2_OF",5) == 0)
               { 
                digitalWrite(RELAY2, HIGH);
                digitalWrite(LED_RELAY2, LOW);
                Serial.write("\r\nOK\r\n");    
                commTimer=-1;
               }
    
            bufptr=0;
          } else
          {
            buffer[bufptr] = inChar;
            bufptr++;
            if (bufptr >= 10)
               bufptr=0;
          }
     
       rxCount=0;      
     }   

}



void resetComms(MillisTimer &mt)
{

  do_serial();
  
  powerled();
  if (commTimer>0)
  {
   commTimer--;
  } else
  {
    if (commTimer==0)
     {
       bufptr=0;
       Serial.write("TIMEOUT\n");
     }

    commTimer=-1;
  }

}

void blink(void)
{
  powerblink=5;
  digitalWrite(LED_POWER, LOW);
}

void powerled(void)
{
  if (powerblink > 0)
   {
    powerblink--;
   } else
   {
    digitalWrite(LED_POWER, HIGH); 
   }
  
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
}  
