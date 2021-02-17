BUILD_DIR=build
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.o
OS=$(BUILD_DIR)/os/os-image
DISK_IMG=disk.img

QEMUFLAGS = -D ./log.txt

# Defaul build target
all: bootdisk

.PHONY: bootdisk bootloader os

dqemu: QEMUFLAGS += -s -S
dqemu: qemu

# Build the bootloader
bootloader:
	make -C boot

# Build the OS (i.e. kernel)
os:
	make -C os

# Build the disk image
bootdisk: bootloader os
	cat $(BOOTLOADER) $(OS) > $(DISK_IMG)

# Run qemu to simulate booting of our code
qemu: all
	qemu-system-i386 $(QEMUFLAGS) -drive format=raw,file=$(DISK_IMG)

.SILENT:clean
clean:
	make -C boot clean
	make -C os clean

