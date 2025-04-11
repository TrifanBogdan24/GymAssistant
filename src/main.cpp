#include <Arduino.h>
#include <SD.h>                           // SD module library
#include <TMRpcm.h>                       // speaker control library  https://github.com/TMRh20/TMRpcm/archive/master.zip
#include <LiquidCrystal_I2C.h>            // I2C LCD library

// Pin indices
#define PIN_SD_CHIP_SELECT 10
#define PIN_BUTTON_VOLUME_DOWN 2
#define PIN_BUTTON_VOLUME_UP 3
#define PIN_BUTTON_PLAY_PAUSE 4
#define PIN_BUTTON_NEXT_SONG 5
#define PIN_SPEAKER 9
// For ultrasonic sensors:
#define PIN_TRIGGER 8
#define PIN_ECHO 7

/*
song01.wav - Roman Jewels - Rolling
song02.wav - Moldavite - Crank it!
song03.wav - NOES - Like a Boss
song04.wav - Indila - Tourner Dans Le Vide
*/

volatile int song_index = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
TMRpcm audio;

volatile int volume = 4;
volatile bool isPausePlayButtonPressed = false;

long duration, cm, inches;

void decreaseVolume()
{
  volume = max(volume - 1, 0);
  audio.setVolume(volume);
}

void increaseVolume()
{
  volume = min(volume + 1, 6);
  audio.setVolume(volume);
}

void play_pause()
{
  isPausePlayButtonPressed = true;
}


void nextSong()
{
  song_index = (song_index + 1) % 4 + 1;
  
  if (song_index == 1) {
    audio.play("songs/song01.wav");
  } else if (song_index == 2) {
    audio.play("songs/song02.wav");
  } else if (song_index == 3) {
    audio.play("songs/song03.wav");
  } else if (song_index == 4) {
    audio.play("songs/song04.wav");
  }

}


void setup() {
  Serial.begin(9600);

  // Folosesc rezistente de PULL-DOWN
  pinMode(PIN_BUTTON_VOLUME_DOWN, INPUT_PULLUP);
  pinMode(PIN_BUTTON_VOLUME_UP, INPUT_PULLUP);
  pinMode(PIN_BUTTON_PLAY_PAUSE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_NEXT_SONG, INPUT_PULLUP);

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_VOLUME_DOWN), decreaseVolume, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_VOLUME_UP), increaseVolume, FALLING); 


  audio.speakerPin = PIN_SPEAKER;

  while (!SD.begin(PIN_SD_CHIP_SELECT)) {
    Serial.println("SD init failed!");
    delay(100);
  }
  Serial.println("SD init success!");


  Serial.println("Playing audio...");

  song_index = 1;
  audio.play("songs/song01.wav");
  audio.setVolume(volume);

  lcd.init();
  lcd.backlight();
  lcd.print("Bine ai venit!");

}



void loop() {
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(PIN_ECHO, INPUT);
  duration = pulseIn(PIN_ECHO, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);
}
