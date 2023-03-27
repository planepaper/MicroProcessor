OUTPUT	= test
SRC	= test.c

a :
	echo This is a

b :
	@echo This is b

c : b
	@echo This is c # 아무말대잔치

d : c
	@echo This is $(OUTPUT) $@

$(OUTPUT) :
	$(CC) -o $@ $(SRC)

clean:
	@rm -f $(OUTPUT)


