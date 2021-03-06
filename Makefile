# put your *.o targets here, make should handle the rest!

SRCS = 										\
		stm32f4xx_it.c						\
		system_stm32f4xx.c					\
		Buttons.cpp							\
		SPI.cpp								\
		UART.cpp							\
		TimingControl.cpp							\
		LEDS.cpp							\
		FPGA.cpp							\
		gameEngine/Coordinate.cpp			\
		gameEngine/GameObject.cpp			\
		gameEngine/Ball.cpp					\
		gameEngine/Engine.cpp				\
		gameEngine/SideWall.cpp				\
		gameEngine/FloorWall.cpp			\
		GameControllers/GameController.cpp	\
		GameControllers/Handball.cpp		\
		GameControllers/Tennis.cpp			\
		GameControllers/Demo.cpp			\
		GameControllers/Hockey.cpp			\
		GameControllers/PlayerController.cpp\
		MVC/Model.cpp						\
		MVC/View.cpp						\
		MVC/Controller.cpp					\
		MVC/Observer.cpp					\
		Menu/TextManager.cpp				\
		Menu/MenuBox.cpp					\
		Menu/MenuItem.cpp					\
		Menu/MenuViewer.cpp					\
		Menu/MenuItems/StartDemo.cpp		\
		Menu/MenuItems/StartTennis.cpp		\
		Menu/MenuItems/StartHandball.cpp	\
		Menu/MenuItems/StartHockey.cpp		\
		Menu/MenuItems/PlayerColorSelect.cpp\
		Menu/MenuItems/OpenMainMenu.cpp		\
		Menu/MenuItems/ResumeGame.cpp		\
		Menu/MenuItems/SetInfrared.cpp		\
		Game.cpp							\
		main.cpp
OUT=./out/
BIN=./bin/
DEP=./out/

OPT=0


#$(shell rm ./out/LEDS.o)
$(shell mkdir -p $(OUT) >/dev/null)
$(shell mkdir -p $(OUT)/MVC >/dev/null)
$(shell mkdir -p $(BIN) >/dev/null)
$(shell mkdir -p $(DEP) >/dev/null)

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=3D_pong

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O$(OPT) -Tstm32_flash.ld
CFLAGS += -Wall -Werror -Wtype-limits -Wuninitialized -Wunused-parameter -Wunused-but-set-parameter -Wempty-body   
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
LDFLAGS = -Os -Wl,-gc-sections --specs=nano.specs -specs=nosys.specs 

###################################################

vpath %.c src
vpath %.cpp src
vpath %.h inc
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

LIST = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OUT),$(LIST:.c=.o))
OBJS_FULL = $(OBJS) lib/startup_stm32f4xx.s # add startup file to build


###################################################

.PHONY: lib proj

all: lib proj
	@echo finished

lib: $(OUT)
	$(MAKE) -C lib

proj: $(BIN)$(PROJ_NAME).elf

$(BIN)$(PROJ_NAME).elf: $(OBJS_FULL)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@ -L$(OUT)lib -lstm32f4 -std=c++11
	$(OBJCOPY) -O ihex $(BIN)$(PROJ_NAME).elf $(BIN)$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BIN)$(PROJ_NAME).elf $(BIN)$(PROJ_NAME).bin
	
$(OUT)%.o : %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $< -std=c++11;
	rm -f $(DEP)/$*.d
	$(CXX) $(CFLAGS) -MM -MT $@ -MD $< -MF $(DEP)/$*.d -std=c++11;
	@echo "Compiled "$<"!\n"

$(OUT)%.o : %.c	
	$(CC) $(CFLAGS) -c -o $@ $<
	$(CC) $(CFLAGS) -MM -MT $@ -MD $< -MF $(DEP)/$*.d;
	@echo "Compiled "$<"!\n"

rebuild: clean lib proj
	
clean:
	rm -f $(OBJS)
	$(MAKE) -C lib clean
	rm -f $(BIN)$(PROJ_NAME).elf
	rm -f $(BIN)$(PROJ_NAME).hex
	rm -f $(BIN)$(PROJ_NAME).bin
	
include $(wildcard $(DEP)*/*.d)