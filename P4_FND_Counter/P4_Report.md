# <center>P4 FND Counter 및 argc argv 결과보고서</center>

<div style="text-align: right"> 3조 20162581 손승표 </div>
<br></br>

# 1.FND Counter
## 개요
- FND에 옵션에 따라 0~100으로 Up Counting 혹은 Down Counting 을 진행한다.

## 코드
```c

static unsigned short fnd_hexadecimal[16] = {
 0x3F, // 0
 0x06, // 1
 0x5B, // 2
 0x4f, // 3
 0x66, // 4
 0x6d, // 5
 0x7d, // 6
 0x07, // 7
 0x7f, // 8
 0x67, // 9
 0x77, // A
 0x7c, // B
 0x39, // C
 0x5e, // D
 0x79, // E
 0x71, // F
};

void fnd_up()
{
 int i;
 for (i = 0; i <= 100; i++)
 {
  fnd_decimal_number_only_number(i);
  usleep(100000);
 }
}

void fnd_down()
{
 int i;
 for (i = 100; i >= 0; i--)
 {
  fnd_decimal_number_only_number(i);
  usleep(100000);
 }
}

void fnd_decimal_clearing_front_zeros(unsigned long number)
{
 int i;
 //표시해야하는 숫자들을 fnd에 표시
 for (i = 0; i < MAX_FND; i++)
 {
  fnd_write(number % 10, i);
  number /= 10;

  if (number == 0)
   break;
 }
 //표시하지 말아야할 나머지 불들은 꺼줌
 for (i++; i < MAX_FND; i++)
 {
  *fnd[i] = 0x00;
 }
}

void fnd_write(int hexadecimal, int fnd_num)
{
 *fnd[fnd_num] = fnd_hexadecimal[hexadecimal];
}

```
- fnd_hexademical
    - 숫자마다 해당되는 fnd 어떤걸 켜야하는지를 정의
- fnd_up
    - 0부터 0.1초마다 숫자를 업카운팅해 100까지 표시해주는 함수
- fnd_down
    - 100부터 0.1초마다 숫자를 다운카운팅해 0까지 표시해주는 함수
- fnd_decimal_clearing_front_zeros
    - 숫자를 표시할 때 불필요한 앞의 0 숫자들을 지워서 표시하는 함수
        - 반복문을 통해 일의 자리부터 먼저 필요한 숫자들을 표시한 후
        - 반복문을 하나 더 이용해 나머지 불필요한 불들은 모두 끄도록 동작

# 2.argc와 argv 예제

## 개요
- argc와 argv에 어떤 값이 들어오는지를 살펴본다.

## 코드
```c
# include <stdio.h>

int main(int argc, char*argv[]) {

 int i;

 printf("argc: %d \n\n", argc);
 for (i = 0; i < argc; i++) {

 printf("argv[%d]: %s \n",i ,argv[i]);

 }
 return 0;
}
````
- argc에는 입력하는 매개변수들의 총 개수가 들어옴
    - ex) ./main hello 
        - 2
- argv에는 입력하는 매개변수들의 내용이 들어옴
    - ex) ./main hello
        - ./main
        - hello