BUILD_DIR=../../build/os/utils

CFLAGS+= -m32 -fno-pie -ffreestanding -Wall -Wextra -pedantic

UTILS_SRCS := $(wildcard *.c)
UTILS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(UTILS_SRCS))

all: $(UTILS_OBJS)

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

$(BUILD_DIR)/%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< 

.SILENT:clean

clean:
	-rm $(BUILD_DIR)/*