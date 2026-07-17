#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>

// Your original pin assignments
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
Servo myservo;

const int greenLED=10;
const int redLED=11;
const int buzzer=12;

#define Password_Length 5

char Master[Password_Length]="1234"; // This stores the correct password
char Data[Password_Length];            // This temporarily holds what the user types
byte data_count=0;                    // Tracks how many digits have been entered
int attempts=0;                       // Tracks wrong attempts for lockout
bool locked=false;                    // Tracks if system is currently locked out

const byte ROWS=4,COLS=4;
char keys[ROWS][COLS]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

// CHANGED: Row 1 is moved from Pin 0 to Pin 8 to fix the 1,2,3,A buttons
byte rowPins[ROWS]={8,1,2,3};
byte colPins[COLS]={4,5,6,7};

Keypad keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

// Function to make a quick beep sound on the buzzer
void beep(int t){digitalWrite(buzzer,HIGH);delay(t);digitalWrite(buzzer,LOW);}

void setup(){
 pinMode(greenLED,OUTPUT);
 pinMode(redLED,OUTPUT);
 pinMode(buzzer,OUTPUT);
 myservo.attach(9);
 myservo.write(0); // Set servo to 0 degrees (Locked)
 
 // Load the saved password from EEPROM memory on startup
 if(EEPROM.read(0) != 255){ 
    for(int i=0; i<4; i++) {
      Master[i] = EEPROM.read(i);
    }
 }

 lcd.begin(16,2);
 lcd.print("Smart Door Lock"); // Welcome message
 delay(1500);
 lcd.clear();
}

void loop(){
 // If the system is locked out after 3 wrong tries, wait 30 seconds
 if(locked){
   lcd.setCursor(0,0); lcd.print("System Locked ");
   delay(30000);
   locked=false;
   attempts=0;
   lcd.clear();
 }
 
 lcd.setCursor(0,0);
 lcd.print("Enter Password");
 
 char k=keypad.getKey(); // Check if a key was pressed
 if(k){
   beep(30); // Short confirmation beep for any key press
   
   // IF USER PRESSES '#' - PASSWORD CHANGE ROUTINE START
   if(k=='#'){
      lcd.clear();
      lcd.print("Current Pass:");
      
      char oldPass[Password_Length];
      byte old_count = 0;
      
      // Loop to read 4 digits for the current password check
      while(old_count < 4){
        char oldKey = keypad.getKey();
        if(oldKey){
          beep(30);
          oldPass[old_count] = oldKey;
          lcd.setCursor(old_count, 1);
          lcd.print('*');
          old_count++;
        }
      }
      oldPass[4] = '\0'; // End the string properly
      
      // Compare entered password with the Master password
      if(strcmp(oldPass, Master) == 0){
        lcd.clear();
        lcd.print("New Pass:");
        byte new_count = 0;
        
        // Loop to read 4 digits for the new password
        while(new_count < 4){
          char newKey = keypad.getKey();
          if(newKey){
            beep(30);
            Master[new_count] = newKey; // Directly save new key into Master array
            lcd.setCursor(new_count, 1);
            lcd.print('*');
            new_count++;
          }
        }
        
        // Save the newly assigned password to EEPROM permanently
        for(int i=0; i<4; i++) {
          EEPROM.write(i, Master[i]);
        }

        lcd.clear();
        lcd.print("Pass Changed!");
        delay(1500);
      } else {
        // If the current password was wrong, deny access to change it
        lcd.clear();
        lcd.print("Wrong Password!");
        digitalWrite(redLED,HIGH); beep(300); digitalWrite(redLED,LOW);
        delay(1500);
      }
      
      lcd.clear();
      return; // Return back to the start of the main loop
   }
   // PASSWORD CHANGE ROUTINE END
   
   Data[data_count]=k; // Store normal key input into our data buffer
   lcd.setCursor(data_count,1);
   lcd.print('*');     // Print a hidden character on screen
   data_count++;
 }
 
 // If 4 digits are successfully typed out for unlocking
 if(data_count==4){
    Data[4]='\0'; // End the string properly
    
    // Check if entered password matches the stored Master password
    if(strcmp(Data,Master)==0){
      lcd.clear();
      lcd.print("Access Granted");
      digitalWrite(greenLED,HIGH); // Turn green LED ON
      myservo.write(90);            // Turn servo to 90 degrees (Unlocked)
      beep(300);
      delay(5000);                 // Wait 5 seconds
      myservo.write(0);            // Turn servo back to 0 degrees (Locked)
      digitalWrite(greenLED,LOW);  // Turn green LED OFF
      attempts=0;                  // Reset security attempts back to 0
    }else{
      // If password does not match
      attempts++;
      lcd.clear();
      lcd.print("Wrong Password");
      // Flash red LED and beep 3 times
      for(int i=0;i<3;i++){
        digitalWrite(redLED,HIGH);beep(120);
        digitalWrite(redLED,LOW);delay(120);
      }
      // If 3 incorrect entries are made, flag the system as locked
      if(attempts>=3){
        locked=true;
        digitalWrite(redLED,HIGH);
        digitalWrite(buzzer,HIGH);
        delay(1000);
        digitalWrite(buzzer,LOW);
        digitalWrite(redLED,LOW);
      }
    }
    memset(Data,0,sizeof(Data)); // Clear out the Data input buffer array
    data_count=0;                // Reset counter back to 0 for next time
    delay(1000);
    lcd.clear();
 }
}