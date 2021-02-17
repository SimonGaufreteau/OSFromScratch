BUILD_DIR=../build/bootloader

BOOTLOADER_SRCS := $(wildcard *.asm)
BOOTLOADER_OBJS := $(BUILD_DIR)/bootloader.o

all: $(BOOTLOADER_OBJS)

$(BUILD_DIR)/bootloader.o: bootloader.asm
	nasm $<  -g -o $@
#ld -m elf_i386 -T bootloader.lds $@ -o $@.elf
#objcopy -O binary  $(BUILD_DIR)/bootloader.o.elf $@

.SILENT:clean

clean:
	-rm $(BUILD_DIR)/*