#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    std::cout << &raw << "\n";
    std::cout << &orig_termios << "\n";
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
