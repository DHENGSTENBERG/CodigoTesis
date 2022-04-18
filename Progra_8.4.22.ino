#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <Servo.h>

#define dirPin 16             //definición de pines
#define stepPin 15
#define stepsPerRevolution 100 //pulso necesario para una vuelta completa del nema
#define fin 8
#define ene 14

//definición de variables 
int derecha;
int izquierda;

int FinalCD=11;
int FinalCI=12;

Servo motorRiel;
Servo motorGarra;
int angulo=motorGarra.read();
int Fin;
int var;
int L=40;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(ene, OUTPUT);
  pinMode(fin, INPUT);
  pinMode(FinalCD, INPUT); 
  pinMode(FinalCI, INPUT);
  
  Serial.begin(9600);
  motorGarra.attach(9,520,2490);
  motorRiel.attach(10);
   var=1;                   //primer paso lo manda Juanpa
   izquierda=1;
   derecha=0;      


      
   
           
}
void loop() {
          

switch(var){
case 0:

//   if (digitalRead(FinalCI)==LOW && angulo==180){         //garra dentro de lado izquierdo
//      motorRiel.write(180);
//      if (digitalRead(FinalCD)==LOW){
//        motorRiel.write(90);
//        //var=0;
//        }
//   }
//
//   if (digitalRead(FinalCI)==LOW && digitalRead(FinalCD)==HIGH && angulo==0){   //garra lado izquierdo 
//      //var=0;
//        
//   }
//
//   if (digitalRead(FinalCD)==LOW && angulo==0){         //garra dentro lado derecho
//      motorRiel.write(0);
//      if (digitalRead(FinalCI)==LOW){
//        motorRiel.write(90);
//        //var=0;
//        }
//   }
//
//   if (digitalRead(FinalCD)==LOW && angulo==180){       //garra lado derecho
//      //var=0;
//        
//   }
//
//    if (digitalRead(FinalCD)==HIGH && digitalRead(FinalCI)==HIGH && angulo ==180){    //garra en el centro viendo a izquierda
//      motorRiel.write(180);
//      if (digitalRead(FinalCD)==LOW){
//        motorRiel.write(90);
//        //var=0;
//        }
//   }
//    if (digitalRead(FinalCD)==HIGH && digitalRead(FinalCI)==HIGH && angulo ==0){      //garra en el centro viendo a derecha
//      motorRiel.write(0);
//      if (digitalRead(FinalCI)==LOW){
//        motorRiel.write(90);
//        //var=0;
//        }
//   }
//
//    if (digitalRead(FinalCD)==HIGH && digitalRead(FinalCI)==HIGH && angulo ==90){     //garra en el centro viendo al frente
//      motorRiel.write(180); 
//      if (digitalRead(FinalCD)==LOW){
//        motorRiel.write(90);
//        //var=0;
//        }
//   }





 digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) { //2*L*steps es el ancho de pulso
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500); //define la velocidad
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=1; 
     
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(1000); 

//  motorRiel.write(40);
//  motorGarra.write(90);
//  delay(1000);

break;
    
case 1:                                     //ESCOGE DIRECCIÓN DE GARRA



  if (derecha==0 && izquierda==1){
    
      if (digitalRead(FinalCD)==LOW){
          motorRiel.write(90);         
          delay(500);
          motorGarra.write(180);
          delay(500);
          var=2;
      }
    else{
      motorRiel.write(180);
      delay(350);
      motorGarra.write(90);  
    }
  }

  if (izquierda==0 && derecha==1){
    
      if (digitalRead(FinalCI)==LOW){
          motorRiel.write(90);
          delay(500);
          motorGarra.write(0);
          delay(500);
          var=2;           
      }
    else{
      motorRiel.write(0);
      delay(350);
      motorGarra.write(90);
    
    }
  }

break;

  
case 2: //SUBE GARRA
//L=93; // nivel 5 con pallet
//L=72; // nivel 4 con pallet
//L=52;  // nivel 3 con pallet
//L=32;  // nivel 2 con pallet
//L=12;   // nivel 1 con pallet
L=93 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {        
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  delay(1000);
  var=3;
  
   
 break;

  case 3:   
  
                                                        //GIRA GARRA A DERECHA/IZQUIERDA Y ENTRA HACIA EL PALLET
  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      delay(1000);
      var=4;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      delay(1000);
      var=4;
      
    }
  else{
    motorRiel.write(180);
    }
  }


  break;

  case 4:
  digitalWrite(dirPin,HIGH); 
  for(int i = 0; i < 400; i++) {
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(1000); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(1000); 
  }
  
  delay(1000);
  var=5;  
   break;



   case 5:   
   //RETIRA PALLET

if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(1000);
    var=6;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    delay(1000);
    var=6;
  }
  else{
    motorRiel.write(0);
    }
  }
  delay(500);



break;



case 6:
 digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=7;     //var 1 se cambió a var 7 para dejar pallets
     //derecha=1;3
     //izquierda=0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(5000);  
   break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
case 7:                                                                         //SUBE HACIA PLATAFORMA A DEJAR PALLET
L=6 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {        
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  delay(1000);
  var=8;
  break;
case 8:                                                       /// SE ACERCA A PLATAFORMA A DEJAR PALLET

  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      delay(1000);
      var=9;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      delay(1000);
      var=9;
      
    }
  else{
    motorRiel.write(180);
    }
  }
  break;
  
case 9:                         //// BAJA Y DEJA PALLET
delay(3000);
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=10;     //var 1 se cambió a var 7 para dejar pallets
     //derecha=1;3
     //izquierda=0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(1000); 
  break;
  
case 10:                                                                    ///SE RETIRA DE PLATAFORMA DESPUES DE DEJAR PALLET Y GIRA A 90°
if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(1000);
    motorGarra.write(90);
    delay(5000);
    var=11;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    delay(1000);
    motorGarra.write(90);
    delay(5000);
    var=11;
  }
  else{
    motorRiel.write(0);
    }
  }
  delay(500);
  break;
case 11:
                                                        //GIRA GARRA A DERECHA/IZQUIERDA Y ENTRA HACIA PALLET EN DESPACHO
  if (derecha==0 && izquierda==1){ //0 1
    motorGarra.write(180);
    delay(500);
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      delay(1000);
      var=12;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
    motorGarra.write(0);
    delay(500);
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      delay(1000);
      var=12;
      
    }
  else{
    motorRiel.write(180);
    }
  }
 break;
case 12:                                    //LEVANTA PALLET DE DESPACHO
L=6 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  delay(1000);
  var=13;
  break;

case 13:
                                                    //RETIRA PALLET DE DESPACHO

if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(1000);
    var=14;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    delay(1000);
    var=14;
  }
  else{
    motorRiel.write(0);
    }
  }
  delay(500);
  break;


case 14:

  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=15;     //var 1 se cambió a var 7 para dejar pallets
     //derecha=1;3
     //izquierda=0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(1000); 
  break;

case 15:
delay(5000);
L=96 ;
  digitalWrite(ene, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

 for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < (L-5) * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

    for (int i = 0; i < (L-(L-2)) * stepsPerRevolution; i++) {        
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  } 
  delay(1000);
  var=16;
  break;

case 16:

  if (derecha==0 && izquierda==1){ //0 1
 
    if (digitalRead(FinalCI)==LOW){  //CD
      motorRiel.write(90);
      delay(1000);
      var=17;      
      
  }
  else{
      motorRiel.write(0);
    }
  }
  
  if (derecha==1 && izquierda==0){  
 
    if (digitalRead(FinalCD)==LOW){ //CI
      motorRiel.write(90);
      delay(1000);
      var=17;
      
    }
  else{
    motorRiel.write(180);
    }
  }
  break;
  
case 17:                         //// BAJA Y DEJA PALLET
delay(3000);
  digitalWrite(dirPin,LOW); 
  for(int i = 0; i < 400; i++) {
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(1000); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(1000); 
  }
  
  delay(1000);
   var=18;  
   break;
  
case 18:                                                                    ///SE RETIRA DE PLATAFORMA DESPUES DE DEJAR PALLET Y GIRA A 90°
if (derecha==0 && izquierda==1){
 
  if (digitalRead(FinalCD)==LOW){ //i
    motorRiel.write(90);
    delay(1000);
    motorGarra.write(90);
    delay(5000);
    var=19;
  }
  else{
    motorRiel.write(180);
    }
  }

   
if (derecha==1 && izquierda==0){
 
  if (digitalRead(FinalCI)==LOW){ //D
    motorRiel.write(90);
    delay(1000);
    motorGarra.write(90);
    delay(5000);
    var=19;
  }
  else{
    motorRiel.write(0);
    }
  }
  delay(500);
  break;

case 19:                         //// BAJA Y DEJA PALLET
delay(500);
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2*L * stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  
    
    Fin=digitalRead(fin);
    if (Fin==LOW){
     digitalWrite(ene, HIGH);
     delay(1000);
     L=0;
     var=1;     //var 1 se cambió a var 7 para dejar pallets
     //derecha=1;3
     //izquierda=0;
      }
      else{
        digitalWrite(ene, LOW);
      }
  }
  delay(1000); 
  break;

}
}
