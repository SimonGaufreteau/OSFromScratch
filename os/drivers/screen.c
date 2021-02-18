#include "screen.h"
#include "../kernel/low_level.h"
#include "../utils/memcopy.h"

int get_screen_offset(int row, int column) {
    return (row * MAX_COLS + column) * 2;
}

int get_cursor() {
    // The device uses its control register as an index
    // to select its internal registers , of which we are
    // interested in:
    // reg 14: which is the high byte of the cursor ’s offset
    // reg 15: which is the low byte of the cursor ’s offset
    // Once the internal register has been selected , we may read or
    // write a byte on the data register .
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    // Since the cursor offset reported by the VGA hardware is the
    // number of characters , we multiply by two to convert it to
    // a character cell offset .
    return offset * 2;
}

void set_cursor(int offset) {
    offset /= 2; // Convert from cell offset to char offset .
    // This is similar to get_cursor , only now we write
    // bytes to those internal device registers .
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, offset >> 8);
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, offset & 0xff);
}

int handle_scrolling(int offset) {
    int i;
    /*shift the content by 1 line up*/
    for (i = 1; i < MAX_ROWS; i++) {
        memcopy(get_screen_offset(i, 0) + VIDEO_ADDRESS,
                get_screen_offset(i - 1, 0) + VIDEO_ADDRESS, MAX_COLS * 2);
    }

    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    int current_offset = get_screen_offset(MAX_ROWS - 1, 0);
    /*create one blank line at the end*/
    for (i = 0; i < MAX_COLS; i++) {
        vidmem[current_offset] = ' ';
        vidmem[current_offset + 1] = WHITE_ON_BLACK;
        current_offset += 2;
    }
    offset = get_screen_offset(MAX_ROWS - 1, 0);
    return offset;
}
/* Print a char on the screen at col , row , or at cursor position */
void print_char(char character, int row, int col, char attribute_byte) {
    unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;
    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(row, col);
    } else {
        offset = get_cursor();
    }

    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(rows + 1, col);
    } else {
        // Set the char in the video memory
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
    }

    // Move to the next cell
    offset += 2;

    // Make scrolling adjustment , for when we reach the bottom
    // of the screen .
    if (offset >= get_screen_offset(MAX_ROWS, 0))
        offset = handle_scrolling(offset);
    // Update the cursor position on the screen device .
    set_cursor(offset);
}

void print_at(char *message, int row, int col) {
    // Update the cursor if col and row not negative .
    if (col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(row, col));
    }
    // Loop through each char of the message and print it.
    int i = 0;
    while (message[i] != 0) {
        print_char(message[i++], row, col, WHITE_ON_BLACK);
    }
}

void print(char *message) { print_at(message, -1, -1); }

void clear_screen() {
    int row = 0;
    int col = 0;
    /* Loop through video memory and write blank characters . */
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            print_char(' ', row, col, WHITE_ON_BLACK);
        }
    }
    // Move the cursor back to the top left .
    set_cursor(get_screen_offset(0, 0));
}
