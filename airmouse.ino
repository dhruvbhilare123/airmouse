//calibrate_airmouse
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>
#include<Keyboard.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;

const int SW_pin = 7; // digital pin connected to button output of joystick

const int X_pin = A0; // analog pin connected to X output

const int Y_pin = A1; // analog pin connected to Y output

int x, y;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
  pinMode(SW_pin, INPUT); 

  digitalWrite(SW_pin, HIGH); 
  Keyboard.begin();
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = -(gx+300)/150;  // change 300 from 0 to 355 I have added a minus for mirroring the axis (depends from case 2 case)
  vy = (gz-100)/150; // same here about "-100"  from -355 to 0

  Serial.print("gx = ");
  Serial.print(gx);
  Serial.print(" | gz = ");
  Serial.print(gz);
  
  Serial.print("        | X = ");
  Serial.print(vx);
  Serial.print(" | Y = ");
  Serial.println(vy);
  
  Mouse.move(vx, vy);
  
  delay(20);
  {

  x = analogRead(X_pin); // output of X_pin is read

 // Ive put >1000  and <50 as my joysticks arent accurate to use =1023 (case specific)
 if (x > 1000) 
  {

    Serial.println("Up:");

    Keyboard.press(KEY_LEFT_CTRL);

    Keyboard.press(KEY_TAB); 
     delay(500);
      Keyboard.releaseAll();

  }

  else

  {

    Keyboard.releaseAll();  // release the keys

  }

  x = analogRead(X_pin);  

  if (x < 50) 


  {

    Serial.println("Down:");

    
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_TAB); 
     delay(500);
      Keyboard.releaseAll();

  }

  else

  {

     Keyboard.releaseAll();  

  }

  y = analogRead(Y_pin); 


    if (y > 1000) 

    {

      Serial.println("left"); 

     Keyboard.press(KEY_LEFT_ALT);
     Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_TAB); 
      delay(500);
      Keyboard.releaseAll();

    }

    else

    {

     Keyboard.releaseAll(); 

    }

  y = analogRead(Y_pin); 


    if (y < 20) 

    {

      Serial.println("Right");

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_TAB); 
      delay(500);
      Keyboard.releaseAll();
  }

  else

  {

     Keyboard.releaseAll();  

  }

  int z = digitalRead(SW_pin); // ive added only a left click but to add a right click its the same process just (MOUSE_RIGHT)


    if (z == 0) 

    {

      Serial.println("Click");

     Mouse.press(MOUSE_LEFT);
     delay(200);
      Mouse.release(MOUSE_LEFT);
   }

}
}
