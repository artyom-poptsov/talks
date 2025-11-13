const int SPEAKER = 2;

// Октавная система.
const float c0 = 16.352;
const float d0 = 18.354;
const float e0 = 20.602;
const float f0 = 21.827;
const float g0 = 24.500;
const float a0 = 27.500;
const float b0 = 30.868;

const float c1 = c0 * 2;

const float c2 = c0 * 4;

const float c3 = c0 * 8;
const float b3 = b0 * 8;

const float c4 = c0 * 16;
const float d4 = d0 * 16;
const float e4 = e0 * 16;
const float e4b = (e4 + d4) / 2;
const float f4 = f0 * 16;
const float g4 = g0 * 16;
const float f4s = (f4 + g4) / 2; // F4 Диез (F4#, F4 Sharp)
const float a4 = a0 * 16;
const float b4 = b0 * 16;

const float c5 = c0 * 32;
const float d5 = d0 * 32;

const float R = 0; // Rest -- Покой, пауза.

void setup() {
  pinMode(SPEAKER, OUTPUT);
}

void play_tone(int pin, float f , long t) {
  if (f > 0) {
    const long T = 1000000 / f;
    long d = T / 2;
    long count = t / T;
    for (int c = 0; c < count; c++) {
      digitalWrite (pin, 1);
      delayMicroseconds(d);
      digitalWrite (pin, 0);
      delayMicroseconds(d);
    }
  } else {
    delay(t / 1000);
  }
}

// "Twinkle, Twinkle, Little Star"
float melody[][2] = {
  /* 0 */ {c4, 4}, {c4, 4}, {g4, 4}, {g4, 4},
  /* 1 */ {a4, 4}, {a4, 4}, {g4, 2},
  /* 2 */ {f4, 4}, {f4, 4}, {e4, 4}, {e4, 4},
  /* 3 */ {d4, 4}, {d4, 4}, {c4, 2},
  /* 4 */ {g4, 4}, {g4, 4}, {f4, 4}, {f4, 4},
  /* 5 */ {e4, 4}, {e4, 4}, {d4, 2},
  /* 6 */ {g4, 4}, {g4, 4}, {f4, 4}, {f4, 4},
  /* 7 */ {e4, 4}, {e4, 4}, {d4, 2},
};

float prostokvashino[][2] = {
  /* 1 */ {b3, 8}, {b3, 8}, {b4, 16.0 / 3.0}, {f4s, 16}, {a4, 8}, {g4, 8}, {e4, 4},
  /* 2 */ {d4, 8}, {d4, 8}, {d5, 16.0 / 3.0}, {c5, 16}, {c5, 8},  {b4, 8}, {R, 4}
};

void loop() {
  const int BPM = 90; // Beats Per Minute
  const long MINUTE = 60000000;
  const long MEASURE = (MINUTE / BPM) * 4;

  int n = sizeof(melody) / sizeof(melody[0]);
  for (int i = 0; i < n; i++) {
    play_tone(SPEAKER, melody[i][0], MEASURE / melody[i][1]);
    delay(10);  
  }

//  float a[] = {
//    c4, e4, g4
//  };
//  float b[] = {
//    c4, e4b, g4
//  };
//  for (float j = 1.1; j < 4; j += 0.1) {
//    for (int i = 0; i < 3; i++) {
//      play_tone(SPEAKER, a[i] * j, T / j);
//    }
//  }
//  for (float j = 4; j > 1; j -= 0.1) {
//    for (int i = 0; i < 3; i++) {
//      play_tone(SPEAKER, b[i] * j, T / j);
//    }
//  }
}
