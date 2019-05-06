// by farsheed ashouri
// based on getline documentation. For more info, see `man getline`.
//
// Actually, I don't know what's this first line doing.
// UPDATE: I guess this is related to macro tests, but not sure. #TODO
//
// ---------------------- includes and definitions -------------------
#define _GNU_SOURCE
// Import IO library. getline comes with this include
#include <stdio.h>
// Include standard library
#include <stdlib.h>

// ---------------------- code logic ---------------------------------
//
// argc is the number of input arguments and argv is an array of those
int main(int argc, char *argv[]) {
  /*
   ssize_t getline(char **lineptr, size_t *n, FILE *stream);

   getline with store the address of the buffer to this var.
   we will set it to NULL to let getline to allocate a buffer for storing the
   line. This buffer should be freed later. (even if getline fails).
  */
  char *lineptr = NULL;

  // We have to set len to zero to allow getline to allocate buffer for storing
  // the line. This is the second param.
  size_t len = 0;

  // Now, we define a FILE for storing the data
  // This will store the input (I guess).
  FILE *stream;

  // we also need a signed int to store the return value of getline (which is
  // the number of read characters)
  ssize_t nread;

  // ---------------------- validations --------------------------------
  //
  // Now, lets check if input includes required args:
  if (argc != 2) {
    // we write out to stderr using fprintf
    // argv[0] will never be empty an is the name of executable
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // ---------------------- opening input ------------------------------
  //
  // now lets open the input file using fopen in "read mode"
  stream = fopen(argv[1], "r");

  // ---------------------- validation ---------------------------------
  // let's check if stream is null

  if (stream == NULL) {

    // return posix error
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // ---------------------- reading the file and printing --------------
  //
  // Now that everything looks ok, let's READ the file line by line
  // getline will result to -1 if line is empty, so
  while ((nread = getline(&lineptr, &len, stream)) != -1) {
    // print information about line
    // printf("Retrived line of length %zu:\n", nread);
    // still I don't know why the third parameter is 1.
    // TODO
    fwrite(lineptr, nread, 1, stdout);
  };

  free(lineptr);
  fclose(stream);
  exit(EXIT_SUCCESS);
  // -------------------------------------------------------------------
}
