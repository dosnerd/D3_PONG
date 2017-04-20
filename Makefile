# put your *.o targets here, make should handle the rest!

SRCS = 						\
		stm32f4xx_it.c		\
		system_stm32f4xx.c	\
		Vector.cpp			\
		SPI.cpp				\
		main.cpp
OUT=./out/
BIN=./bin/

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=main

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS = -Os -Wl,-gc-sections --specs=nano.specs -specs=nosys.specs 

###################################################

vpath %.c src
vpath %.cpp src
vpath %.h inc
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

#LIST1 = $(SRCS:.h=.o)
LIST = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OUT),$(LIST:.c=.o))
OBJS_FULL = $(OBJS) lib/startup_stm32f4xx.s # add startup file to build


###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C lib

proj: 	$(BIN)$(PROJ_NAME).elf

$(BIN)$(PROJ_NAME).elf: $(OBJS_FULL)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@ -L$(OUT)lib -lstm32f4 -std=c++11
	$(OBJCOPY) -O ihex $(BIN)$(PROJ_NAME).elf $(BIN)$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BIN)$(PROJ_NAME).elf $(BIN)$(PROJ_NAME).bin

$(OUT)%.o : %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^ -std=c++11
	@echo "Compiled "$<"!\n"
	
$(OUT)%.o : %.h
	$(CXX) $(CFLAGS) -c -o $@ $^ -std=c++11
	@echo "Compiled "$<"!\n"
	
$(OUT)%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	@echo "Compiled "$<"!\n"

rebuild: clean lib proj
	
clean:
	rm -f $(OBJS)
	$(MAKE) -C lib clean
	rm -f $(BIN)$(PROJ_NAME).elf
	rm -f $(BIN)$(PROJ_NAME).hex
	rm -f $(BIN)$(PROJ_NAME).bin