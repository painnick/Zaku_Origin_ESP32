#include <Arduino.h>

#include "common.h"
#include "controllers/Mp3Controller.h"

#define MAX_EASING_SERVOS 1
// #define DISABLE_COMPLEX_FUNCTIONS
#define ENABLE_EASE_ELASTIC
#define DISABLE_MICROS_AS_DEGREE_PARAMETER
#define ENABLE_EASE_PRECISION

#include <ServoEasing.hpp>

#define MAIN_TAG "Main"

#define TABLE_SERVO_DEFAULT_DEGREE 90

#define WAIST_SERVO_DEFAULT_DEGREE 90
#define WAIST_SERVO_UP_DEGREE 80

ServoEasing tableServo;
Servo waistServo;

void fire();

void setup() {
  ESP_LOGI(MAIN_TAG, "Setup...");

  setupSound();

  ESP_LOGI(MAIN_TAG, "Setup Mono-eye");
  ledcSetup(CH_EYE, 1000, 8);
  ledcAttachPin(PIN_EYE, CH_EYE);

  ESP_LOGI(MAIN_TAG, "Setup Bazuka");
  ledcSetup(CH_BAZUKA, 1000, 8);
  ledcAttachPin(PIN_BAZUKA, CH_BAZUKA);

  ESP_LOGI(MAIN_TAG, "Setup backpack");
  ledcSetup(CH_BACKPACK, 1000, 8);
  ledcAttachPin(PIN_BACKPACK_A, CH_BACKPACK);
  ledcAttachPin(PIN_BACKPACK_B, CH_BACKPACK);

  ESP_LOGI(MAIN_TAG, "Setup Foot");
  ledcSetup(CH_FOOT, 1000, 8);
  ledcAttachPin(PIN_FOOT_A, CH_FOOT);
  ledcAttachPin(PIN_FOOT_B, CH_FOOT);

  ESP_LOGI(MAIN_TAG, "Setup Table-servo");
  tableServo.attach(PIN_SERVO_TABLE, TABLE_SERVO_DEFAULT_DEGREE);
  //  tableServo.setEasingType(EASE_ELASTIC_IN_OUT);

  ESP_LOGI(MAIN_TAG, "Setup Waist-servo");
  waistServo.attach(PIN_SERVO_WAIST);
  waistServo.write(WAIST_SERVO_DEFAULT_DEGREE);

  delay(3000);
}

unsigned long lastChecked = 0;

void loop() {
  const unsigned long now = millis();
  if (lastChecked == 0) {
    lastChecked = now;
    return;
  }
  if (now - lastChecked > 1000 * 3) {
    int right = random(0, 90);
    uint_fast16_t speed1 = random(30, 60);
    ESP_LOGI(MAIN_TAG, "Move to %d(spd %d)", right, speed1);
    tableServo.easeTo(right, speed1);

    if (random(0, 2) == 0) {
      delay(2000);
      fire();
    } else {
      delay(1000);
    }

    int left = random(90, 180);
    uint_fast16_t speed2 = random(30, 60);
    ESP_LOGI(MAIN_TAG, "Move to %d(spd %d)", left, speed2);
    tableServo.easeTo(left, speed2);

    if (random(0, 2) == 0) {
      delay(2000);
      fire();
    } else {
      delay(1000);
    }

    lastChecked = millis();
  }

  dfmp3.loop();
}

void fire() {
  ESP_LOGI(MAIN_TAG, "Fire!");
  playBazuka();
  delay(500);
  waistServo.write(WAIST_SERVO_UP_DEGREE);
  delay(200);
  waistServo.write(WAIST_SERVO_DEFAULT_DEGREE);
}