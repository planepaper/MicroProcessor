SIM_SRC		= $(SIM_PATH)/Ximulator.c
SIM_PATH	= $(PWD)

WRAP := -Wl,

sim :
	cd "$(xim_PATH)" && $(CC) \
		$(WRAP)usleep \
		$(WRAP)open \
		$(WRAP)close \
		$(WRAP)mmap \
		$(WRAP)munmap \
		$(xim_CFLAGS) \
		-I$(SIM_PATH) \
		-o xim_$(xim_OUTPUT) $(SIM_SRC) $(xim_SRCS)