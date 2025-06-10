#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <Servo.h>
#include <Stepper.h>

Servo S;
int servo;
#define Servo_PWM 9


byte donnee[8];

byte rx_add[5] = {0xD0, 0xD0, 0xD0, 0xD0, 0xD0};

uint32_t lastCommandTime = 0;

uint8_t data1, data2;

//stepper motor
int i1=A8;
int i2=A9;
int i3=A10;
int i4=A11;



const int STEPS_PER_REV = 200;
Stepper stepper_NEMA17(STEPS_PER_REV, i1, i2, i3, i4);


//servo motor
#define Servo_PWM 10

// Motor R Connections
int Ren = 3;
int Rin1 = A0;
int Rin2 = A1;




// Motor L Connections
int Len = 2;
int Lin1 = A2;
int Lin2 = A3;


//center MOTOR

int Cen = 6;
int Cin = 4;


 
 

uint8_t v ;
uint8_t v2;
uint8_t a ;


void setup()
{
 
 // Mirf.csnPin = 10;-->7 
 // Mirf.cePin = 9;  -->8
  Mirf.csnPin = 49;
  Mirf.cePin = 48;  

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR(rx_add);
  Mirf.payload = 8;
  Mirf.config();
   Serial.begin(57600);
  Serial.println("Listening...");

  pinMode(Ren, OUTPUT);
  pinMode(Rin2, OUTPUT);
  pinMode(Rin1, OUTPUT);

  pinMode(Len, OUTPUT);
  pinMode(Lin1, OUTPUT);
  pinMode(Lin2, OUTPUT);

   pinMode(Cen, OUTPUT);
  pinMode(Cin, OUTPUT);


   S.attach(Servo_PWM);
   // S.write(90);
   

   
   
}

void loop()
{
  
 
  
  if (!Mirf.isSending() && Mirf.dataReady())
  {
    Serial.println("Got packet");
    Mirf.getData(donnee);




    data1 = ~donnee[2];
    data2 = ~donnee[3];
   
   

    /*    data 1
       1 = analogico L para esquerda
       2 = analogico L para baixo
       4 = analogico L para direita
       8 =  analogico L para cima
    */
    /*   data 2
       1 = [] / analogico R para esquerda
       2 = X / analogico R para baixo
       4 = O / analogico R para direita
       8 = /\ / analogico R para cima
       16 = R1
       32 = L1
       64 = R2
       128 = L2
    */

    switch (data2) {
      case 0:
        v = 0;
        v2 = 0;
        
        analogWrite(Cen, 0);
        
         stepper_NEMA17.setSpeed(0);
        
        break;
      case 1:
       analogWrite(Cen, 50);
       digitalWrite(Cin,HIGH); 
        break;
      case 2:
     
       stepper_NEMA17.setSpeed(60);
       stepper_NEMA17.step(STEPS_PER_REV);
       
        break;
      case 4:
      analogWrite(Cen, 50);
       digitalWrite(Cin,LOW); 
        
        break;
      case 8:
        /* stepper_NEMA17.setSpeed(60);
         stepper_NEMA17.step(-STEPS_PER_REV);*/
       
        break;
      case 16: //R1
        

    /*   stepper_NEMA17.setSpeed(60);
       stepper_NEMA17.step(STEPS_PER_REV);*/
 
        break;

      case 32: //L1
      /*  stepper_NEMA17.setSpeed(60);
         stepper_NEMA17.step(-STEPS_PER_REV);*/
        
        break;

      case 64: //R2

  
       /*  Serial.println("servo 20");
          Serial.println(servo);
         servo-=5;
        S.write(servo);
        Serial.println(servo);*/
        
     
        break;

      case 128: //L2
      
    /*   Serial.println("servo 90");
       Serial.println(servo);
       servo+=5;
        S.write(servo);
        Serial.println(servo);*/
        break;
    }
    switch (data1) {
      case 0:
        v = 0;
         analogWrite(Ren, v);
         analogWrite(Len, v);
        break;
      case 1://right
        

        RIGHT();
        analogWrite(Ren, 150);
        analogWrite(Len, 150);
        break;
      case 2:
        

        backward();
        analogWrite(Ren, 150);
        analogWrite(Len, 150);
        break;
      case 4://left
        

        LEFT();
        analogWrite(Ren, 150);
        analogWrite(Len, 150);
        break;
      case 8:
       

        forward();
        analogWrite(Ren, 150);
        analogWrite(Len, 150);
        break;
    }



    Serial.print("Data 1 ==> ");
    Serial.println(data1);
    Serial.print("Data 2 ==> ");
    Serial.println(data2);
    
   

    Mirf.flushRx();
    lastCommandTime = millis();





  }

  if ((millis() - lastCommandTime) > 100)
  {

    Mirf.flushRx();
    lastCommandTime = millis();
    data1 = 0;
    data2 = 0;
    
    Serial.print("Data 1 ==> ");
    Serial.println(data1);
    Serial.print("Data 2 ==> ");
    Serial.println(data2);
    
  }

}
void RIGHT()
{
  digitalWrite(Rin1, HIGH);//A
  digitalWrite(Rin2, LOW);//A

  digitalWrite(Lin1, HIGH);
  digitalWrite(Lin2, LOW);


}
void LEFT()
{
  digitalWrite(Rin1, LOW);//A
  digitalWrite(Rin2, HIGH);//A

  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);

}

void backward()
{
  digitalWrite(Rin1, LOW);//A
  digitalWrite(Rin2, HIGH);//A

  digitalWrite(Lin1, HIGH);
  digitalWrite(Lin2, LOW);

}
void forward()
{
  digitalWrite(Rin1, HIGH);//A
  digitalWrite(Rin2, LOW);//A


  digitalWrite(Lin1, LOW);
  digitalWrite(Lin2, HIGH);

}
