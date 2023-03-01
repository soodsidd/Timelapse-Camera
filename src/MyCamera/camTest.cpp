#include <Wire.h>
#include <ArduCAM.h>
#include <SPI.h>

// Arducam configuration parameters
#define CS_PIN 10
#define WIDTH 160
#define HEIGHT 120
#define BMPIMAGEOFFSET 66
#define BMPHEADER 54

ArduCAM myCAM(OV2640, CS_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize Arducam
  myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
  uint8_t val = myCAM.read_reg(ARDUCHIP_TEST1);
  if (val != 0x55) {
    Serial.println("Arducam initialization failed");
    while (1);
  }

  myCAM.InitCAM();
  myCAM.set_format(JPEG);
  myCAM.OV2640_set_JPEG_size(OV2640_160x120);
  myCAM.write_reg(ARDUCHIP_TIM, VSYNC_LEVEL_MASK);
}

void loop() {
  // Capture image
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  myCAM.start_capture();

  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK)) {
    // Wait for capture to complete
  }

  // Read image data
  uint32_t length = myCAM.read_fifo_length();
// Get the length of the image data in the FIFO buffer
uint32_t length = myCAM.read_fifo_length();

// Allocate a buffer to store the image data
uint8_t *imageData = new uint8_t[length];

// Read the entire image data from the FIFO buffer into the buffer
for (int i = 0; i < length; i++) {
  imageData[i] = myCAM.read_fifo();
  Serial.println(imageData[i]);
  // Print a space between each byte of data for readability
  Serial.print(' ');
}

  Serial.println(*imageData);

  // Save image to SD card
  // saveImage(imageData, length);

  // Free memory
  delete[] imageData;

  delay(1000);
}

// void saveImage(uint8_t *imageData, uint32_t length) {
//   // Open file on SD card
//   File file = SD.open("image.jpg", FILE_WRITE | O_TRUNC | O_CREAT);

//   // Write image data to file
//   file.write(0xFF);
//   file.write(0xD8);
//   file.write(imageData + BMPIMAGEOFFSET, length - BMPIMAGEOFFSET);
//   file.write(0xFF);
//   file.write(0xD9);

//   // Close file
//   file.close();

//   Serial.println("Image saved to SD card");
// }