#include "player.h"

Player::Player(int left_pin_, int right_pin_, int button_pin_){
    left_pin = left_pin_;
    right_pin = right_pin_;
    button_pin = button_pin_;
}

void Player::click(){
    stick = digitalRead(left_pin) + digitalRead(right_pin) * -1;

    button = !digitalRead(button_pin);

    changed_state = true;
}

bool Player::changed(){
    bool tmp = changed_state;
    changed_state = false;
    return tmp;
}