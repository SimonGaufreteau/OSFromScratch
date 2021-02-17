BUILD_DIR=../../build/os/kernel

CFLAGS+= -m32 -fno-pie -ffreestanding -Wall -Wextra -pedantic
LDFLAGS = -m elf_i386

OS_SRCS := $(wildcard *.c)
OS_ASM := $(wildcard *.asm)
OS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_SRCS))
OS_OBJS += $(patsubst %.asm, $(BUILD_DIR)/asm/%.o, $(OS_ASM))

all: $(OS_OBJS) 
	objcopy $(BUILD_DIR)/kernel.o -O elf32-i386 $(BUILD_DIR)/kernel.elf

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

$(BUILD_DIR)/%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR)/asm/%.o: %.asm
	nasm -f elf $< -o $@

.SILENT:clean

clean:
	-rm $(BUILD_DIR)/*
	