int Xstep = 2;
int Ystep = 3;
int Ydir = 6;
int Xdir = 5;
int ena = 8; 
int steps =   1000;
int speed = 500; 
int i = 0;
int x_speed = 10;
int y_speed = 10;
int kx ;
int ky;
int k;
int c;
int lcd_x;
int lcd_y;
int current_angle = 0;


#include <Servo.h>
Servo pen;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
 

void homing_xy (){
  Serial.println("homing sequence");
  int y_sensorVal = digitalRead(10); 
  while(y_sensorVal == HIGH){

     digitalWrite(ena,LOW);
     digitalWrite(Xdir,LOW);
     digitalWrite(Ydir,HIGH);
  
     digitalWrite(Xstep,HIGH);
     digitalWrite(Ystep,HIGH);
      delayMicroseconds(speed);
     digitalWrite(Xstep,LOW);
     digitalWrite(Ystep,LOW );
     delayMicroseconds(speed);
     
     y_sensorVal = digitalRead(10);    
   }
  delay(100);
  int x_sensorVal = digitalRead(9); 
  while(x_sensorVal == HIGH){

     digitalWrite(ena,LOW);
     digitalWrite(Xdir,HIGH);
     digitalWrite(Ydir,HIGH);
     
     digitalWrite(Xstep,HIGH);
     digitalWrite(Ystep,HIGH);
     delayMicroseconds(speed);
     digitalWrite(Xstep,LOW);
     digitalWrite(Ystep,LOW );
     delayMicroseconds(speed);
     
      x_sensorVal = digitalRead(9);
   
     
   }
   digitalWrite(ena,HIGH);
}

int X_axis(int x){
      int x_sensorVal = digitalRead(9);
      lcd_x = lcd_x + x;
      int b = 0;
      if(x>0){
          Serial.println("positive"); 
          digitalWrite(ena,LOW);
          digitalWrite(Xdir,LOW);
          digitalWrite(Ydir,LOW);
      }
      else{
          Serial.println("negative");
          digitalWrite(ena,LOW);
          digitalWrite(Xdir,HIGH);
          digitalWrite(Ydir,HIGH);
          x = x * -1;
          
      }
     
      while( b < x){
         if(x_sensorVal == HIGH  ){
             digitalWrite(Xstep,HIGH);
             digitalWrite(Ystep,HIGH);
             delayMicroseconds(speed);
             digitalWrite(Xstep,LOW);
             digitalWrite(Ystep,LOW );
             delayMicroseconds(speed);
             b++;
        }
          
        else{
          digitalWrite(ena,HIGH);
          Serial.println("X SAFETY");
        }
     }
  Serial.println(x);
}


int Y_axis(int y){
      int y_sensorVal = digitalRead(10);
      lcd_y = lcd_y + y;
      int b = 0;
      if(y>0){
          Serial.println("positive");
          digitalWrite(ena,LOW);
          digitalWrite(Xdir,HIGH);
          digitalWrite(Ydir,LOW);
      }
      else{
          Serial.println("negative");
          digitalWrite(ena,LOW);
          digitalWrite(Xdir,LOW);
          digitalWrite(Ydir,HIGH);
          y = y * -1;
          
      }
     
      while( b < y){
        if(y_sensorVal == HIGH){
            digitalWrite(Xstep,HIGH);
            digitalWrite(Ystep,HIGH);
            delayMicroseconds(speed);
            digitalWrite(Xstep,LOW);
            digitalWrite(Ystep,LOW );
            delayMicroseconds(speed);
            b++;
      }
        else{
            digitalWrite(ena,HIGH);
            Serial.println("Y SAFETY");  
            
      }
  }
  Serial.println(y);
}


 void LCD(){
    lcd.setCursor(1,1);
    lcd.print("X");
    lcd.setCursor(1,2);
    lcd.print(lcd_x);
    lcd.setCursor(2,1);
    lcd.print("Y");
    lcd.setCursor(2,2);
    lcd.print(lcd_y);
    
 }



int cordinate_xy (int x, int y){
  if(x > y ){    
    k = x/y;
    int kx = 1;
    int ky = k;
    c = x;
  }
  else {
    k = y/x;
    int ky = 1;
    int kx = k;
    c = y;
  }
  for( int i = 0 ; i <= c; i++){
   k = y/x;
   c = y;
   if (i % kx == 0){
      digitalWrite(ena,LOW);
      
      digitalWrite(Xdir,LOW);
      digitalWrite(Ydir,LOW);
      
      digitalWrite(Xstep,HIGH);
      digitalWrite(Ystep,HIGH);
      delayMicroseconds(x_speed);
      digitalWrite(Xstep,LOW);
      digitalWrite(Ystep,LOW);
      delayMicroseconds(x_speed);
      //Serial.println(x_speed);
      //Serial.println(i);
      
      
    }
    if (i % ky == 0){
      digitalWrite(ena,LOW);
      
      digitalWrite(Xdir,HIGH);
      digitalWrite(Ydir,LOW);
      
      digitalWrite(Xstep,HIGH);
      digitalWrite(Ystep,HIGH);
      delayMicroseconds(y_speed);
      digitalWrite(Xstep,LOW);
      digitalWrite(Ystep,LOW);
      delayMicroseconds(y_speed);
      //Serial.println(x_speed);
      //Serial.println(i);
    }
  }
}

int pen_tool(int angle){
   pen.write(angle);

}


void  setup() {
  //  put your setup code here, to run once:
  
  pinMode(Xstep,OUTPUT);
  pen.attach(11);
  pinMode(Xdir, OUTPUT);
  pinMode(Ydir, OUTPUT);
  pinMode(Ystep, OUTPUT);
  pinMode(10,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(ena,OUTPUT);
  Serial.begin(115200);
  digitalWrite(ena,HIGH);
  lcd.init();
  lcd.backlight();
  lcd.print("online");
  delay(200);
  lcd.clear();
  //homing_xy();
  X_axis(-700);
  X_axis(700);
  X_axis(-700);
  delay(100);
  Y_axis(500);
  delay(100);
  Y_axis(-500);
  delay(100);
  Y_axis(-500);

//cordinate_xy(100,1);
   //pen_tool(45);
} 



 
void loop() { 

 
}       
                          
