BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.o
OS=$(BUILD_DIR)/os/os-image
DISK_IMG=disk.img

QEMUFLAGS = -D ./log.txt

# Defaul build target
all: bootloader os
all: bootdisk
.PHONY: bootloader os

dqemu: QEMUFLAGS += -s -S
dqemu: qemu

# Build the bootloader
bootloader:
	make -C boot

# Build the OS (i.e. kernel)
os:
	make -C os

# Build the disk image
bootdisk:
	#cat $(BOOTLOADER) $(OS) > $(DISK_IMG)
	dd if=/dev/zero of=$(DISK_IMG) bs=512 count=2880
	dd conv=notrunc if=$(BOOTLOADER) of=$(DISK_IMG) bs=512
	dd conv=notrunc if=$(OS) of=$(DISK_IMG) bs=512 seek=1


# Run qemu to simulate booting of our code
qemu: all
	qemu-system-i386 $(QEMUFLAGS) -drive format=raw,file=$(DISK_IMG)

debug_boot: 
	make -C boot debug
debug_os:	
	make -C os debug 
debug: debug_boot debug_os bootdisk

.SILENT:clean
clean:
	make -C boot clean
	make -C os clean

