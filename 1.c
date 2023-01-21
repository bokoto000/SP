//Да се напише програма на C, която реализира командата cp файл1 файл2
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    // Print error message and exit if incorrect number of arguments
    printf("Usage: cp file1 file2\n");
    return 1;
  }

  // Open file1 for reading
  int fd_src = open(argv[1], O_RDONLY);
  if (fd_src == -1) {
    // Print error message and exit if file1 cannot be opened
    printf("Error opening file %s\n", argv[1]);
    return 1;
  }

  // Open/create file2 for writing
  int fd_dst = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if (fd_dst == -1) {
    // Print error message and exit if file2 cannot be opened/created
    printf("Error opening/creating file %s\n", argv[2]);
    return 1;
  }

  // Copy contents of file1 to file2
  char buffer[4096];
  ssize_t n;
  while ((n = read(fd_src, buffer, sizeof(buffer))) > 0) {
    write(fd_dst, buffer, n);
  }

  // Close file descriptors
  close(fd_src);
  close(fd_dst);

  return 0;
}