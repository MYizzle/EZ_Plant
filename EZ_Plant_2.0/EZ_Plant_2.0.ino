#include <JeeLib.h>
#include <Servo.h>

Port Water = Port(1);
Port Bright = Port(2);
//Port Motor1 = Port(3);
//Port Motor2 = Port(4);

Servo myservo;
Servo mikeservo;
int pos= 0;
int LDR_pin=0;


void setup (){
  Serial.begin(115200);
  Serial.println("Initiating EZ Plant");
 // myservo.attach(Motor1.digiWrite());
  Serial.println("Begininning the servo motor");
  myservo.attach(6);
  mikeservo.attach(4);
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {

  //Moisture Sensor /////////
  int moisture;
  moisture = Water.anaRead();
  Serial.println(" ");
  Serial.println("moisture");
  Serial.println(moisture);
  Serial.println(" ");
  int tic =0;

  //Light Sensor ////////////
  double raw_value;
  raw_value = Bright.anaRead();
  double lux;
  lux = exp((0.02312*raw_value) + 0.05501);
  Serial.println("lux value");
  Serial.println(lux);

  //Arteficial Light
  if (lux > 10000){
    Bright.digiWrite(HIGH);
    //digitalWrite(4,HIGH);
    
  }
  else{
    Bright.digiWrite(LOW);
  }

  //Plant Spinning Servo

  
  if(lux > 10000){
   //mikeservo.writeMicroseconds(4000);
    for(pos =0; pos<= 180; pos += 1){
    mikeservo.write(pos);
    delay(1000);
  }
  for( pos=180; pos >=0; pos-=1){
    mikeservo.write(pos);
    delay(1000);
  }
  //  mikeservo.writeMicroseconds(100);
  }


  //Sun Shading Servo
    if(lux > 200000){
  
  myservo.writeMicroseconds(4000);
 
  }else{
  
  myservo.writeMicroseconds(100);
  }
  delay(500);

  
}
