#include <iostream>
#include <termios.h>


void enableRawMode() {

}
int main() {
    std::cout << "Hello, World!" << std::endl;
    // printf("Hello, World!\n");
    char c;
    while (std::cin.get(c) && c != 'q') {
        // std::cout << c;
    }
    return 0;
}
