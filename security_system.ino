#include <Keypad.h>
#include <Servo.h>

Servo lockServo;

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {2,3,4,5};
byte colPins[cols] = {6,7,8,9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

String password = "9250";
String input = "";

int buzzer = 11;

void setup() {
  lockServo.attach(10);
  lockServo.write(0);   // Locked
  pinMode(buzzer, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {

    // CLEAR ALL
    if (key == '*') {
      input = "";
    }

    // DELETE LAST DIGIT USING D
    else if (key == 'D') {
      if (input.length() > 0) {
        input.remove(input.length() - 1);
      }
    }

    // ACCEPT NUMBERS ONLY
    else if (key >= '0' && key <= '9') {
      if (input.length() < 4) {
        input += key;
      }
    }

    // AUTO VERIFY AT 4 DIGITS
    if (input.length() == 4) {
      if (input == password) {
        lockServo.write(90);   // Unlock
        delay(3000);
        lockServo.write(0);    // Lock
      } else {
        tone(buzzer, 1000, 500); // Wrong password
      }
      input = ""; // Reset
    }
  }
}
