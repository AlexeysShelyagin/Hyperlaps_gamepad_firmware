#ifndef RECONNECTION_HPP
#define RECONNECTION_HPP

#include <Arduino.h>
#include "player.h"
#include "indicator.hpp"

uint8_t select_id_process(Player &player){
    int8_t new_id = 0;
    player.changed();
    bool pressed = true;

    while(!player.button || pressed){
        if(player.changed()){
            new_id += player.stick;
            Serial.println(new_id);
            new_id = max(new_id, (int8_t) 0);
            new_id = min(new_id, (int8_t) 3);

            pressed = player.button;
        }
        set_score(new_id + 1, false);
        delay(1);
    }

    return (uint8_t) new_id;
}

#endif