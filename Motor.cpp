#include <Arduino.h>
#include "Motor.h"


Motor::Motor(byte pin1, byte pin2, byte pin3, byte pin4){
  in1 = pin1;
  in2 = pin2;
  in3 = pin3;
  in4 = pin4;
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void Motor::RunForward(int obor, int dl){
  Serial.print("Run forward drive, oborotov: ");
  Serial.println(obor);
  int r = 1000;
  for(int i = 0; i < obor*512; i++)
    {
      r = r - 1;
      if(i < 250){
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, HIGH );
        delay(dl);

        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl);

        digitalWrite( in1, LOW ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl);

        digitalWrite( in1, LOW ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);

        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);

        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);

        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl);

        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl);

      }
      else{
        digitalWrite( in1, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl*2);
      
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl*2);
      
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, LOW ); 
        delay(dl*2);
      
        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, LOW ); 
        delay(dl*2);
        }
    }
    digitalWrite( in1, LOW ); 
    digitalWrite( in2, LOW ); 
    digitalWrite( in3, LOW ); 
    digitalWrite( in4, LOW );
  }

void Motor::RunBack(int obor, int dl){
  Serial.print("Run back drive, oborotov: ");
  Serial.println(obor);
  for(int i = 0; i < obor*512; i++)
    {
      if(i < 128){
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, HIGH );
        delay(dl);
      
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl);
      
        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl);
      
        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);
      
        digitalWrite( in1, HIGH ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);
      
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
        delay(dl);
      
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, HIGH ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl);
      
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl);
      }
      else{
        digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
        delay(dl*2);
      
        digitalWrite( in1, HIGH ); 
        digitalWrite( in4, LOW );
        delay(dl*2);
      
        digitalWrite( in1, LOW ); 
        digitalWrite( in2, HIGH ); 
        delay(dl*2);
      
        digitalWrite( in2, LOW ); 
        digitalWrite( in3, HIGH ); 
        delay(dl*2);
        }
    }
    digitalWrite( in1, LOW ); 
    digitalWrite( in2, LOW ); 
    digitalWrite( in3, LOW ); 
    digitalWrite( in4, LOW );
  }

