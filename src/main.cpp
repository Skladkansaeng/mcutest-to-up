#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#define swReset D1
#define swMode D2
#define swFormat D3
#define ledPin LED_BUILTIN
#define delayLoop 0
// #define useMCP  // if connet all pin in mcp uncomment this code
Adafruit_MCP23017 mcp;

void setup()
{
  mcp.begin(0);
  for (uint8 i = 0; i < 16; i++)
  {
    mcp.pinMode(i, INPUT);
  }
  Serial.begin(9600);
#ifdef useMCP
  pinMode(swReset, INPUT);
  pinMode(swMode, INPUT);
  pinMode(swFormat, INPUT);
#endif
  pinMode(ledPin, OUTPUT);
}

bool readDip()
{
  bool swDip = false;
  Serial.print("Dip switch :");
  for (int8_t i = 0; i < 8; i++)
  {
    swDip |= mcp.digitalRead(i);
    Serial.print(swDip);
    Serial.print(" ");
  }
  Serial.println();
#ifdef useMCP
  swDip |= mcp.digitalRead(swReset);
  Serial.print(swDip);
  Serial.print(" ");
  swDip |= mcp.digitalRead(swMode);
  Serial.print(swDip);
  Serial.print(" ");
  swDip |= mcp.digitalRead(swFormat);
  Serial.print(swDip);
  Serial.print(" ");
#else
  swDip |= digitalRead(swReset);
  Serial.print(swDip);
  Serial.print(" ");
  swDip |= digitalRead(swMode);
  Serial.print(swDip);
  Serial.print(" ");
  swDip |= digitalRead(swFormat);
  Serial.print(swDip);
  Serial.print(" ");
#endif
  return swDip;
}

void loop()
{
  if (readDip())
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  delay(delayLoop);
}