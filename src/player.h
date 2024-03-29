#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "config.h"

class Player{
    int left_pin, right_pin, button_pin;

    int8_t last_stick = 0;
    bool last_button = 0;

    bool changed_state = false;

    uint64_t button_filter_timer = 0;
public:
    int8_t stick = 0;
    bool button = 0;

    Player(int left_pin_, int right_pin_, int button_pin_);

    void click();

    bool changed();
};

#endif