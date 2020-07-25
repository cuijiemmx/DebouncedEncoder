#include "DebouncedEncoder.h"

DebouncedEncoder encoder(4, 0);

volatile int count = 0;

void setup() {
  Serial.begin(9600);

  encoder.setLeftRotationHandler(rotateLeft);
  encoder.setRightRotationHandler(rotateRight);
}

void rotateLeft(DebouncedEncoder& encoder) {
  count -= 1;
  Serial.println(count);
}

void rotateRight(DebouncedEncoder& encoder) {
  count += 1;
  Serial.println(count);
}

void loop() {
  encoder.loop();
}
