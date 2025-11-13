void setup() {
  pinMode(2, OUTPUT);
}

void play_tone(int port, float f, long t) {
  if (f > 0) {
    const long T = 1000000 / f;
    long d = T / 2;
    int count = t / T;
    for (int n = 0; n < count; n++) {
      digitalWrite(port, HIGH);
      delayMicroseconds(d);
      digitalWrite(port, LOW);
      delayMicroseconds(d);
    }
  } else {
    delay(t / 1000);
  }
}

void loop() {
  for (float f = 50; f < 1000; f = f * 1.2) {
    play_tone(2, f, 10000);
  }
  for (float f = 1000; f > 50; f = f / 1.2) {
    play_tone(2, f, 10000);
  }
}
