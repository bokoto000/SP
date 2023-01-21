//Да се напише програма на C, която реализира командата tail файл
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define DEFAULT_LINE_COUNT 10

int main(int argc, char *argv[]) {
    int line_count = DEFAULT_LINE_COUNT;
    char *file;

    if (argc < 2) {
        printf("Usage: tail [line_count] <file>\n");
        return 1;
    } else if (argc == 2) {
        file = argv[1];
    } else if (argc == 3) {
        line_count = atoi(argv[1]);
        file = argv[2];
    }

    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        printf("Error: Unable to open file %s\n", file);
        return 1;
    }

    int lines = 0;
    char c;
    off_t offset, current_offset;
    current_offset = lseek(fd, 0, SEEK_END);
    offset = current_offset;
    while (offset--) {
        lseek(fd, offset, SEEK_SET);
        if (read(fd, &c, 1) == 1) {
            if (c == '\n') {
                lines++;
                if (lines == line_count) {
                    offset++;
                    break;
                }
            }
        }
    }
    lseek(fd, offset, SEEK_SET);
    char buffer[1024];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytes_read);
    }
    close(fd);
    return 0;
}