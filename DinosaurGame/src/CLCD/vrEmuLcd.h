/*
 * Troy's HD44780U Lcd Display Emulator
 *
 * Copyright (c) 2020 Troy Schrapel
 *
 * This code is licensed under the MIT license
 *
 * https://github.com/visrealm/VrEmuLcd
 *
 */

#ifndef _VR_EMU_LCD_H_
#define _VR_EMU_LCD_H_

#define VR_LCD_EMU_DLLEXPORT extern

//#if VR_LCD_EMU_COMPILING_DLL
//  #define VR_LCD_EMU_DLLEXPORT __declspec(dllexport)
//#elif VR_LCD_EMU_STATIC
//  #ifdef __cplusplus
//    #define VR_LCD_EMU_DLLEXPORT extern "C"
//  #else
//    #define VR_LCD_EMU_DLLEXPORT extern
//  #endif
//#elif __EMSCRIPTEN__
//  #include <emscripten.h>
//  #define VR_LCD_EMU_DLLEXPORT EMSCRIPTEN_KEEPALIVE
//#else
//  #define VR_LCD_EMU_DLLEXPORT __declspec(dllimport)
//#endif

#include <stdint.h>

/* PRIVATE DATA STRUCTURE
 * ---------------------------------------- */
struct vrEmuLcd_s;
typedef struct vrEmuLcd_s VrEmuLcd;

/* PUBLIC CONSTANTS
 * ---------------------------------------- */
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_CLEAR;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_HOME;

VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_ENTRY_MODE;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_ENTRY_MODE_INCREMENT;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_ENTRY_MODE_DECREMENT;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_ENTRY_MODE_SHIFT;

VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_DISPLAY;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_DISPLAY_ON;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_DISPLAY_CURSOR;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_DISPLAY_CURSOR_BLINK;

VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SHIFT;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SHIFT_CURSOR;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SHIFT_DISPLAY;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SHIFT_LEFT;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SHIFT_RIGHT;

VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_FUNCTION;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_FUNCTION_LCD_1LINE;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_FUNCTION_LCD_2LINE;

VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SET_CGRAM_ADDR;
VR_LCD_EMU_DLLEXPORT const uint8_t LCD_CMD_SET_DRAM_ADDR;

typedef enum
{
  EmuLcdRomA00,  // Japanese
  EmuLcdRomA02   // European
} vrEmuLcdCharacterRom;

/* PUBLIC INTERFACE
 * ---------------------------------------- */

/* Function:  vrEmuLcdNew
 * --------------------
 * create a new LCD
 *
 * cols: number of display columns  (8 to 40)
 * rows: number of display rows (1, 2 or 4)
 * rom:  character rom to load
 */
VR_LCD_EMU_DLLEXPORT
VrEmuLcd* vrEmuLcdNew(int width, int height, vrEmuLcdCharacterRom rom);

/* Function:  vrEmuLcdDestroy
 * --------------------
 * destroy an LCD
 *
 * lcd: lcd object to destroy / clean up
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdDestroy(VrEmuLcd* lcd);

/* Function:  vrEmuLcdSendCommand
 * --------------------
 * send a command to the lcd (RS is low, R/W is low)
 *
 * data: the data (DB0 -> DB7) to send
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdSendCommand(VrEmuLcd* lcd, uint8_t data);


/* Function:  vrEmuLcdWriteByte
 * --------------------
 * write a byte to the lcd (RS is high, R/W is low)
 *
 * data: the data (DB0 -> DB7) to send
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdWriteByte(VrEmuLcd* lcd, uint8_t data);

/* Function:  vrEmuLcdWriteString
 * ----------------------------------------
 * write a string to the lcd
 * iterates over the characters and sends them individually
 *
 * str: the string to write.
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdWriteString(VrEmuLcd* lcd, const char *str);


/* Function:  vrEmuLcdGetDataOffset
 * ----------------------------------------
 * return the character offset in ddram for a given
 * row and column on the display.
 *
 * can be used to set the current cursor address
 */
VR_LCD_EMU_DLLEXPORT
int vrEmuLcdGetDataOffset(VrEmuLcd* lcd, int row, int col);

/* Function:  vrEmuLcdReadByte
 * --------------------
 * read a byte from the lcd (RS is high, R/W is high)
 *
 * returns: the data (DB0 -> DB7) at the current address
 */
VR_LCD_EMU_DLLEXPORT
uint8_t vrEmuLcdReadByte(VrEmuLcd* lcd);

/* Function:  vrEmuLcdReadByteNoInc
 * --------------------
 * read a byte from the lcd (RS is high, R/W is high)
 * don't update the address/scroll 
 *
 * returns: the data (DB0 -> DB7) at the current address
 */
VR_LCD_EMU_DLLEXPORT
uint8_t vrEmuLcdReadByteNoInc(VrEmuLcd* lcd);

/* Function:  vrEmuLcdReadAddress
 * --------------------
 * read the current address offset (RS is low, R/W is high)
 *
 * returns: the current address offset (either CGRAM or DDRAM)
 */
VR_LCD_EMU_DLLEXPORT
uint8_t vrEmuLcdReadAddress(VrEmuLcd* lcd);


/* Function:  vrEmuLcdCharBits
 * ----------------------------------------
 * return a character's pixel data
 *
 * pixel data consists of 5 uint8_ts where each is
 * a vertical row of bits for the character
 *
 * c: character index
 *    0 - 15   cgram
 *    16 - 255 rom
 */
VR_LCD_EMU_DLLEXPORT
const uint8_t *vrEmuLcdCharBits(VrEmuLcd* lcd, uint8_t c);

/* Function:  vrEmuLcdUpdatePixels
 * ----------------------------------------
 * updates the display's pixel data
 * changes are only reflected in the pixel data when this function is called
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdUpdatePixels(VrEmuLcd* lcd);

/* Function:  vrEmuLcdNumPixels
 * ----------------------------------------
 * get the size of the entire display in pixels (including unused border pixels)
 */
VR_LCD_EMU_DLLEXPORT
void vrEmuLcdNumPixels(VrEmuLcd *lcd, int* width, int* height);

/* Function:  vrEmuLcdNumPixelsX
 * ----------------------------------------
 * returns: number of horizontal pixels in the display
 */
VR_LCD_EMU_DLLEXPORT
int vrEmuLcdNumPixelsX(VrEmuLcd *lcd);

/* Function:  vrEmuLcdNumPixelsY
 * ----------------------------------------
 * returns: number of vertical pixels in the display
 */
VR_LCD_EMU_DLLEXPORT
int vrEmuLcdNumPixelsY(VrEmuLcd *lcd);

/* Function:  charvrEmuLcdPixelState
 * ----------------------------------------
 * returns: pixel state at the given location
 *
 * -1 = no pixel (character borders)
 *  0 = pixel off
 *  1 = pixel on
 *
 */
VR_LCD_EMU_DLLEXPORT
char vrEmuLcdPixelState(VrEmuLcd *lcd, int x, int y);

#endif // _VR_EMU_LCD_H_