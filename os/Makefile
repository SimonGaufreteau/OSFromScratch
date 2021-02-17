BUILD_DIR=../build/os
KERNEL_BUILD_DIR=../build/os/kernel
DRIVERS_BUILD_DIR=../build/os/drivers
OS=$(BUILD_DIR)/os-image

LDFLAGS = -m elf_i386



all: kernel drivers $(OS)

.PHONY: kernel drivers $(OS)

drivers:
	make -C drivers

kernel:
	make -C kernel

debug: LDFLAGS += -g
debug: all

$(OS): OS_OBJS += $(wildcard $(KERNEL_BUILD_DIR)/*.o)
$(OS): OS_OBJS += $(wildcard $(DRIVERS_BUILD_DIR)/*.o)
$(OS):
	ld $(LDFLAGS) -o $@ -Ttext 0x1000 $(KERNEL_BUILD_DIR)/asm/kernel_entry.o $(OS_OBJS) --oformat binary



.SILENT:clean

clean:
	make -C kernel clean
	make -C drivers clean
	-rm $(OS)