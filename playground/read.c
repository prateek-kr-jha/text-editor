#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    char* fileName = "hello.txt";
    int fd = open(fileName, O_RDWR);
    if(fd == -1) {
        printf("\nError opening file!!\n");
        return 1;
    } else {
        printf("\nFile %s opened sucessfully!\n", fileName);
    }
    char buffer[1024];

    int bytesRead = read(fd, buffer, sizeof(buffer));


    printf("%d bytes read!\n", bytesRead);
    printf("File contents: %s\n", buffer);


    return 0;
}