#include <mySDCard/mySD.h>

MySDClass::MySDClass(int chipSelectPin) {
  _chipSelectPin = chipSelectPin;
}

void MySDClass::begin() {
  if (!SD.begin(_chipSelectPin)) {
    Serial.println(String(_chipSelectPin));
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");
}

void MySDClass::writeData(String data) {
  _dataFile = SD.open("data.txt", FILE_WRITE);

  if (_dataFile) {
    _dataFile.println(data);
    Serial.println("Data written to file.");
  } else {
    Serial.println("Error opening file.");
  }
}

void MySDClass::closeFile() {
  if (_dataFile) {
    _dataFile.close();
    Serial.println("File closed.");
  }
  // SD.end();
}

