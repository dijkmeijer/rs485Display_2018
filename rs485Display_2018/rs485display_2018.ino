
#include <SPI.h>
#include <SoftwareSerial.h>

SPISettings settingsA(200000, MSBFIRST, SPI_MODE3);

byte lijst[] = {
  0b11101110, //0
  0b00101000, //1
  0b11001101, //2
  0b01101101, //3
  0b00101011, //4
  0b01100111, //5
  0b11100111, //6
  0b00101100, //7
  0b11101111, //8
  0b01101111, //9
};

const int chipSelectPin = 10;
const int enablePin = A1;


byte da = 0b10101111;
byte db = 0b11100011;
byte dc = 0b11000110;
byte dd = 0b11101001;
byte de = 0b11000111;


byte PUNT  = 0b00010000;
byte BLANK = 0b00000000;
byte c2[15];
int i;
byte a, b;

SoftwareSerial mySerial(0, 1); // RX, TX

int writeSpi(byte M, byte L);


void setup() {
  // initialize serial:
  SPI.begin();
  // initalize the  data ready and chip select pins:
  pinMode(enablePin, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);


  digitalWrite(enablePin, LOW);
  i = 0;
  mySerial.begin(9600);
  writeSpi(BLANK, BLANK);
}

int n;


void loop() {

  while (mySerial.available()) {
    c2[n] =  mySerial.read();
    if (c2[n] == '\n') {
      a = lijst[char(c2[0]) - '0'];
      if (n == 2)
      { b = a;
        a = BLANK;
      }
      else
        b = lijst[char(c2[1]) - '0'];
      writeSpi(a, b);
      n = 0;
    }
    else n++;
  }
}

int writeSpi(byte M, byte L) {
  digitalWrite(enablePin, HIGH);
  SPI.beginTransaction(settingsA);
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(L);
  SPI.transfer(M);

  digitalWrite(chipSelectPin, HIGH);
  SPI.endTransaction();
  digitalWrite(enablePin, LOW);
}




