#ifndef MYSD_H
#define MYSD_H

#include <SPI.h>
#include <SD.h>

class MySDClass {
  public:
    MySDClass(int chipSelectPin);
    void begin();
    void writeData(String data);
    void closeFile();
  private:
    int _chipSelectPin;
    File _dataFile;
};


#endif