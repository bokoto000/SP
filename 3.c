//Да се напише програма на C, която реализира командата cmp -s файл1 файл2
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    // Print error message and exit if incorrect number of arguments
    printf("Usage: cmp -s file1 file2\n");
    return 1;
  }

  // Open file1 for reading
  int fd1 = open(argv[1], O_RDONLY);
  if (fd1 == -1) {
    // Print error message and exit if file1 cannot be opened
    printf("Error opening file %s\n", argv[1]);
    return 1;
  }
  
  // Open file2 for reading
  int fd2 = open(argv[2], O_RDONLY);
  if (fd2 == -1) {
    // Print error message and exit if file2 cannot be opened
    printf("Error opening file %s\n", argv[2]);
    return 1;
  }

  // Compare contents of file1 and file2
  char buffer1[4096], buffer2[4096];
  ssize_t n1, n2;
  int result = 0;
  while ((n1 = read(fd1, buffer1, sizeof(buffer1))) > 0 && (n2 = read(fd2, buffer2, sizeof(buffer2))) > 0) {
    if (n1 != n2) {
      // Print error message and exit if file sizes are different
      printf("Files %s and %s are different\n", argv[1], argv[2]);
      result = 1;
      goto end;
    }
    for (int i = 0; i < n1; i++) {
      if (buffer1[i] != buffer2[i]) {
        // Print error message and exit if contents are different
        printf("Files %s and %s are different\n", argv[1], argv[2]);
        result = 1;
        goto end;
      }
    }
  }
  end:
  // Close file descriptors
  close(fd1);
  close(fd2);

  return result;
}