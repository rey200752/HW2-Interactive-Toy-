
const int button = A0;

const int RledPin = 3;
const int GledPin = 10;
const int BledPin = 11;

int mood = 10;
int lastButtonState = HIGH;

unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;

const unsigned long unTouchInterval = 5000;
const unsigned long reducedInterval = 1000;

void setup() {
  pinMode(button, INPUT);

  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  touchedTimer = millis();
  reducedTimer = millis();

  showLEDState(mood);
}

void loop() {
  unsigned long currentTimer = millis();
  int buttonState = digitalRead(button);

  if (buttonState == LOW && lastButtonState == HIGH) {
    if (mood < 20) {
      mood++;
    }

    touchedTimer = currentTimer;
    reducedTimer = currentTimer;

    showLEDState(mood);
    delay(30);
  }

  lastButtonState = buttonState;

  if (currentTimer - touchedTimer >= unTouchInterval) {
    if (currentTimer - reducedTimer >= reducedInterval) {
      if (mood > 0) {
        mood--;
        showLEDState(mood);
      }

      reducedTimer += reducedInterval;
    }
  }
}

void showLEDState(int points) {
  int redValue;
  int greenValue;
  int blueValue;

  if (points <= 10) {
    redValue = 255;
    greenValue = points * 25.5;
    blueValue = 0;
  } else {
    redValue = (20 - points) * 25.5;
    greenValue = 255;
    blueValue = (points - 10) * 25.5;
  }

  analogWrite(RledPin, 255 - redValue);
  analogWrite(GledPin, 255 - greenValue);
  analogWrite(BledPin, 255 - blueValue);
}
