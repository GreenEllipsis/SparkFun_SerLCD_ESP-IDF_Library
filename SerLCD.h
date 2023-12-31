#pragma once

#include "stdint.h"
#include "driver/i2c.h"
#include "Print.h"

#ifndef QWIIC_SER_LCD_H
#define QWIIC_SER_LCD_H

#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD
#define MAX_ROWS 4
#define MAX_COLUMNS 20

//OpenLCD command characters
#define SPECIAL_COMMAND 254  //Magic number for sending a special command
#define SETTING_COMMAND 0x7C //124, |, the pipe character: The command to change settings: baud, lines, width, backlight, splash, etc

//OpenLCD commands
#define CLEAR_COMMAND 0x2D					//45, -, the dash character: command to clear and home the display
#define CONTRAST_COMMAND 0x18				//Command to change the contrast setting
#define ADDRESS_COMMAND 0x19				//Command to change the i2c address
#define SET_RGB_COMMAND 0x2B				//43, +, the plus character: command to set backlight RGB value
#define ENABLE_SYSTEM_MESSAGE_DISPLAY 0x2E  //46, ., command to enable system messages being displayed
#define DISABLE_SYSTEM_MESSAGE_DISPLAY 0x2F //47, /, command to disable system messages being displayed
#define ENABLE_SPLASH_DISPLAY 0x30			//48, 0, command to enable splash screen at power on
#define DISABLE_SPLASH_DISPLAY 0x31			//49, 1, command to disable splash screen at power on
#define SAVE_CURRENT_DISPLAY_AS_SPLASH 0x0A //10, Ctrl+j, command to save current text on display as splash

// special commands
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

class SerLCD : public Print
{

  public:
	SerLCD();
	~SerLCD();
	void begin(i2c_port_t &wirePort);
	void begin(i2c_port_t &wirePort, uint8_t i2c_addr);
	// void begin(Stream &serial);
	// void begin(SPIClass &spiPort, uint8_t csPin);
//Only available for Arduino 1.6 and greater
// #ifdef SPI_HAS_TRANSACTION
	//pass SPISettings by value to allow settings object creation in fucntion call like examples
	// void begin(SPIClass &spiPort, uint8_t csPin, SPISettings spiSettings);
// #endif
	void clear();
	void home();
	void setCursor(uint8_t col, uint8_t row);
	void createChar(uint8_t location, uint8_t charmap[]);
	void writeChar(uint8_t location);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buffer, size_t size, uint16_t ms);
	virtual size_t write(const uint8_t *buffer, size_t size);
	virtual size_t write(const char *str);
	void noDisplay();
	void display();
	void noCursor();
	void cursor();
	void noBlink();
	void blink();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void scrollDisplayLeft(uint8_t count);
	void scrollDisplayRight(uint8_t count);
	void moveCursorLeft();
	void moveCursorRight();
	void moveCursorLeft(uint8_t count);
	void moveCursorRight(uint8_t count);
	void setBacklight(unsigned long rgb);
	void setBacklight(uint8_t r, uint8_t g, uint8_t b);
	void setFastBacklight(unsigned long rgb);
	void setFastBacklight(uint8_t r, uint8_t g, uint8_t b);
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();
	void setContrast(uint8_t new_val);
	void setAddress(uint8_t new_addr);
	void command(uint8_t command);
	void specialCommand(uint8_t command);
	void specialCommand(uint8_t command, uint8_t count);

	void enableSystemMessages();
	void disableSystemMessages();
	void enableSplash();
	void disableSplash();
	void saveSplash();
	uint8_t getAddress();

  private:
	i2c_port_t _i2cPort = -1;   //The ESP32 I2C port number
	// TODO Stream *_serialPort = NULL; //The generic connection to user's chosen serial hardware
	// TODO SPIClass *_spiPort = NULL;  //The generic connection to user's chosen spi hardware

//TODO SPI support 
// #ifdef SPI_HAS_TRANSACTION
// 	SPISettings _spiSettings = SPISettings(100000, MSBFIRST, SPI_MODE0);
// 	bool _spiTransaction = false; //since we pass by value, we need a flag
// #endif
	// uint8_t _csPin = 10;
	uint8_t _i2cAddr = DISPLAY_ADDRESS1;
	uint8_t _displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	uint8_t _displayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	void init();
	// void beginTransmission();
	// void transmit(uint8_t data);
	// void endTransmission();
	long map(long, long, long, long, long);
};

#endif