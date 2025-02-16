#include <Arduino.h>

#include "common.h"
#include "controllers/Mp3Controller.h"

#define MAX_EASING_SERVOS 2
//#define DISABLE_COMPLEX_FUNCTIONS
//#define ENABLE_EASE_ELASTIC
#define DISABLE_MICROS_AS_DEGREE_PARAMETER

#include <ServoEasing.hpp>

#define MAIN_TAG "Main"

#define TABLE_SERVO_DEFAULT_DEGREE 90

#define WAIST_SERVO_DEFAULT_DEGREE 90
#define WAIST_SERVO_UP_DEGREE 75

#define EYE_BRIGHT_NORMAL 23
#define EYE_BRIGHT_MAX 255

ServoEasing tableServo, waistServo;

int lastTableDegree = TABLE_SERVO_DEFAULT_DEGREE;

int move();

void fire();

void setup() {
  ESP_LOGI(MAIN_TAG, "Setup...");

  setupSound();

  ESP_LOGI(MAIN_TAG, "Setup Mono-eye");
  ledcSetup(CH_EYE, 1000, 8);
  ledcAttachPin(PIN_EYE, CH_EYE);
  ledcWrite(CH_EYE, EYE_BRIGHT_NORMAL);

  ESP_LOGI(MAIN_TAG, "Setup Bazuka");
  pinMode(PIN_BAZUKA, OUTPUT);

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
  tableServo.setEasingType(EASE_ELASTIC_IN_OUT);

  ESP_LOGI(MAIN_TAG, "Setup Waist-servo");
  waistServo.attach(PIN_SERVO_WAIST, WAIST_SERVO_DEFAULT_DEGREE);

  delay(3000);
}

void loop() {
  int diff = move();
  delay(min(diff * diff, 1000));
  dfmp3.loop();
}

int move() {
  int diff = 0;

  ledcWrite(CH_BACKPACK, 195);
  ledcWrite(CH_FOOT, 195);
  delay(500);

  int degree;
  while (true) {
    degree = random(0, 180);
    diff = abs(lastTableDegree - degree);
    if (diff > 30) {
      lastTableDegree = degree;
      break;
    }
  }

  uint_fast16_t speed = random(15, 30);
  ESP_LOGD(MAIN_TAG, "Move to %d(spd %d)", degree, speed);
  tableServo.easeTo(degree, speed);
  ledcWrite(CH_BACKPACK, 0);
  ledcWrite(CH_FOOT, 0);

  if (random(0, 3) != 0) {
    delay(random(300, 1000));
    fire();
  }

  return diff;
}

void fire() {
  ESP_LOGI(MAIN_TAG, "Fire!");
  ledcWrite(CH_EYE, EYE_BRIGHT_MAX);
  delay(400);
  ledcWrite(CH_EYE, (EYE_BRIGHT_MAX + EYE_BRIGHT_NORMAL) / 2);
  delay(100);
  ledcWrite(CH_EYE, (EYE_BRIGHT_MAX + EYE_BRIGHT_NORMAL) / 4);
  delay(100);
  ledcWrite(CH_EYE, EYE_BRIGHT_NORMAL);
  delay(700);

  playBazuka();
  delay(300);

  digitalWrite(PIN_BAZUKA, HIGH);

  waistServo.easeTo(WAIST_SERVO_UP_DEGREE, 180);
  delay(200);
  digitalWrite(PIN_BAZUKA, LOW);
  waistServo.easeTo(WAIST_SERVO_DEFAULT_DEGREE, 180);
}