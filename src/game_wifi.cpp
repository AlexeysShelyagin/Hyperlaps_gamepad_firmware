#include "game_wifi.h"

namespace Recieve{
    uint8_t *recieved_data;
    bool updates_available = false;
}

void Game_wifi::on_data_sent(uint8_t *mac, uint8_t status){
    //Serial.println("sent");
}

void Game_wifi::on_data_recv(uint8_t *mac, uint8_t *incoming_data, uint8_t len){
    Recieve::recieved_data = incoming_data;
    Recieve::updates_available = true;
}

bool Game_wifi::init(uint8_t *motherboard_addr, uint8_t id){
    address = motherboard_addr;
    gamepad_id = id;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != 0)
        return 0;

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(address, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

    esp_now_register_send_cb(on_data_sent);
    esp_now_register_recv_cb(on_data_recv);

    return 1;
}

void Game_wifi::change_id(uint8_t id){
    gamepad_id = id;
    // TODO: write id to eeprom
}

void Game_wifi::send_player_state(Player &player){
    Player_data state;
    state.stick = player.stick;
    state.button = player.button;
    state.id = gamepad_id;
    esp_now_send(address, (uint8_t *) &state, sizeof(state));
}

void Game_wifi::update_recieved(){
    if(!Recieve::updates_available)
        return;
    Recieve::updates_available = false;

    Motherboard_response data;
    memcpy(&data, Recieve::recieved_data, sizeof(Motherboard_response));

    if(data.id == gamepad_id)
        score = data.score;
}