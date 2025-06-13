/*
Clock Software for an 11x27 LED Matrix made from ARGB LED Strips.
Please see the Readme file for Wiring diagramm and how the LED Strips need to be
wired and placed!

Build: 12.06.2025
Version: 1.0.4
Author: Mister1000Craft
*/

// Segments:
/*
  oxxxo
  xooox
  xooox
  xooox
  oxxxo
  xooox
  xooox
  xooox
  oxxxo

  N 1_1 N
  1_2 N 1_3
  N 1_4 N
  1_5 N 1_6
  N 1_7 N
*/
// Include Librarys
  #include <FastLED.h> // By Daniel Garcia Version 3.9.16

// Example
  #include <Wire.h>
  #include "RTClib.h"
  RTC_DS3231 rtc;

// Define LED Values
  #define LED_PIN 13
  #define NUM_LEDS 297
  #define Zeile 11
  #define Spalte 27
  #define BRIGHTNESS 100
  #define LED_TYPE WS2812B
  #define COLOR_ORDER GRB

  CRGB leds[NUM_LEDS];

// Segment dicitonary, Wiring type 2
char* dict[11][27] = {
    {"N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N"},
    {"N", "N", "4_1", "4_1", "4_1", "N" "N" "N", "3_1", "3_1", "3_1", "N", "N", "N", "N", "N", "2_1", "2_1", "2_1", "N", "N", "N", "1_1", "1_1", "1_1", "N", "N"},
    {"N", "1_2", "N", "N", "N", "1_3", "N", "2_2", "N", "N", "N", "2_3", "N", "N", "N", "3_2", "N", "N", "N", "3_3", "N", "4_2", "N", "N", "N", "4_3", "N"},
    {"N", "4_3", "N", "N", "N", "4_2", "N", "3_3", "N", "N", "N", "3_2", "N", "N", "N", "2_3", "N", "N", "N", "2_2", "N", "1_3", "N", "N", "N", "1_2", "N"},
    {"N", "1_2", "N", "N", "N", "1_3", "N", "2_2", "N", "N", "N", "2_3", "N", "P", "N", "3_2", "N", "N", "N", "3_3", "N", "4_2", "N", "N", "N", "4_3", "N"},
    {"N", "N", "4_4", "4_4", "4_4", "N" "N" "N", "3_4", "3_4", "3_4", "N", "N", "N", "N", "N", "2_4", "2_4", "2_4", "N", "N", "N", "1_4", "1_4", "1_4", "N", "N"},
    {"N", "1_5", "N", "N", "N", "1_6", "N", "2_5", "N", "N", "N", "2_6", "N", "P", "N", "3_5", "N", "N", "N", "3_6", "N", "4_5", "N", "N", "N", "4_6", "N"},
    {"N", "4_6", "N", "N", "N", "4_5", "N", "3_6", "N", "N", "N", "3_5", "N", "N", "N", "2_6", "N", "N", "N", "2_5", "N", "1_6", "N", "N", "N", "1_5", "N"},
    {"N", "1_5", "N", "N", "N", "1_6", "N", "2_5", "N", "N", "N", "2_6", "N", "N", "N", "3_5", "N", "N", "N", "3_6", "N", "4_5", "N", "N", "N", "4_6", "N"},
    {"N", "N", "4_7", "4_7", "4_7", "N" "N" "N", "3_7", "3_7", "3_7", "N", "N", "N", "N", "N", "2_7", "2_7", "2_7", "N", "N", "N", "1_7", "1_7", "1_7", "N", "N"},
    {"N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N"}
};


// Segment/Matrix dicionary
const bool digitSegments[10][7] = {
  { 1, 1, 1, 0, 1, 1, 1 }, // 0
  { 0, 0, 1, 0, 0, 1, 0 }, // 1
  { 1, 0, 1, 1, 1, 0, 1 }, // 2
  { 1, 0, 1, 1, 0, 1, 1 }, // 3
  { 0, 1, 1, 1, 0, 1, 0 }, // 4
  { 1, 1, 0, 1, 0, 1, 1 }, // 5
  { 1, 1, 0, 1, 1, 1, 1 }, // 6
  { 1, 0, 1, 0, 0, 1, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1 }, // 8
  { 1, 1, 1, 1, 0, 1, 1 }  // 9
};

bool s1_1 = false;
bool s1_2 = false;
bool s1_3 = false;
bool s1_4 = false;
bool s1_5 = false;
bool s1_6 = false;
bool s1_7 = false;

bool s2_1 = false;
bool s2_2 = false;
bool s2_3 = false;
bool s2_4 = false;
bool s2_5 = false;
bool s2_6 = false;
bool s2_7 = false;

bool s3_1 = false;
bool s3_2 = false;
bool s3_3 = false;
bool s3_4 = false;
bool s3_5 = false;
bool s3_6 = false;
bool s3_7 = false;

bool s4_1 = false;
bool s4_2 = false;
bool s4_3 = false;
bool s4_4 = false;
bool s4_5 = false;
bool s4_6 = false;
bool s4_7 = false;

bool N = false;
bool P = false;

int hour;
int minute;

int d1 = 0;
int d2 = 0;
int d3 = 0;
int d4 = 0;

// Segment data calculating
  bool isActive(char* word) 
    {
      if (strcmp(word, "N") == 0) return N;
      if (strcmp(word, "P") == 0) return P;

      if (strcmp(word, "1_1") == 0) return s1_1;
      if (strcmp(word, "1_2") == 0) return s1_2;
      if (strcmp(word, "1_3") == 0) return s1_3;
      if (strcmp(word, "1_4") == 0) return s1_4;
      if (strcmp(word, "1_5") == 0) return s1_5;
      if (strcmp(word, "1_6") == 0) return s1_6;
      if (strcmp(word, "1_7") == 0) return s1_7;

      if (strcmp(word, "2_1") == 0) return s2_1;
      if (strcmp(word, "2_2") == 0) return s2_2;
      if (strcmp(word, "2_3") == 0) return s2_3;
      if (strcmp(word, "2_4") == 0) return s2_4;
      if (strcmp(word, "2_5") == 0) return s2_5;
      if (strcmp(word, "2_6") == 0) return s2_6;
      if (strcmp(word, "2_7") == 0) return s2_7;

      if (strcmp(word, "3_1") == 0) return s3_1;
      if (strcmp(word, "3_2") == 0) return s3_2;
      if (strcmp(word, "3_3") == 0) return s3_3;
      if (strcmp(word, "3_4") == 0) return s3_4;
      if (strcmp(word, "3_5") == 0) return s3_5;
      if (strcmp(word, "3_6") == 0) return s3_6;
      if (strcmp(word, "3_7") == 0) return s3_7;

      if (strcmp(word, "4_1") == 0) return s4_1;
      if (strcmp(word, "4_2") == 0) return s4_2;
      if (strcmp(word, "4_3") == 0) return s4_3;
      if (strcmp(word, "4_4") == 0) return s4_4;
      if (strcmp(word, "4_5") == 0) return s4_5;
      if (strcmp(word, "4_6") == 0) return s4_6;
      if (strcmp(word, "4_7") == 0) return s4_7;
    }

void setup() {
// RTC - Example
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

// Init LED Strips
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
//  hour = // Your Hour Input
//  minute = // Your Minute Input


//  Example using RTC-Module  
  DateTime now = rtc.now();

  hour = now.hour();
  minute = now.minute();

// Clock logic
  d1 = hour / 10;
  d2 = hour % 10;
  d3 = minute / 10;
  d4 = minute % 10;

  s1_1 = digitSegments[d1][0];
  s1_2 = digitSegments[d1][1];
  s1_3 = digitSegments[d1][2];
  s1_4 = digitSegments[d1][3];
  s1_5 = digitSegments[d1][4];
  s1_6 = digitSegments[d1][5];
  s1_7 = digitSegments[d1][6];

  s2_1 = digitSegments[d2][0];
  s2_2 = digitSegments[d2][1];
  s2_3 = digitSegments[d2][2];
  s2_4 = digitSegments[d2][3];
  s2_5 = digitSegments[d2][4];
  s2_6 = digitSegments[d2][5];
  s2_7 = digitSegments[d2][6];

  s3_1 = digitSegments[d3][0];
  s3_2 = digitSegments[d3][1];
  s3_3 = digitSegments[d3][2];
  s3_4 = digitSegments[d3][3];
  s3_5 = digitSegments[d3][4];
  s3_6 = digitSegments[d3][5];
  s3_7 = digitSegments[d3][6];

  s4_1 = digitSegments[d4][0];
  s4_2 = digitSegments[d4][1];
  s4_3 = digitSegments[d4][2];
  s4_4 = digitSegments[d4][3];
  s4_5 = digitSegments[d4][4];
  s4_6 = digitSegments[d4][5];
  s4_7 = digitSegments[d4][6];

  for (int z=0; z<27; z++)
    {
      for (int s=0; s<11; s++)
        {
          char* word = dict[27][11];
          int currentled = (z * 27) + s;
          if (isActive(word))
            {
              leds[currentled] = CRGB::Blue;
              FastLED.show();
            }
          else
            {
              leds[currentled] = CRGB::Black;
              FastLED.show();
            }
        }
    }

}