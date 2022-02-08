//library
#include <Servo.h>
Servo pen;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

//general variable 
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
int kx ,ky ,k ,c ,lcd_x ,lcd_y;
int current_angle = 0;

//calibration
void homing_xy () {
  Serial.println("homing sequence");
  int y_sensorVal = digitalRead(10); 
  while(y_sensorVal == HIGH){

    digitalWrite(ena,LOW);
    digitalWrite(Xdir,HIGH);
    digitalWrite(Ydir,HIGH);

    digitalWrite(Xstep,HIGH);
    digitalWrite(Ystep,HIGH);
    delayMicroseconds(speed);
    digitalWrite(Xstep,LOW);
    digitalWrite(Ystep,LOW );
    delayMicroseconds(speed);
    
    y_sensorVal = digitalRead(10);    
  }
  delay(10);
  int x_sensorVal = digitalRead(9); 
  while(x_sensorVal == HIGH){

    digitalWrite(ena,LOW);
    digitalWrite(Xdir,HIGH);
    digitalWrite(Ydir,LOW);
    
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

//x axis control
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
    digitalWrite(Xstep,HIGH);
    digitalWrite(Ystep,HIGH);
    delayMicroseconds(speed);
    digitalWrite(Xstep,LOW);
    digitalWrite(Ystep,LOW );
    delayMicroseconds(speed);
    b++;
  }    
}

//y axis control
int Y_axis(int y){
  int y_sensorVal = digitalRead(10);
  lcd_y = lcd_y + y;
  int b = 0;
  if(y>0){
    Serial.println("postive");
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
    digitalWrite(Xstep,HIGH);
    digitalWrite(Ystep,HIGH);
    delayMicroseconds(speed);
    digitalWrite(Xstep,LOW);
    digitalWrite(Ystep,LOW );
    delayMicroseconds(speed);
    b++;
  }
  Serial.println(y);
}

//to control display
void LCD(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("X");
  lcd.setCursor(2,0);
  lcd.print(lcd_x);
  lcd.setCursor(1,1);
  lcd.print("Y");
  lcd.setCursor(2,1);
  lcd.print(lcd_y);
}

//doesnt work
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


int go_to (){

}


//control pen position
int pen_tool(String state ){
    if(state == "up"){
    pen.write(90);
    Serial.println("up");
    }
    else{
    pen.write(5);
    Serial.print("down");
    }  
}


void  setup1() {
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
  //homing_xy();
  //cordinate_xy(100,1);
  //pen_tool(45);
  Y_axis(80);
  LCD();

} 



 
void loop() { 

 
}       
                          

class Stepper {
    int step, dir, default_dir;
    int s_delay;
  public:
    Stepper(int step_pin, int dir_pin, int clock_dir, int step_delay) {
       /* The clock_dir set  to make it go clock wise */ 
       step = step_pin;
       dir = dir_pin;
       s_delay = step_delay;
       default_dir = clock_dir;
       pinMode(step, OUTPUT);
       pinMode(dir, OUTPUT);
    }

    int flip(int value) {
      if (value == HIGH) {
        return LOW;
      }
      return HIGH;
    }

    void clock(int steps) {
      /* positive number to step in clock direction. 
      *  Negative number to step in anti-clock direction. */
      int dir_value = LOW;
      if (default_dir) {
        dir_value = HIGH;
      }
      if (steps < 0) {
        /* flip direction if anti-clock */
        steps = -1 * steps;
        dir_value = flip(dir_value);
      }
      digitalWrite(dir, dir_value);
      for (int s= 0; s < steps; s++) {
        digitalWrite(step, HIGH);
        delayMicroseconds(s_delay);
        digitalWrite(step, LOW);
        delayMicroseconds(s_delay);
      }
    }
};

class AxiDraw {
  int x,y;
  Stepper &motorL;
  Stepper &motorR;
  int enable;
  public:
    AxiDraw(int enable_pin, Stepper &s_motorL, Stepper &s_motorR) :
      motorL(s_motorL), motorR(s_motorR), enable(enable_pin) {

      }
};

class motor {
  int dir,step,FLIP;
  public:
    motor(int dir_pin, int step_pin, int speed, int flip) {
      dir = dir_pin ; 
      step = step_pin ;
      pinMode(step,OUTPUT);
      pinMode(dir,OUTPUT);
      FLIP = flip;
    }
    
    void stepper(int steps){
      steps = steps * FLIP;
      if(steps > 0){
        digitalWrite(dir,HIGH);
        Serial.println("pos");
      }
      else{
        digitalWrite(dir,LOW);
        Serial.println("neg");
        steps = steps * -1;
      }
      for(int i;steps > i;i++ ){
        digitalWrite(step,HIGH);
        delayMicroseconds(speed);
        digitalWrite(step,LOW);
        delayMicroseconds(speed);
      }
    }



};


void setup() {
  pinMode(ena,OUTPUT);
  digitalWrite(ena,LOW);
  motor l (5,2,500,-1);
  l.stepper(1000);

  
  
}