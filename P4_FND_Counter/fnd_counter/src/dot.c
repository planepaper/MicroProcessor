//-------| src/dot.c |-------// 
 #include "dot.h"
 static unsigned short dot_decimal[10][MAX_DOT] = { 
 {0x7F, 0x41, 0x41, 0x41, 0x7F}, // 0 
 {0x00, 0x00, 0x7F, 0x00, 0x00}, // 1 
 {0x79 ,0x49 ,0x49 ,0x49 ,0x4F }, // 2 
 {0x7F ,0x49 ,0x49 ,0x49 ,0x49 }, // 3 
 {0x08 ,0x7F ,0x08 ,0x08 ,0x78 }, // 4 
 {0x4F ,0x49 ,0x49 ,0x49 ,0x79 }, // 5 
 {0x4F ,0x49 ,0x49,0x49 ,0x7F }, // 6 
 {0x7F ,0x40 ,0x40 ,0x40 ,0x40 }, // 7 
 {0x7F ,0x49 ,0x49 ,0x49 ,0x7F }, // 8 
 {0x7F ,0x48 ,0x48 ,0x48 ,0x78 } // 9 
 }; 
 static short * dot[MAX_DOT]; 
 /* mmap() 된 주소를 받아오는 함수 */ 
 void init_dot(short * address[]) { 
 int i; 
 for( i=0; i<MAX_DOT; i++ ) { 
 dot[i]= address[i]; 
 } 
 } 
 /* 화면을 지우는 함수 */ 
 void dot_clear() { 
 int i; 
 for(i=0; i<MAX_DOT; i++){ 
 *dot[i] = 0x00 ; 
 }
 usleep(0); // for Ximulator 
 } 
 /* 화면에 숫자를 그리는 함수 */ 
 void dot_write(int decimal) { 
 int i; 
 for(i=0; i<MAX_DOT; i++){ 
  *dot[i] = dot_decimal[decimal][i]; 
 } 
 usleep(0); // for Ximulator 
 } 
 /* 화면의 숫자가 50ms마다 올라가는 함수 */ 
void dot_up_shift(int decimal) {
 int shift, i; 
 for( shift=0; shift<=7; shift++ ) {
 for(i=0; i<MAX_DOT; i++){ 
 *dot[i] = dot_decimal[decimal][i]<<shift ;
 }
 usleep(50000); 
} 
} 
 /* 화면의 숫자가 50ms마다 내려가는 함수 */ 
 void dot_down_shift(int decimal) { 
int shift, i; 
 for( shift=0; shift<=7; shift++ ) {
 for(i=0; i<MAX_DOT; i++){ 
 *dot[i] = dot_decimal[decimal][i]>>shift ;
 }
 usleep(50000); 
} 
 }

 /* 화면을 0.3초 간격으로 흑백 반전하고 지우는 함수 */ 
 void dot_inverse(int decimal) { 
 int shift, i; 
 for( shift=0; shift<3; shift++ ) { 
 for(i=0; i<MAX_DOT; i++){ 
 *dot[i] = dot_decimal[decimal][i]; 
 } 
 usleep(300000); 
for(i=0; i<MAX_DOT; i++){ 
 *dot[i] = ~dot_decimal[decimal][i]; 
 } 
usleep(300000);
 dot_clear(); 
 }
}
