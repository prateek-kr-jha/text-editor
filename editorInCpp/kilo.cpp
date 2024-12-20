#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <cctype>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | IXON | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);
    raw.c_cc[VMIN] = 0;
    raw.c_cflag |= (CS8);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    // printf("Hello, World!\n");
    char c;
    enableRawMode();
    std::cout << STDIN_FILENO << "\n";
    while (std::cin.get(c) && c != 'q') {
        // std::cout << c;
        if(iscntrl(c)) {
            std::cout << static_cast<int>(c) << "\r\n";
        } else {
            std::cout << static_cast<int>(c) << " (" << c << ")" << "\r\n";
        }
    }
    return 0;
}
