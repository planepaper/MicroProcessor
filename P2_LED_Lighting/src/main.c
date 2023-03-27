//-------| src/main.c |-------//
#include "main.h"

#define INPUT_UP		1
#define INPUT_DOWN		2
#define INPUT_ALL		3
#define INPUT_EXIT		0

int main() {
	
	int fd;
	short * led;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	
	led = (short *)mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED, fd, (off_t)IEB_LED);
	if ( led == (short *)MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		close(fd);
		exit(EXIT_FAILURE);
	}
	init_led(led);
	
	while( menu() != INPUT_EXIT ) {	}
	
	munmap(led, sizeof(short));
	close(fd);
	
	return 0;
}

int menu(){
	int menu_input;

	printf("\n");
	printf("*********** Choice Menu **********\n");
	printf("* %d.     LED UP    Shift         *\n", INPUT_UP);
	printf("* %d.     LED DOWN  Shift         *\n", INPUT_DOWN);
	printf("* %d.     ALL                     *\n", INPUT_ALL);
	printf("* %d.           EXIT              *\n", INPUT_EXIT);
	printf("**********************************\n\n");

	printf("Select the menu number : ");
	scanf("%d", &menu_input);

	switch (menu_input) {
		case INPUT_UP :
			led_up_shift();
			break;
		case INPUT_DOWN :
			led_down_shift();
			break;
		case INPUT_ALL :
			led_blink_all();
			break;
		default :
			break;
	}
	
	return menu_input;
}
