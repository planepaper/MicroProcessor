# Made by plaonn(plaonn@cau.ac.kr)
CC := /usr/local/arm-linux-4.1.1/bin/arm-linux-gcc

OUTPUT		= clcd
SRCS		= ./src/main.c \
				./src/clcd.c

CFLAGS		= -I./lib


$(OUTPUT) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

xim : $(SRCS)
	@cd /usr/xim && $(MAKE) -s xim_OUTPUT="$(OUTPUT)" \
	xim_PATH="$(PWD)" xim_SRCS="$(SRCS)" xim_CFLAGS="$(CFLAGS)"

clean:
	@rm -f $(OUTPUT)
	@rm -f xim_$(OUTPUT)