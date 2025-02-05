# TITLE: Renode testing makefile
# AUTHOR: Ethan Smith
# DESCRIPTION: defines the process for compiling a simple test program for an
#	       STM32 Arm Processor and emulating it using Renode.

SRC = main.c
OBJ = $(patsubst %.c,%.o,$(SRC))


DEFS		+= -DSTM32F4 -DSTM32F401xE
FP_FLAGS	 = -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS	 = -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

CFLAGS = -Wall -Wextra -Werror
CFLAGS += $(ARCH_FLAGS)
CFLAGS += -fno-common -ffunction-sections -fdata-sections -ggdb3

TARGET = firmware

################################################################################
# Programs/Tool Paths
PREFIX = arm-none-eabi
AS = $(PREFIX)-as
CC = $(PREFIX)-gcc
LD = $(PREFIX)-gcc
OBJCOPY = $(PREFIX)-objcopy
OBJDUMP = $(PREFIX)-objdump

################################################################################
# Rules for Lib Compilation
CFLAGS += -I ./libopencm3/include

LDFLAGS = -T linkerscript.ld -L ./libopencm3/lib
LDFLAGS += $(CFLAGS)
#LDFLAGS += -Wl,--cref -Wl,--gc-sections
LDFLAGS += --static -nostartfiles

LDLIBS += -lc -lgcc -lnosys
LDLIBS += -lopencm3_stm32f4

opencm3:
	make -C libopencm3

################################################################################
# Rules for Target Compilation
elf: $(TARGET).elf
bin: $(TARGET).bin
all: bin

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.elf: $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) $(DEFS) -c -o $@ $<

%.asm: %.o
	$(OBJDUMP) -d -S $<

asm: $(TARGET).elf
	$(OBJDUMP) -d -S $<

clean: 
	rm -f *.o $(TARGET).*
################################################################################
# Rules for Emulation
RENODE = renode
RENODE_SCRIPT = ./emulator.resc

# start emulator
# start uart viewer
emulate:
	gnome-terminal -- renode --console $(RENODE_SCRIPT)

view_serial:
	stty -F /tmp/uart 115200 -raw
	screen /dev/pts/5

.PHONY: opencm3 clean elf bin asm %.asm emulate
