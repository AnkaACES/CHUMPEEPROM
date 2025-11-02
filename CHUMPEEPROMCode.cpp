#define a0 A4
#define a1 A3
#define a2 A2
#define a3 A1
#define e A5
#define d 9
#define c A0
#define b 5
#define a 2
#define f 3
#define g 4
#define dec 6
#define WE 7
#define OE 8

/*
//0 to F
byte digits[16] = {
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11110010, // 3
  0b01100110, // 4
  0b10110110, // 5
  0b10111110, // 6
  0b11100000, // 7
  0b11111110, // 8
  0b11110110, // 9
  0b11101110, // A
  0b00111110, // b
  0b10011100, // C
  0b01111010, // d
  0b10011110, // E
  0b10001110  // F
};
*/

/*
// Machine Code
byte digits[16] = {
  0b10000000,
  0b00010000,
  0b01001001,
  0b11000111,
  0b00100000,
  0b01110000,
  0b11000000,
  0b00101001,
  0b10000000,
  0b00010000,
  0b11100000,
  0b00100001,
  0b01110000,
  0b11000111,
  0b00000000,
  0b00000000
};
*/
/*
// Machine Code Upper Nibble
byte digits[16] = {
  0b11111110, // 8
  0b01100000, // 1
  0b01100110, // 4
  0b10011100, // C
  0b11011010, // 2
  0b11100000, // 7
  0b10011100, // C
  0b11011010, // 2
  0b11111110, // 8
  0b01100000, // 1
  0b10011110, // E
  0b10011100, // C
  0b11100000, // 7
  0b10011100, // C
  0b00000000,
  0b00000000
};
*/
/*
// Machine Code Lower Nibble
byte digits[16] = {
  0b11111100, // 0
  0b11111100, // 0
  0b11110110, // 9
  0b11100000, // 7
  0b11111100, // 0
  0b11111100, // 0
  0b11111100, // 0
  0b11110110, // 9
  0b11111100, // 0
  0b11111100, // 0
  0b11111100, // 0
  0b01100000, // 1
  0b11111100, // 0
  0b11100000, // 7
  0b00000000,
  0b00000000
};
*/
/*
// Feinberg Code
byte digits[16] = {
  0b10000010, 
  0b00010000,
  0b00100001,
  0b01100010,
  0b11000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};
*/
/*
// Feinberg Code Upper Nibble
byte digits[16] = {
  0b11111110, // 8
  0b01100000, // 1
  0b11011010, // 2
  0b10111110, // 6
  0b10011100, // C
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};
*/

// Feinberg Code Lower Nibble
byte digits[16] = {
  0b11011010, // 2
  0b11111100, // 0
  0b01100000, // 1
  0b11011010, // 2
  0b11111100, // 0
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

// The pin configurations to control the addresses
byte address[16] = {
  0b0000, 
  0b0001, 
  0b0010, 
  0b0011,
  0b0100, 
  0b0101, 
  0b0110, 
  0b0111,
  0b1000, 
  0b1001, 
  0b1010, 
  0b1011,
  0b1100, 
  0b1101, 
  0b1110, 
  0b1111,
};

void setup() {
  // Set Nano pins on output mode
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(a0, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(a3, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dec, OUTPUT);

  digitalWrite(WE, HIGH); // turn off writing mode
  digitalWrite(OE, HIGH); // input mode while writing

  // Flash the EEPROM
  for (uint8_t i = 0; i < 16; i++) {
    // Set the address
    digitalWrite(a0, (address[i] >> 0) & 1);
    digitalWrite(a1, (address[i] >> 1) & 1);
    digitalWrite(a2, (address[i] >> 2) & 1);
    digitalWrite(a3, (address[i] >> 3) & 1);

    // Provide the pin configuration for the address
    digitalWrite(a,   (digits[i] >> 7) & 1);
    digitalWrite(b,   (digits[i] >> 6) & 1);
    digitalWrite(c,   (digits[i] >> 5) & 1);
    digitalWrite(d,   (digits[i] >> 4) & 1);
    digitalWrite(e,   (digits[i] >> 3) & 1);
    digitalWrite(f,   (digits[i] >> 2) & 1);
    digitalWrite(g,   (digits[i] >> 1) & 1);
    digitalWrite(dec, (digits[i] >> 0) & 1);

    digitalWrite(WE, LOW);    // turn on writing mode for 1 microsecond
    delayMicroseconds(1);
    digitalWrite(WE, HIGH);   // turn off writing mode immediately
    delay(50);                // wait a little bit
  }

  // Turn on output mode after writing
  pinMode(a, INPUT);
  pinMode(b, INPUT);
  pinMode(c, INPUT);
  pinMode(d, INPUT);
  pinMode(e, INPUT);
  pinMode(f, INPUT);
  pinMode(g, INPUT);
  pinMode(dec, INPUT);
  digitalWrite(WE, HIGH); // disable write
  digitalWrite(OE, LOW);  // enable EEPROM outputs
}

void loop() {
  // Cycle through all addresses so EEPROM outputs the stored data
  for (uint8_t addr = 0; addr < 16; addr++) {
    digitalWrite(a0, (addr >> 0) & 1);
    digitalWrite(a1, (addr >> 1) & 1);
    digitalWrite(a2, (addr >> 2) & 1);
    digitalWrite(a3, (addr >> 3) & 1);
    delay(1000);
  }
}
