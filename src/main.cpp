#include <Arduino.h>

#include "config.h"
#include "indicator.hpp"
#include "player.h"
#include "game_wifi.h"
#include "reconnection.hpp"

Player player(STICK_LEFT, STICK_RIGHT, BUTTON);
Game_wifi wifi;

IRAM_ATTR void player_event(){
    player.click();
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(LATCH_PIN, HIGH);

  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);

  pinMode(STICK_LEFT, INPUT);
  pinMode(STICK_RIGHT, INPUT);
  pinMode(BUTTON, INPUT);

  attachInterrupt(digitalPinToInterrupt(STICK_LEFT), player_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(STICK_RIGHT), player_event, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON), player_event, CHANGE);

  wifi.init(motherboadrd_addr, DEFAULT_GAMEPAD_ID);

#ifdef DYNAMIC_MOTHERBOARD_ADDR
  if(digitalRead(BUTTON) == 0){
    wifi.change_id(select_id_process(player));
  }
#endif

  Serial.println("initialized");
  
  for(int i = 0; i <= 10; i++){
    set_score(i);
    delay(50);
  }
  delay(100);
}


void loop() {
    if(player.changed())
        wifi.send_player_state(player);
    
    wifi.update_recieved();
    set_score(wifi.score);  
}