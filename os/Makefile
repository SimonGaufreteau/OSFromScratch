BUILD_DIR=../build/os
KERNEL_BUILD_DIR=../build/os/kernel
DRIVERS_BUILD_DIR=../build/os/drivers
UTILS_BUILD_DIR=../build/os/utils

OS=$(BUILD_DIR)/os-image

LDFLAGS = -m elf_i386


all: kernel drivers utils $(OS)

.PHONY: kernel drivers utils $(OS)

drivers:
	make -C drivers

kernel:
	make -C kernel

utils:
	make -C utils

debug_kernel: 
	make -C kernel debug
debug_drivers:	
	make -C drivers debug
debug_utils:	
	make -C utils debug

debug: LDFLAGS += -g
debug: debug_kernel debug_drivers debug_utils $(OS)

$(OS): OS_OBJS += $(wildcard $(KERNEL_BUILD_DIR)/*.o)
$(OS): OS_OBJS += $(wildcard $(DRIVERS_BUILD_DIR)/*.o)
$(OS): OS_OBJS += $(wildcard $(UTILS_BUILD_DIR)/*.o)

$(OS):
	#ld $(LDFLAGS) -o $@ -Ttext 0x1000 $(KERNEL_BUILD_DIR)/asm/kernel_entry.o $(OS_OBJS) --oformat binary
	ld $(LDFLAGS) -nmagic -Tos.lds $(KERNEL_BUILD_DIR)/asm/kernel_entry.o $(OS_OBJS) -o $(BUILD_DIR)/os-image.elf
	objcopy -O binary $(BUILD_DIR)/os-image.elf $(OS)



.SILENT:clean

clean:
	make -C kernel clean
	make -C drivers clean
	-rm $(OS)