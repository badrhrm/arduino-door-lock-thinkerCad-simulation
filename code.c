#include <Keypad.h>
#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

// Define the rows and columns of the keypad
const byte ROWS = 4;
const byte COLS = 4;

// Define the characters on the keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Define the pins connected to the rows and columns of the keypad
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

// Create a Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Create a Servo object
Servo doorServo;
const int servoPin = 13;

// This LCD type always takes (0) as value 
Adafruit_LiquidCrystal lcd_1(0);

// Define the password
const char originalPassword[] = "4566";
char enteredPassword[5];
int i = -1;
int characterPointerIndex = -1; 


void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  // Attach the servo to pin 9
  doorServo.attach(servoPin);
  // Move the servo to the 0 degrees position (counterclockwise)
  // meaning close the door
  doorServo.write(0);
  
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Enter password:");
  lcd_1.clear();
}

void loop() {
  char key = keypad.getKey();
  
  if (key != NO_KEY) {
    if ((key >= '0' && key <= '9')) {
       if ( strlen(enteredPassword) < strlen(originalPassword) ){
        	i++;
      		lcd_1.setCursor(i, 0);
      		Serial.print("key : ");
      		Serial.println(key);
      		enteredPassword[i]= key;
      		// method 2 pour concatener to Concatenate the key character to the enteredPassword array
      		//strncat(enteredPassword, &key, 1);
      		Serial.print("enteredPassword : ");
      		Serial.println(enteredPassword);
      		lcd_1.print(enteredPassword[i]); // Display the entered character on the LCD
      	}
     }
    
    if(key=='#'){
      if (strcmp(originalPassword, enteredPassword) == 0) {
      	lcd_1.setCursor(0, 1);
        lcd_1.print("access allowed");
        // Move the servo to the 0 degrees position (counterclockwise)
  		  // meaning close the door
  		  doorServo.write(90);
        delay(2000);
        // to close the door
        resetEverythingStartOver();
   	  }else {
        lcd_1.setCursor(0, 1);
        lcd_1.print("access denied");
      }
    }
    
    //character pointer to specify which char to delete/modify
    if(key == '*' && strlen(enteredPassword)>0){
      // if ^ reachs last char of pwd then we reset index
      if(strlen(enteredPassword) == (characterPointerIndex+1) ){
        characterPointerIndex = -1;
      }
      re_renderPassword();
      characterPointerIndex++;
      lcd_1.setCursor(characterPointerIndex,1);
      lcd_1.print('^');
    }
    
    if(key == 'D'){
      deleteCharacter();
    }
    
    if(key == 'C'){
      modifyCharacter();
    }
    if(key == 'A'){
      resetEverythingStartOver();
    }
  }
}

void deleteCharacter(){
  for (int j = characterPointerIndex; enteredPassword[j] != '\0'; j++) {
    enteredPassword[j] = enteredPassword[j + 1];
  }
  
  re_renderPassword();
  
  // Move the cursor to the end of the enteredPassword on the LCD display
  lcd_1.setCursor(strlen(enteredPassword), 0);
  
  i--;
  // reset delete pointer index 
  characterPointerIndex = -1;
}

void re_renderPassword(){
  lcd_1.clear();
  lcd_1.setCursor(0,0);
  lcd_1.print(enteredPassword);
  // another method 
  //for(int k = 0; k < i+1; k++){
    //lcd_1.print(enteredPassword[k]);
  //}
}
void modifyCharacter(){
  char key = '\0';
  while(true){
    //blinkingUnderscore
  	lcd_1.setCursor(characterPointerIndex, 0); 
  	lcd_1.print("_"); 
  	//delay(500); 
  	lcd_1.setCursor(characterPointerIndex, 0); 
  	lcd_1.print(" "); 
  	delay(20); 
    key = keypad.getKey();
    // if a button is clicked then stop blinking
    if(key!=NO_KEY){break;}
  }
  //when entering a new char then display and stop the blinking
  if((key >= '0' && key <= '9')){
    Serial.print("new modified char:");
    Serial.println(key);
    enteredPassword[characterPointerIndex]=key;
    lcd_1.setCursor(characterPointerIndex, 0); 
    lcd_1.print(enteredPassword[characterPointerIndex]);
  }
}

void resetEverythingStartOver(){
   // Reset variables and start over
   characterPointerIndex = -1;
   i = -1;
   for(int j = 0; j < sizeof(enteredPassword); j++) {
       enteredPassword[j] = '\0';
   } 
   lcd_1.clear();
   lcd_1.setCursor(0, 0);
   doorServo.write(0); // Close the door
   delay(1000);
}
