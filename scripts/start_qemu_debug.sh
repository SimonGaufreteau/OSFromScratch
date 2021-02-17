make clean
make debug
make dqemu
gdb -ex "target remote localhost:1234" -ex "symbol-file build/os/os-image.elf"
