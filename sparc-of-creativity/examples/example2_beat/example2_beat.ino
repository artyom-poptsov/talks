void setup() {
  pinMode(2, OUTPUT);
}

void play_tone(int port, float f, long t) {
  const long T = 1000000 / f; // Период
  long d = T / 2;
  int count = t / T;
  for (int n = 0; n < count; n++) {
    digitalWrite(port, HIGH);
    delayMicroseconds(d);
    digitalWrite(port, LOW);
    delayMicroseconds(d);
  }
}

void beat(float m, long t) {
  play_tone(2, 32 * m, t);
  delay(10);
  play_tone(2, 64 * m, t);
  delay(10);
  play_tone(2, 32 * m, t);
  delay(10);
  play_tone(2, 128 * m, t);
  delay(10);
}

void loop() {
  long t = 100000;
  for (int i = 0; i <= 4; i++) {
    beat(1 + i, t);
    beat(2 + i, t);
    beat(1 + i, t);
    beat(4 + i, t);
  }
  for (int i = 4; i >= 0; i--) {
    beat(1 + i, t);
    beat(2 + i, t);
    beat(1 + i, t);
    beat(4 + i, t);
  }
}
