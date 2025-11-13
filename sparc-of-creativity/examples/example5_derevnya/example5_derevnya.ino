float c0 = 16.352;
float d0 = 18.354;
float e0 = 20.602;
float f0 = 21.827;
float g0 = 24.500;
float a0 = 27.500;
float b0 = 30.868;

float c1 = c0 * 2;
float c2 = c0 * 4;

float c3 = c0 * 8;
float b3 = b0 * 8;

float c4 = c0 * 16;
float d4 = d0 * 16;
float e4 = e0 * 16;
float e4f = (e4 + d4) / 2; // E4b = Бемоль (Flat)
float f4 = f0 * 16;
float g4 = g0 * 16;
float f4s = (f4 + g4) / 2; // F4# = Диез (Sharp)
float a4 = a0 * 16;
float b4 = b0 * 16;

float c5 = c0 * 32;
float d5 = d0 * 32;
float e5 = e0 * 32;
float f5 = f0 * 32;
float g5 = g0 * 32;
float a5 = a0 * 32;
float a5f = (a5 + g5) / 2; // a5 бемоль (flat)
float b5 = b0 * 32;
float b5f = (b5 + a5) / 2;

float c6 = c0 * 64;
float d6 = d0 * 64;
float d6f = (d6 + c6) / 2;
float c6s = (c6 + d6) / 2;
float e6 = e0 * 64;
float e6f = (e6 + d6) / 2;
float f6 = f0 * 64;
float g6 = g0 * 64;
float f6s = (f6 + g6) / 2;

float R = 0; // Rest -- Пауза, покой

void setup() {
  pinMode(2, OUTPUT);
}

void play_tone(int port, float f, long t) {
  if (f > 0) {
    const long T = 1000000 / f; // Период
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

float melody[14][2] = {
  {b3, 8}, {b3, 8}, {b4, 16.0 / 3.0}, {f4, 16}, {a4, 8}, {g4, 8}, {e4, 4},
  {d4, 8}, {d4, 8}, {d5, 16.0 / 3.0}, {c5, 16}, {c5, 8}, {b4, 8}, {R,  4}
};

float derevnya[][2] = {
  // 1
  {a5f, 8}, {b5f, 8}, {a5f, 8}, {g5, 8},
  {a5f, 8}, {b5f, 8}, {c6, 8}, {d6f, 8},
  // 2
  {e6f, 8}, {R, 8}, {c6, 8}, {R, 8},
  {c6, 4}, {R, 4},
  // 3
  {f6s, 8}, {R, 8}, {e6f, 8}, {R, 8},
  {e6f, 4}, {R, 4},
  // 4
  {e6f, 8}, {R, 8}, {c6, 8}, {R, 8},
  {c6, 4}, {R, 4},
  // 5
  {a5f, 8}, {b5f, 8}, {a5f, 8}, {g5, 8},
  {a5f, 8}, {b5f, 8}, {c6, 8}, {d6f, 8},
  // 6
  {e6f, 8}, {R, 8}, {c6, 8}, {R, 8},
  {c6, 4}, {R, 4},
  // 7 
  {d6, 8}, {c6, 8}, {b5f, 8}, {R, 8}, 
  {d6f, 8}, {c6, 8}, {b5f, 8}, {R, 8},
  // 8
  {e6f, 4}, {R, 4}, {R, 2},
};

void loop() {
  const int BPM = 220; // Beats per Minute -- Удары в минуту
  const long MINUTE = 60000000;
  const long TAKT = (MINUTE / BPM) * 4;
  int m = sizeof(derevnya) / sizeof(derevnya[0]);
  for (int n = 0; n < m; n++) {
    play_tone(2, derevnya[n][0], TAKT / derevnya[n][1]);
    delay(10);
  }
}
