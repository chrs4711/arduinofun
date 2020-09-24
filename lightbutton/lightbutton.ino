const int BUTTON_ONE_PIN = 2;
const int BUTTON_TWO_PIN = 3;
const int LED_ONE = 10;
const int LED_TWO = 9;

int buttonOneState = 0;
int buttonTwoState = 0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_ONE, OUTPUT);
  pinMode(LED_TWO, OUTPUT);

  pinMode(BUTTON_ONE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_TWO_PIN, INPUT_PULLUP);
}

void loop() {
  
  buttonOneState = digitalRead(BUTTON_ONE_PIN);  

  if (buttonOneState == HIGH) {
    digitalWrite(LED_ONE, LOW);
  } else {
    digitalWrite(LED_ONE, HIGH);
  }

  buttonTwoState = digitalRead(BUTTON_TWO_PIN);

  if (buttonTwoState == HIGH) {
    digitalWrite(LED_TWO, LOW);
  } else {
    digitalWrite(LED_TWO, HIGH);
  }

  delay(100);
}
