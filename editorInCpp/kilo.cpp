#include <iostream>
#include <termios.h>
#include <unistd.h>


void enableRawMode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    // printf("Hello, World!\n");
    char c;
    enableRawMode();
    std::cout << STDIN_FILENO << "\n";
    while (std::cin.get(c) && c != 'q') {
        std::cout << c;
    }
    return 0;
}
