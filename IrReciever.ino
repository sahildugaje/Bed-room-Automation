#include <IRremote.h>
int input_pin = 8; //set D10 as input signal pin
int fan = 3;
int light = 2;
unsigned long prev, current;
IRrecv irrecv(input_pin);
decode_results signals;
void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // enable input from IR receiver
    pinMode(light, OUTPUT);
    pinMode(fan, OUTPUT);
    digitalWrite(light,HIGH);
    digitalWrite(fan,HIGH);
}
int flag = 0;
int flag1 = 0;
void loop() {
if (irrecv.decode(&signals)) {
        Serial.println(signals.value);
        if((signals.value == 1345799060 and flag == 0) or (signals.value == 551535420 and flag == 0)){
          digitalWrite(light,LOW);
          flag = ~flag;
          delay(500);
        }
        else if((signals.value == 1345799060 and flag == -1) or (signals.value == 551535420 and flag == -1)){
          digitalWrite(light,HIGH);
          flag = ~flag;
          delay(500);
        }
        if((signals.value == 2283296306 and flag1 == 0) or (signals.value == 551519100 and flag1 == 0)){
          digitalWrite(fan,LOW);
          flag1 = ~flag1;
          delay(500);
        }
        else if((signals.value == 2283296306 and flag1 == -1) or (signals.value == 551519100 and flag1 == -1)){
          digitalWrite(fan,HIGH);
          flag1 = ~flag1;
          delay(500);
        }
        if(((signals.value == 1253111734 ) or (signals.value == 551502780)) and flag == 0){
          prev=millis();
          digitalWrite(light,LOW);
          delay(1000);
          digitalWrite(light,HIGH);
        }
        if(((signals.value == 1253111734 ) or (signals.value == 551502780)) and flag == -1){
          prev=millis();
          digitalWrite(light,HIGH);
          delay(1000);
          digitalWrite(light,LOW);
        }
        
        irrecv.resume(); // get the next signal
    }
    current= millis();
        if(current-prev >= 600000 and current-prev <= 601000){
          if(flag == 0){
            digitalWrite(light,LOW); 
            delay(1100);
          }
          else if(flag == -1){
          digitalWrite(light,HIGH); 
          delay(1100);   
          }
          flag = ~flag;
        }
    Serial.println(flag);
}
