#ifndef GAME_WIFI_H
#define GAME_WIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "player.h"
#include "config.h"

class Game_wifi{
    uint8_t *address;
    static uint8_t recieved_score;

    struct Player_data{
        uint8_t id = 0;
        int8_t stick = 0;
        bool button = 0;
    };

    struct Motherboard_response{
        uint8_t id = 0;
        uint8_t score = 0;
    };

    static void on_data_sent(uint8_t *mac, uint8_t status);
    static void on_data_recv(uint8_t *mac, uint8_t *incoming_data, uint8_t len);

public:
    uint8_t score = 0;

    Game_wifi() = default;

    bool init(uint8_t *motherboard_addr);

    void send_player_state(Player &player);

    void update_recieved();
};

#endif