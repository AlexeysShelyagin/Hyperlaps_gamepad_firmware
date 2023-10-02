#ifndef INDICATOR_HPP
#define INDICATOR_HPP

#include <Arduino.h>
#include "config.h"

void set_score(bool data[]){
    byte leds = 0;
    for(int i = 0; i < 8; i++){
        leds = leds | (data[i] << i);
    }

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, SCK_PIN, MSBFIRST, leds);
    digitalWrite(LATCH_PIN, HIGH);

    digitalWrite(LED9, data[8]);
    digitalWrite(LED10, data[9]);

    //Serial.print(data[8]);
    //Serial.print(" ");
    //Serial.println(data[9]);
}

void set_score(int n, bool fill = true){
    bool data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(fill)
        for(int i = 0; i < n; i++)
            data[i] = 1;
    data[n - 1] = 1;
    set_score(data);
}

#endif