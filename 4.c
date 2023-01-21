//Да се напише програма на C, която реализира командата wc файл
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: wc <file>\n");
        return 1;
    }

    char *file = argv[1];
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        printf("Error: Unable to open file %s\n", file);
        return 1;
    }

    int lines = 0, words = 0, characters = 0;
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            characters++;
            if (buffer[i] == '\n') {
                lines++;
            }
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') {
                words++;
            }
        }
    }

    printf("%d %d %d %s\n", lines, words, characters, file);

    close(fd);
    return 0;
}