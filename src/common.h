#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

// C3 PWM available on: 1-10,18-21

#define PIN_MP3_TX 5 // dfplayer(FIXED)
#define PIN_MP3_RX 6 // dfplayer(FIXED)

#define PIN_SERVO_TABLE 7
#define PIN_SERVO_WAIST 1

/**
 * Mono-eye
 */
#define PIN_EYE 3

#define CH_EYE 2

/**
 * Bazuka
 */
#define PIN_BAZUKA 0

/**
 * Backpack
 */
#define PIN_BACKPACK_A 20
#define PIN_BACKPACK_B 21

#define CH_BACKPACK 4

/**
 * Foot
 */
#define PIN_FOOT_A 4
#define PIN_FOOT_B 10

#define CH_FOOT 5