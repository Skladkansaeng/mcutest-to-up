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

bool readDiv(){
  bool swDiv = false;
  for(int8_t i=0;i<8;i++){
      swDiv |= mcp.digitalRead(i);
  }
  #ifdef useMCP
    swDiv |= mcp.digitalRead(swReset);

    swDiv |= mcp.digitalRead(swMode);

    swDiv |= mcp.digitalRead(swFormat);
  # else
    swDiv |= digitalRead(swReset);

    swDiv |= digitalRead(swMode);

    swDiv |= digitalRead(swFormat);
  #endif
    return swDiv;
}

void loop() {
  if(readDiv()){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
  delay(delayLoop);
}