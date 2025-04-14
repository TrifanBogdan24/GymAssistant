#include <Arduino.h>
#include <SD.h>                           // SD module library
#include <TMRpcm.h>                       // speaker control library  https://github.com/TMRh20/TMRpcm/archive/master.zip
#include <LiquidCrystal_I2C.h>            // I2C LCD library
#include <EnableInterrupt.h>


// Pin indices
#define PIN_SD_CHIP_SELECT 10
#define PIN_BUTTON_VOLUME_DOWN 2
#define PIN_BUTTON_VOLUME_UP 3
#define PIN_BUTTON_PLAY_PAUSE 4
#define PIN_BUTTON_NEXT_SONG 5
#define PIN_SPEAKER 9
// For ultrasonic sensors:
#define PIN_TRIGGER 8
#define PIN_ECHO_1 7
#define PIN_ECHO_2 6


/*
song01.wav - Remember The Name (Official Video) - Fort Minor
song02.wav - Moldavite - Crank it!
song03.wav - NOES - Like a Boss
song04.wav - Indila - Tourner Dans Le Vide
*/

volatile int song_index = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
TMRpcm audio;

volatile int volume = 4;
volatile bool isPausePlayButtonPressed = false;
volatile bool isPaused = false;
volatile bool isChangedVolume = false;


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
  audio.pause();
  isPaused = !isPaused;
}


void nextSong()
{
  song_index = (song_index + 1) % 4;
  isPaused = false;
  
  if (song_index == 0) {
    audio.play("songs/song01.wav");
  } else if (song_index == 1) {
    audio.play("songs/song02.wav");
  } else if (song_index == 2) {
    audio.play("songs/song03.wav");
  } else if (song_index == 3) {
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
  pinMode(PIN_ECHO_1, INPUT);
  pinMode(PIN_ECHO_2, INPUT);

  enableInterrupt(PIN_BUTTON_PLAY_PAUSE, play_pause, FALLING);
  enableInterrupt(PIN_BUTTON_NEXT_SONG, nextSong, FALLING);

  enableInterrupt(PIN_BUTTON_VOLUME_DOWN, decreaseVolume, FALLING);
  enableInterrupt(PIN_BUTTON_VOLUME_UP, increaseVolume, FALLING);

  audio.speakerPin = PIN_SPEAKER;

  while (!SD.begin(PIN_SD_CHIP_SELECT)) {
    Serial.println("SD init failed!");
    delay(100);
  }
  Serial.println("SD init success!");


  Serial.println("Playing audio...");

  song_index = 0;
  audio.play("songs/song01.wav");
  audio.setVolume(volume);

  lcd.init();
  lcd.backlight();
  lcd.print("Bine ai venit!");

}



void loop() {
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
  long duration1 = pulseIn(PIN_ECHO_1, HIGH);

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);

  long duration2 = pulseIn(PIN_ECHO_2, HIGH);


 
  long distance1 = duration1 / 58.31;
  long distance2 = duration2 / 58.31;





  delay(50);
}
