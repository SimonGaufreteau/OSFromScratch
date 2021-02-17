BUILD_DIR=../../build/os/drivers

CFLAGS+= -m32 -fno-pie -ffreestanding -Wall -Wextra -pedantic

DRIVERS_SRCS := $(wildcard *.c)
DRIVERS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(DRIVERS_SRCS))

all: $(DRIVERS_OBJS)

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

$(BUILD_DIR)/%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< 

.SILENT:clean

clean:
	-rm $(BUILD_DIR)/*