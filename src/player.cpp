#include "player.h"

Player::Player(int left_pin_, int right_pin_, int button_pin_){
    left_pin = left_pin_;
    right_pin = right_pin_;
    button_pin = button_pin_;
}

void Player::click(){
    int8_t stick_new = digitalRead(left_pin) + digitalRead(right_pin) * -1;
    bool button_new = !digitalRead(button_pin);

    if(button != button_new && millis() - button_filter_timer >= BUTTON_FILTERING_TIME){
        button = button_new;
        button_filter_timer = millis();

        changed_state = true;
    }

    if(stick != stick_new){
        stick = stick_new;
        changed_state = true;
    }
}

bool Player::changed(){
    bool tmp = changed_state;
    changed_state = false;
    return tmp;
}