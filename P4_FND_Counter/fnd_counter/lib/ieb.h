 //-------| lib/ieb.h |-------// 
 #ifndef IEB_H 
 #define IEB_H 
 
 #include <unistd.h> // off_t 
 
 #define IEB_FND0 ((off_t) 0x11000000) //0001 0001 0000 0000 000 … 
 #define IEB_FND1 ((off_t) 0x11100000) //0001 0001 0001 0000 000 … 
#define IEB_FND2 ((off_t) 0x11200000) //0001 0001 0010 0000 000 … 
 #define IEB_FND3 ((off_t) 0x11300000) //0001 0001 0011 0000 000 … 
 #define IEB_FND4 ((off_t) 0x11400000) //0001 0001 0100 0000 000 … 
 #define IEB_FND5 ((off_t) 0x11500000) //0001 0001 0101 0000 000 … 
#define IEB_FND6 ((off_t) 0x11600000) //0001 0001 0110 0000 000 … 
 #define IEB_FND7 ((off_t) 0x11700000) //0001 0001 0111 0000 000 … 
 #define IEB_DOT1 ((off_t) 0x11800000) //0001 0001 1000 0000 000 … 
 #define IEB_DOT2 ((off_t) 0x11900000) //0001 0001 1001 0000 000 … 
 #define IEB_DOT3 ((off_t) 0x11A00000) //0001 0001 1010 0000 000 … 
 #define IEB_DOT4 ((off_t) 0x11B00000) //0001 0001 1011 0000 000 … 
 #define IEB_DOT5 ((off_t) 0x11C00000) //0001 0001 1100 0000 000 … 
 #define IEB_KEY_W ((off_t) 0x11D00000) //0001 0001 1101 0000 000 … 
 #define IEB_KEY_R ((off_t) 0x11E00000) //0001 0001 1110 0000 000 … 
 #define IEB_DAC ((off_t) 0x11F00000) //0001 0001 1111 0000 000 … 
 #define IEB_ADC ((off_t) 0x12000000) //0001 0010 0000 0000 000 … 
 #define IEB_ST_MOTOR ((off_t) 0x12100000) //0001 0010 0001 0000 000 … 
 #define IEB_DC_MOTOR ((off_t) 0x12200000) //0001 0010 0010 0000 000 … 
 #define IEB_CLCD_CMD ((off_t) 0x12300000) //0001 0010 0011 0000 000 … 
 #define IEB_CLCD_DATA ((off_t) 0x12380000) //0001 0010 0011 1000 000 … 
 #define IEB_LED ((off_t) 0x12400000) //0001 0010 0100 0000 000 … 
 
 #endif
