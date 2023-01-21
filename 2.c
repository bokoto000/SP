//Да се напише програма на C, която реализира командата head файл
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    // Print error message and exit if incorrect number of arguments
    printf("Usage: head file\n");
    return 1;
  }

  // Open file for reading
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    // Print error message and exit if file cannot be opened
    printf("Error opening file %s\n", argv[1]);
    return 1;
  }

  // Print first 10 lines of file
  char buffer[4096];
  ssize_t n;
  int lines = 0;
  while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
    for (int i = 0; i < n; i++) {
      if (buffer[i] == '\n') {
        lines++;
      }
      write(1, &buffer[i], 1); // write to stdout
      if (lines == 10) {
        goto end;
      }
    }
  }
  end:
  // Close file descriptor
  close(fd);

  return 0;
}