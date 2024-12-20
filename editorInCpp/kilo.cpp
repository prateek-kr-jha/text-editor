#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cerrno>
#include <cstring>

struct termios orig_termios;

void die(std::string s) {
    std::cerr << s << "\r\n" << std::strerror(errno) << std::endl;
    exit(1);
}

void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | IXON | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    // printf("Hello, World!\n");
    enableRawMode();
    while(1) {
        char c { '\0' };
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
            die("read");
        }
        if(iscntrl(c)) {
            std::cout << static_cast<int>(c) << "\r\n";
        } else {
            std::cout << static_cast<int>(c) << " (" << c << ")" << "\r\n";
        }
        if(c == 'q') break;
    }
    return 0;
}
