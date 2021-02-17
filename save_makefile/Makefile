# Default make target .
all: os-image

# Run qemu
run: all
	qemu-system-i386 -drive format=raw,file=os-image

# boot_sect.bin
os-image: boot_sector.bin kernel.bin
	cat $^ > os-image


# Build the kernel binary
kernel.bin: kernel_entry.o kernel.o
	ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

# Build the kernel object file
kernel.o: kernel.c
	gcc -ffreestanding -c $< -o $@

# Build the kernel entry object file .
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf64 -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sector.asm
boot_sector.bin : boot_sector.asm
	nasm $< -f bin -I '.' -o $@

clean :
	rm *.bin *.o

# Disassemble our kernel - might be useful for debugging .
kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@
