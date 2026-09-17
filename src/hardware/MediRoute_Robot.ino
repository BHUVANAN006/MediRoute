// ZONE_0 is connected to 2
// ZONE_1 is connected to 3
// ZONE_2 is connected to 4
// ZONE_3 is connected to 5
// ZONE_4 is connected to 6
// ZONE_5 is connected to 7
// ZONE_6 is connected to A3
// I2C LCD DISPLAY is connected to SDA - SCL

#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);
int Scrolling_Speed = 50;
String message = " AUTONOMOUS MEDICAL SUPPLY DELIVERY ROBOT FOR HOSPITALS ";


// ************** Pin Configuration *********************************************** 
int ZONE_0_pin = 2;   
int ZONE_0_State = 0;
String ZONE_0 = "";

int ZONE_1_pin = 3;   
int ZONE_1_State = 0;
String ZONE_1 = "";

int ZONE_2_pin = 4;   
int ZONE_2_State = 0;
String ZONE_2 = "";

int ZONE_3_pin = 5;   
int ZONE_3_State = 0;
String ZONE_3 = "";

int ZONE_4_pin = 6;   
int ZONE_4_State = 0;
String ZONE_4 = "";

int ZONE_5_pin = 7;   
int ZONE_5_State = 0;
String ZONE_5 = "";

int ZONE_6_pin = A3;   
int ZONE_6_State = 0;
String ZONE_6 = "";

int Zone = 0;
int Rec_Zone = 0;

/* Motor Pin Controller*/
int LMotor1 =8;
int LMotor2 =9;
int RMotor1 =10;
int RMotor2 =11;


int L_IR_pin = A0;   
int L_IR_State = 0;
String L_IR= "";

int Obstracle_IR_pin = A1;   
int Obstracle_IR_State = 0;
String Obstracle_IR= "";

int IR = 0;

void DCMotorCondition();
void MotorStopCmd();
void MotorForwardCmd();
void MotorReverseCmd();
void MotorLeftCmd();
void MotorRightCmd();
char chh;

int Mspeed = 250;          // Initial speed (0–255)
int SpeedPercent = 0;      // Speed in percentage



// ************** Initial Setup Code *********************************************** 
void setup() { 
pinMode(L_IR_pin,INPUT_PULLUP);
pinMode(Obstracle_IR_pin,INPUT_PULLUP);
pinMode(ZONE_0_pin,INPUT_PULLUP);
pinMode(ZONE_1_pin,INPUT_PULLUP);
pinMode(ZONE_2_pin,INPUT_PULLUP);
pinMode(ZONE_3_pin,INPUT_PULLUP);
pinMode(ZONE_4_pin,INPUT_PULLUP);
pinMode(ZONE_5_pin,INPUT_PULLUP);
pinMode(ZONE_6_pin,INPUT_PULLUP);
lcd.begin();
      lcd.backlight();
      lcd.print("LCD Init..!");
      delay(1000);
      // Scroll message across first line
        for (int i = 0; i < message.length() - 15; i++) {
          lcd.setCursor(0, 0);
          lcd.print(message.substring(i, i + 16));  // Display 16 characters at a time
          delay(Scrolling_Speed);  // Scrolling_Speed
        }
        delay(1000);
        lcd.clear();
        lcdprint("Initilized","Sucessfully");
        // lcdprint("","");

  Serial.begin(9600);
  pinMode(LMotor1,OUTPUT);
  digitalWrite(LMotor1,LOW);
  pinMode(LMotor2,OUTPUT);
  digitalWrite(LMotor2,LOW);
  pinMode(RMotor1,OUTPUT);
  digitalWrite(RMotor1,LOW);
  pinMode(RMotor2,OUTPUT);
  digitalWrite(RMotor2,LOW);
  MotorStopCmd();
  delay(2500);



}


char String_text[10];









// ************** Main code , to run repeatedly  *********************************************** 
void loop() {
      // ZONE_0 Checking
      ZONE_0_State = digitalRead(ZONE_0_pin);
      // ZONE_1 Checking
      ZONE_1_State = digitalRead(ZONE_1_pin);
      // ZONE_2 Checking
      ZONE_2_State = digitalRead(ZONE_2_pin);
      // ZONE_3 Checking
      ZONE_3_State = digitalRead(ZONE_3_pin);
      // ZONE_4 Checking
      ZONE_4_State = digitalRead(ZONE_4_pin);
      // ZONE_5 Checking
      ZONE_5_State = digitalRead(ZONE_5_pin);
      // ZONE_6 Checking
      ZONE_6_State = digitalRead(ZONE_6_pin);

      if(ZONE_0_State == LOW){
          lcdprint("ZONE_1 ","Selected");
          Zone = 1;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_1_State == LOW){
          lcdprint("ZONE_2 ","Selected");
          Zone = 2;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_2_State == LOW){
          lcdprint("ZONE_3 ","Selected");
          Zone = 3;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_3_State == LOW){
          lcdprint("ZONE_4 ","Selected");
          Zone = 4;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_4_State == LOW){
          lcdprint("ZONE_5 ","Selected");
          Zone = 5;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_5_State == LOW){
          lcdprint("ZONE_6","Selected");
          Zone = 6;
          IR = 0;
          MotorForwardCmd();
          Rec_Zone = Zone;
      }

      else if(ZONE_6_State == LOW){
          lcdprint("Home ","Selected");
          Zone = 7;
          IR = 0;
      }

      Zone_Path();
      Obstracle();

}
// ************** Main code END  *********************************************** 



void Zone_Path()
{

   // L_IR Sensor Checking
      L_IR_State = digitalRead(L_IR_pin);
      if(L_IR_State == HIGH){
        IR = IR + 1;
        delay(2000);
      }


      if (Zone || 0)
      {
        itoa(IR, String_text, 10);
        lcd.setCursor(0,0);
        lcd.print("Path Column = ");
        lcd.print(String_text);
        lcd.print("                   ");
        if(Zone || 7)
        {
        lcd.setCursor(0,1);
        lcd.print("Zone = ");
        lcd.print(Zone);
        lcd.print("                   ");
        }
        if(Zone == 7)
        {
        lcd.setCursor(0,1);
        lcd.print(Rec_Zone);
        lcd.print(" Zone to Home ");
        lcd.print("                   ");
        }

        
      }
  if(Zone == 0)
  {
    MotorStopCmd();
  } else if((Zone == 1 && IR == 1) || (Zone == 3  && IR == 2) || (Zone == 5  && IR == 3))
  {
    MotorForwardCmd();
    Obstracle();
    delay(4000);
    Obstracle();
    MotorRightCmd();
    Obstracle();
    delay(5000);
    delay(3300);
    Obstracle();
    MotorForwardCmd();
    delay(3500);
    Zone = 0; 
    lcd.setCursor(0,0);
    lcd.print("Zone Reached");
    lcd.setCursor(0,1);
    lcd.print("                   ");
  } else if((Zone == 2  && IR == 1) || (Zone == 4 && IR == 2) || (Zone == 6 && IR == 3))
  {
    MotorForwardCmd();
    Obstracle();
    delay(4000);
    Obstracle();
    MotorLeftCmd();
    Obstracle();
    delay(5000);
    delay(3300);
    Obstracle();
    MotorForwardCmd();
    Obstracle();
    delay(3500);
    Zone = 0; 
    lcd.setCursor(0,0);
    lcd.print("Zone Reached");
    lcd.setCursor(0,1);
    lcd.print("                   ");
  }else if(Zone == 7)
  {
      MotorReverseCmd();
      Obstracle();
      delay(3500);
      Obstracle();
      if((Rec_Zone == 1) || (Rec_Zone == 3 ) || (Rec_Zone == 5 ))
      {
       MotorLeftCmd();
      }else{
        MotorRightCmd();
      }
      Obstracle();
      delay(5000);
      delay(3500);    
      Zone = 8;
      
  }
  else if(Zone == 8)
  {
    Obstracle();
    MotorReverseCmd();
    if((Rec_Zone == 1 && IR == 1) ||  (Rec_Zone == 2 && IR == 1) ||  (Rec_Zone == 3 && IR == 2) ||  (Rec_Zone == 4 && IR == 2)||  (Rec_Zone == 5 && IR == 3)||  (Rec_Zone == 6 && IR == 3))
     {
      Obstracle();
      lcd.setCursor(0,0);
      lcd.print("Zone Reached");
      lcd.setCursor(0,1);
      lcd.print("                   ");
      delay(1500);
      Zone = 0;
      lcd.clear();
    }
  }

  
}


void Obstracle()
{
        // Obstracle_IR Sensor Checking
      Obstracle_IR_State = digitalRead(Obstracle_IR_pin);
        if (Obstracle_IR_State == LOW)
        {
          // Obstacle detected
          MotorStopCmd();

          lcd.setCursor(0, 0);
          lcd.print("OBSTACLE FOUND  ");
          lcd.setCursor(0, 1);
          lcd.print("ROBOT STOPPED   ");

          Serial.println("Obstacle Detected");

          // Wait until obstacle is removed
          while (digitalRead(Obstracle_IR_pin) == LOW)
          {
            MotorStopCmd();
            delay(50);
          }

          // Obstacle removed
          lcd.clear();
          lcd.print("OBSTACLE CLEAR  ");
          delay(500);

          // Return from function
          return;
        } 
        else
        {
          // No obstacle
          return;
        }

}



void lcdprint(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(l1);
  lcd.print("                   ");
  lcd.setCursor(0,1);
  lcd.print(l2);
  lcd.print("                   ");
  interval();
}

void interval() {
  delay(1000);
  lcd.clear();
}
    void MotorStopCmd(){
         digitalWrite(LMotor1,HIGH);
         digitalWrite(LMotor2,HIGH);
         digitalWrite(RMotor1,HIGH);
         digitalWrite(RMotor2,HIGH);
         delay(250);
    }
    
    void MotorForwardCmd()
    {
         analogWrite(LMotor1, 0);
         analogWrite(LMotor2, Mspeed);
         analogWrite(RMotor1, 0);
         analogWrite(RMotor2, Mspeed);
    }
    void MotorReverseCmd(){
         analogWrite(LMotor2, 0);
         analogWrite(LMotor1, Mspeed);
         analogWrite(RMotor2, 0);
         analogWrite(RMotor1, Mspeed);
    }
    void MotorLeftCmd(){
        digitalWrite(LMotor1,LOW);
        digitalWrite(LMotor2,HIGH);
        digitalWrite(RMotor1,HIGH);
        digitalWrite(RMotor2,LOW);
    }
    
    void MotorRightCmd(){
        digitalWrite(LMotor1,HIGH);
        digitalWrite(LMotor2,LOW);
        digitalWrite(RMotor1,LOW);
        digitalWrite(RMotor2,HIGH);
    }

    void DisplaySpeed()
    {
      SpeedPercent = map(Mspeed, 0, 255, 0, 100);
      lcd.setCursor(0,1);
      lcd.print("SPD:");
      lcd.print(SpeedPercent);
      lcd.print("%   ");   // Clear extra characters
    }


// ************** Code By STPL  ***********************************************
