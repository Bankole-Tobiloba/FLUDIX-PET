#include <TFT_22_ILI9225.h>

// Define pins for the display
#define TFT_RST 8  // Reset pin
#define TFT_RS  9  // Data/Command pin
#define TFT_CS  10 // Chip Select pin
#define TFT_LED 7  // Backlight LED pin (optional)

// Define pin for the buzzer
#define BUZZER_PIN 7

// Define pin for the push button
#define BUTTON_PIN A0

// Create the display object
TFT_22_ILI9225 myLCD = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

void animateText(const char* text, int x, int y, unsigned int color) {
  int len = strlen(text); // Get the length of the text
  char buffer[20];        // Buffer to hold the progressively displayed text
  for (int i = 0; i <= len; i++) {
    strncpy(buffer, text, i); // Copy i characters into the buffer
    buffer[i] = '\0';         // Null-terminate the string
    myLCD.fillRectangle(x, y, x + 200, y + 16, COLOR_BLACK); // Clear previous text
    myLCD.drawText(x, y, buffer, color); // Draw updated text
    delay(400); // Delay for animation effect
  }
}

void showBootScreen() {
  // Clear the screen by filling it with black
  myLCD.fillRectangle(0, 0, 176, 220, COLOR_BLACK); // Screen dimensions: 176x220 for this TFT

  myLCD.setFont(Terminal12x16);  // Set font
  myLCD.drawText(40, 60, "SYSTEM BOOT", COLOR_WHITE); // Display "SYSTEM BOOTING..."

  // Draw the loading bar background
  int barX = 30, barY = 100, barWidth = 140, barHeight = 10;
  myLCD.drawRectangle(barX, barY, barX + barWidth, barY + barHeight, COLOR_WHITE); // Outer rectangle

  // Animate the loading bar
  for (int i = 0; i <= barWidth; i++) {
    myLCD.fillRectangle(barX, barY, barX + i, barY + barHeight, COLOR_GREEN); // Fill the bar
    delay(70); // 7 seconds total = 7000ms / 160 (barWidth)
  }

  // Wait 2 seconds before the buzzer starts
  delay(2000);

  // Buzzer beeps for 2.5 seconds
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2500);
  digitalWrite(BUZZER_PIN, LOW);
}

void showWelcomeScreen() {
  // Clear the screen
  myLCD.fillRectangle(0, 0, 176, 220, COLOR_BLACK);

  // Text to display
  const char* welcomeText = "WELCOME";
  int len = strlen(welcomeText);
  int charWidth = 20; // Approximate width of a character in the font
  int centerX = 140 - (len * charWidth / 2); // Center horizontally
  int centerY = 95  - 8;                   // Center vertically (adjusted for font height)

  char buffer[20]; // Buffer to hold the text

  // Animate text from center outward
  for (int i = 0; i < len; i++) {
    strncpy(buffer, welcomeText, i + 1); // Gradually add characters
    buffer[i + 1] = '\0';               // Null-terminate the string

    myLCD.fillRectangle(centerX, centerY, 176, centerY + 16, COLOR_BLACK); // Clear old text
    myLCD.drawText(centerX, centerY, buffer, COLOR_YELLOW);                // Display new text
    delay(500); // Animation speed
  }
}

void showSettingsScreen() {
  // Clear the screen
  myLCD.fillRectangle(0, 0, 176, 220, COLOR_BLACK);

  // Display "SETTINGS" at the top
  myLCD.setFont(Terminal12x16);
  myLCD.drawText(60, 20, "SETTINGS", COLOR_BLUE); // Adjust x and y for centering
  myLCD.drawText(5, 60, "Note All Instruction", COLOR_WHITE);
  myLCD.drawText(5, 90, "must be inputed", COLOR_WHITE);
  myLCD.drawText(5, 120, "using the LCD below", COLOR_WHITE);
  myLCD.drawText(150, 150, "Next", COLOR_WHITE);
  myLCD.drawText(200, 150, ">", COLOR_RED);
//  delay(2000);
//  myLCD.fillRectangle(0, 0, 176, 220, COLOR_BLACK);
//  myLCD.drawText(5, 120, "using the LCD below", COLOR_BLACK);
//  myLCD.drawText(5, 60, "Note All Instruction", COLOR_BLACK);
//  myLCD.drawText(150, 150, "Next>", COLOR_BLACK);
}

void setup() {
  // Initialize the display
  myLCD.begin();
  myLCD.setOrientation(1); // 1 for landscape, 0 for portrait
  myLCD.setBackgroundColor(COLOR_BLACK); // Set background color to black
  myLCD.setFont(Terminal12x16); // Set a larger font

  // Set buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is off initially

  // Set button pin as input with a pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Display animated text
  animateText("VITAL LINK", 50, 85, COLOR_RED);

  // Wait for 2 seconds
  delay(2000);

  // Show the boot screen with the loading bar and buzzer
  showBootScreen();

  // Show the welcome screen
  showWelcomeScreen();
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == HIGH) { // Button pressed (active low)
    showSettingsScreen();               // Show the settings screen
    }
    
}
