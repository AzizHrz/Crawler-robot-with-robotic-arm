#include <Psx.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


 

#define dataInput 6
#define commandPin 3
#define attentionPin 2
#define clockSignal 5

Psx controller;

byte transmissionData[8];
byte receiverAddress[5] = {0xD0, 0xD0, 0xD0, 0xD0, 0xD0};

void setup()
{
  Serial.begin(57600);
  controller.setupPins(dataInput, commandPin, attentionPin, clockSignal, 10);
  Mirf.csnPin = 10;
  Mirf.cePin = 9;

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = 8;
  Mirf.config();
  Serial.println("Starting system ... ");   
 
}

void loop()
{
  controller.read();

  if(controller.psxID != 0x00)
  {
    transmissionData[0] = controller.psxID; // DIGITAL (82) , ANALOG (CE)
    transmissionData[1] = controller.psxStatus;
    transmissionData[2] = controller.psxThumbL; // D-Pad, SELECT, DIGITAL L
    transmissionData[3] = controller.psxThumbR; // (X, [], /\, O), START, DIGITAL R, (L1, L2, R1, R2)
    transmissionData[4] = controller.psxJoyRX; // Analog X-axis of Right Joystick
    transmissionData[5] = controller.psxJoyRY; // Analog Y-axis of Right Joystick
    transmissionData[6] = controller.psxJoyLX; // Analog X-axis of Left Joystick
    transmissionData[7] = controller.psxJoyLY; // Analog Y-axis of Left Joystick

   
      Serial.print("Data 2 ==> ");
      Serial.println(transmissionData[2]);
      Serial.print("Data 3 ==> ");
      Serial.println(transmissionData[3]);
      Serial.print("Data 4 ==> ");
      Serial.println(transmissionData[4]);
      Serial.print("Data 5 ==> ");
      Serial.println(transmissionData[5]);
      Serial.print("Data 6 ==> ");
      Serial.println(transmissionData[6]);
      Serial.print("Data 7 ==> ");
      Serial.println(transmissionData[7]);

    Mirf.setTADDR(receiverAddress);
    Mirf.send(transmissionData);
    while(Mirf.isSending());
  }
  
 
  delay(50);
}
