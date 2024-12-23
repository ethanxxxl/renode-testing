# TITLE: Renode testing makefile
# AUTHOR: Ethan Smith
# DESCRIPTION: defines the process for compiling a simple test program for an
#              STM32 Arm Processor and emulating it using Renode.

SRC = main.c
OBJ = $(patsubst %.c,%.o,$(SRC))

LIBS = -lopencm3

CFLAGS = -Wall -Wextra -Werror
TARGET = firmware

################################################################################
# Programs/Tool Paths
PREFIX = arm-none-eabi
AS = $(PREFIX)-as
CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
OBJCOPY = $(PREFIX)-objcopy

RENODE = renode

################################################################################
# Rules for Lib Compilation

################################################################################
# Rules for Target Compilation
elf: $(TARGET).elf
bin: $(TARGET).bin

%.bin: %.elf
        $(OBJCOPY) -O binary $@ $<

%.elf: $(OBJ)
        $(LD) $(LDFLAGS) $(LIBS) -o $@ $(OBJ)

%.o: %.c
        $(CC) $(CFLAGS) -o $@ $<

################################################################################
# Rules for Emulation

