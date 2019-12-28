#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#define swReset D1
#define swMode D2
#define swFormat D3
#define ledPin LED_BUILTIN
#define delayLoop 0
// #define useMCP  // if connet all pin in mcp uncomment this code
Adafruit_MCP23017 mcp;

void setup() {
  mcp.begin(0);
  for(uint8 i=0;i<16;i++){
    mcp.pinMode(i,INPUT);
  }

  #ifdef useMCP
  pinMode(swReset,INPUT);
  pinMode(swMode,INPUT);
  pinMode(swFormat,INPUT);
  #endif  
  pinMode(ledPin,OUTPUT);
}

uint8_t readDiv(){
  uint16_t swDiv =0 ;
  for(int8_t i=0;i<8;i++){
      swDiv &= mcp.digitalRead(i);
      swDiv <<= 1
  }
  #ifdef useMCP
    swDiv &= mcp.digitalRead(swReset);
    swDiv <<= 1;
    swDiv &= mcp.digitalRead(swMode);
    swDiv <<= 1;
    swDiv &= mcp.digitalRead(swFormat);
  # else
    swDiv &= digitalRead(swReset);
    swDiv <<= 1;
    swDiv &= digitalRead(swMode);
    swDiv <<= 1;
    swDiv &= digitalRead(swFormat);
  #endif
    return swDiv;
}

void loop() {
  if(readDiv() != ){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
  delay(delayLoop);
}