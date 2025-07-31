#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// LCD configuration
int lcdAddress = 0x27;      // I2C address of the LCD
int lcdColumns = 16;        // Number of columns on the LCD
int lcdRows = 2;            // Number of rows on the LCD

LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

// Push button configuration
const int buttonPin = A0;    // Push button connected to pin A0
bool buttonPressed = false; // Flag to check if button is pressed

// Keypad configuration
const byte ROWS = 4;        // Four rows
const byte COLS = 4;        // Four columns
char keys[ROWS][COLS] = {   // Keypad layout
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'}
};
byte rowPins[ROWS] = {12, 11, 9, 8};  // Row pins connected to the Arduino
byte colPins[COLS] = {7, 6, 5, 4};    // Column pins connected to the Arduino

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables for patient data
String age = "";
String weight = "";
String allergy = "";

// Variables for medication details
String fluidType = "";
String dosage = "";
String volume = "";
String flowRate = "";

// Current section and question tracking
enum Section { PATIENT_DATA, MEDICATION_DETAILS };
Section currentSection = PATIENT_DATA;
int currentQuestion = 0;

// New variable to track data completion
bool dataCompleted = false;
bool infusionStarted = false;

void setup() {
  // Initialize LCD
  Wire.begin();
  lcd.begin(lcdColumns, lcdRows);
  lcd.backlight();
  delay(2000);
  lcd.clear();

  // Booting process
  lcd.setCursor(3, 0);
  lcd.print("VITAL LINK");
  delay(3000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("BOOTING");
  delay(1000);

  // Display the booting bar
  lcd.setCursor(0, 1); // Move to the second row
  for (int i = 0; i < lcdColumns; i++) { // Incrementally fill the bar
    lcd.print("\xFF"); // Use '\xFF' for a solid block character
    delay(12000 / lcdColumns); // Spread delay over 5 seconds
  }
  delay(1000);

  // Ask the user to click the Next button
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Click On");
  lcd.setCursor(3, 1);
  lcd.print("Next Button");

  // Configure the push button
  pinMode(buttonPin, INPUT_PULLUP);
}

void displayQuestion() {
  lcd.clear();
  if (currentSection == PATIENT_DATA) {
    lcd.setCursor(0, 0);
    lcd.print("PATIENT'S DATA");
    lcd.setCursor(0, 1);
    if (currentQuestion == 0) {
      lcd.print("AGE: " + age);
    } else if (currentQuestion == 1) {
      lcd.print("WEIGHT: " + weight);
    } else if (currentQuestion == 2) {
      lcd.print("ALLERGY: " + allergy);
    }
  } else if (currentSection == MEDICATION_DETAILS) {
    lcd.setCursor(0, 0);
    lcd.print("MEDICATION DATA");
    lcd.setCursor(0, 1);
    if (currentQuestion == 0) {
      lcd.print("FLUID: " + fluidType);
    } else if (currentQuestion == 1) {
      lcd.print("DOSAGE: " + dosage + " ML");
    } else if (currentQuestion == 2) {
      lcd.print("VOLUME: " + volume + " ML");
    } else if (currentQuestion == 3) {
      lcd.print("FLOW: " + flowRate + " mL/min");
    }
  }
}

void loop() {
  // Wait for the button press to begin the input process
  if (!buttonPressed && digitalRead(buttonPin) == LOW) {
    delay(200); // Debounce delay
    if (digitalRead(buttonPin) == HIGH) { // Confirm button press
      buttonPressed = true;
      displayQuestion();
    }
  }

  if (buttonPressed) {
    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') { // Add digit to the current input
        if (!dataCompleted) {
          if (currentSection == PATIENT_DATA) {
            if (currentQuestion == 0) age += key;
            else if (currentQuestion == 1) weight += key;
            else if (currentQuestion == 2) allergy += key;
          } else if (currentSection == MEDICATION_DETAILS) {
            if (currentQuestion == 0) fluidType += key;
            else if (currentQuestion == 1) dosage += key;
            else if (currentQuestion == 2) volume += key;
            else if (currentQuestion == 3) flowRate += key;
          }
          displayQuestion(); // Refresh the screen
        }
      } else if (key == 'D') { // Move to the next question
        if (!dataCompleted) {
          currentQuestion++;
          if (currentSection == PATIENT_DATA && currentQuestion > 2) {
            currentSection = MEDICATION_DETAILS;
            currentQuestion = 0;
          } else if (currentSection == MEDICATION_DETAILS && currentQuestion > 3) {
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("DATA COMPLETED");
            dataCompleted = true;
            delay(3000);
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("CLICK INFUSION");
            lcd.setCursor(3, 1);
            lcd.print("BUTTON NOW");
          } else {
            displayQuestion();
          }
        } else if (!infusionStarted) { // Start infusion if data is completed
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("INFUSION IN");
          lcd.setCursor(3, 1);
          lcd.print("PROGRESS...");
          infusionStarted = true;
        }
      } else if (key == 'A') { // Go back to the previous question
        if (!dataCompleted) {
          currentQuestion--;
          if (currentSection == MEDICATION_DETAILS && currentQuestion < 0) {
            currentSection = PATIENT_DATA;
            currentQuestion = 2;
          } else if (currentSection == PATIENT_DATA && currentQuestion < 0) {
            currentQuestion = 0; // Stay on the first question
          }
          displayQuestion();
        }
      } else if (key == '#') { // Save and display summary
        if (!dataCompleted) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("DATA SAVED:");
          delay(2000);
          lcd.clear();
          lcd.print("AGE: " + age);
          lcd.setCursor(0, 1);
          lcd.print("WEIGHT: " + weight);
          delay(2000);
          lcd.clear();
          lcd.print("ALLERGY: " + allergy);
          delay(2000);
          lcd.clear();
          lcd.print("FLUID: " + fluidType);
          lcd.setCursor(0, 1);
          lcd.print("DOSAGE: " + dosage + " ML");
          delay(2000);
          lcd.clear();
          lcd.print("VOLUME: " + volume + " ML");
          lcd.setCursor(0, 1);
          lcd.print("FLOW: " + flowRate + " mL/min");
          delay(3000);
          lcd.clear();
          buttonPressed = false; // Reset to allow new input
        }
      } else if (key == '*') { // Clear current input
        if (!dataCompleted) {
          if (currentSection == PATIENT_DATA) {
            if (currentQuestion == 0) age = "";
            else if (currentQuestion == 1) weight = "";
            else if (currentQuestion == 2) allergy = "";
          } else if (currentSection == MEDICATION_DETAILS) {
            if (currentQuestion == 0) fluidType = "";
            else if (currentQuestion == 1) dosage = "";
            else if (currentQuestion == 2) volume = "";
            else if (currentQuestion == 3) flowRate = "";
          }
          displayQuestion();
        }
      }
    }
  }
}
