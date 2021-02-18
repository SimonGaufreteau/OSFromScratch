#include "../drivers/screen.h"

void main() {
    clear_screen();
    print("Starting the kernel...\n");
    for (int i = 0; i < 10; i++) {
        print(
            "Lorem ipsum dolor sit amet, consectetur adipiscing elit.Donec eu "
            "condimentum felis, eu consequat erat. Vivamus non posuere orci. "
            "Ut "
            "blandit, lacus vel convallis maximus\n");
    }
    print("Handling the scrolling...\n");
    // print("Starting the kernel...\n");
}
