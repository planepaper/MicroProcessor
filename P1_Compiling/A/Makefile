OUTPUT	= make_test
SRCS	= ./src/main.c \
		./src/input.c \
		./src/test.c

CFLAGS	= -I./lib

$(OUTPUT) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)


clean:
	@rum -f $(OUTPUT)

