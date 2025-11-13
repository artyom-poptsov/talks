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
  const int BPM = 95;
  const long MINUTE = 60000000;
  const long MEASURE = (MINUTE / BPM) * 4;
  for (int i = 0; i < 4; i++) {
    play_tone(2, 50, MEASURE / 8);
    delay(10);
  }
  for (int i = 0; i < 3; i++) {
    play_tone(2, 100, MEASURE / 4);
    delay(10);
    play_tone(2, 250, MEASURE / 8);
    delay(10);
    play_tone(2, 250, MEASURE / 8);
    delay(10);
    play_tone(2, 50, MEASURE / 4);
    delay(10);
    play_tone(2, 250, MEASURE / 8);
    delay(10);
    play_tone(2, 150, MEASURE / 8);
    delay(10);
  }
}
