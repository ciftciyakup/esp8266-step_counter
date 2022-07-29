#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "config.h"

long timer = 0;
int steps = 0;
int kalori = 0;
unsigned long eskiZaman = 0;
unsigned long yeniZaman;
float distanceinonestep = 71; //change it according to your distance between your legs in cm
float distance;
int range=0;

Adafruit_MPU6050 mpu;
AdafruitIO_Feed *counter = io.feed("adim-sayaci");
AdafruitIO_Feed *mesafe = io.feed("mesafe");
AdafruitIO_Feed *calori = io.feed("kalori");
AdafruitIO_Feed *mesafeAl = io.feed("mesafe-al");


void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  io.connect();

  mesafeAl->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

  while (io.mqttStatus() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  mesafeAl->get();
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  io.run();

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  if(millis() - timer > 1000){
    Serial.print("accY : ");Serial.print(a.acceleration.y);
  }
  if (a.acceleration.y > 1)
  {
    steps += 1;
    delay(350);
  }
  yeniZaman = millis();
  if (yeniZaman - eskiZaman > 3000) {
    Serial.print("Steps ");
    Serial.println(steps);
    counter->save(steps);

    kalori=steps*0.05;
    Serial.print("Kalori: ");
    Serial.println(kalori);
    calori->save(kalori);

    distance = steps * distanceinonestep / 100;
    Serial.print("Distance ");
    Serial.println(distance);
    mesafe->save(distance);
    delay(100);
    eskiZaman = yeniZaman;
  }

  Serial.println("");
  delay(500);

  
  if(distance>=range){
    Serial.println("Hedefinize ulaştınız");
  }
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");
  Serial.println(data->value());
  range = data->toInt();
  Serial.println(range);
}
