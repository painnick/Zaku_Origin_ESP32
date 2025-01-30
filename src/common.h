#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

#define PIN_SERVO_TABLE 19
#define PIN_SERVO_WAIST 23

/**
 * Mono-eye
 */
#define PIN_EYE 4

#define CH_EYE 12

/**
 * Bazuka
 */
#define PIN_BAZUKA 18

#define CH_BAZUKA 13

/**
 * Backpack
 */
#define PIN_BACKPACK_A 16
#define PIN_BACKPACK_B 17

#define CH_BACKPACK 14

/**
 * Foot
 */
#define PIN_FOOT_A 21
#define PIN_FOOT_B 22

#define CH_FOOT 15