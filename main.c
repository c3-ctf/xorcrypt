#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char** argv) {
  if (argc < 3) {
    fprintf(stderr, "%s ctext keyfiles...\n", argv[0]);
    return -1;
  }

  size_t n_files = argc - 1;

  FILE** files = malloc(n_files * sizeof(FILE*));
  for (int i = 1; i < argc; ++i) {
    if (!strcmp(argv[i], "-"))
      files[i - 1] = stdin;
    else
      files[i - 1] = fopen(argv[i], "r");
    if (!files[i - 1])
      fprintf(stderr, "Could not open file\n");
  }

  unsigned char outbuf[BUF_SIZE];
  unsigned char keybuf[BUF_SIZE];

  while (!feof(files[0])) {
    size_t n_read = fread(outbuf, 1, BUF_SIZE, files[0]);
    for (size_t file_no = 1; file_no < n_files; ++file_no) {
      size_t acc = 0;
      for (; acc != n_read; acc += fread(keybuf + acc, 1, n_read - acc, files[file_no]))
        rewind(files[file_no]);
      for (size_t i = 0; i < n_read; ++i)
        outbuf[i]^=keybuf[i];
    }
    fwrite(outbuf, n_read, 1, stdout);
  }
  fflush(stdout);

  return 0;
}
