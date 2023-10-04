#ifndef CONFIG_H
#define CONFIG_H

//#define STATIC_MOTHERBOARD_ADDR

#define DEFAULT_GAMEPAD_ID 3


#ifdef STATIC_MOTHERBOARD_ADDR

static uint8_t motherboadrd_addr[] = {0xA8, 0x42, 0xE3, 0xC9, 0xE0, 0x04};

#else

#define DYNAMIC_MOTHERBOARD_ADDR
static uint8_t motherboadrd_addr[] = {0xA8, 0x42, 0xE3, 0xC9, 0xE0, 0x04};

#endif



#define LATCH_PIN 15
#define SCK_PIN 13
#define DATA_PIN 5

#define LED9 14
#define LED10 16

#define STICK_LEFT 0
#define STICK_RIGHT 4
#define BUTTON 12


#endif