#include <GyverFIFO.h>
GyverFIFO<int, 16> buf;
// тип данных: любой. byte/int/float...
// размер буфера: код выполняется быстрее при 
// размере буфера, кратном степени двойки (2, 4, 8, 16, 32...)

void setup() {
  Serial.begin(9600);
  buf.write(12);
  buf.write(34);
  buf.write(56);
  for (int i = 3; i < 16; i++) {
    buf.write(i);
  }
  Serial.println(buf.availableForWrite());
  Serial.println(buf.available());
  while (buf.available()) {
    Serial.println(buf.read());
  }
}

void loop() {
}
