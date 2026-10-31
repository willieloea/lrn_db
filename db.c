#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- struct declarations --- //

typedef struct {
  char* buffer;         // character buffer for REPL input
  size_t buffer_length; // memory allocated on heap for buffer
  ssize_t input_length; // number of characters entered so far.
} InputBuffer;


// --- function declarations --- //

void print_prompt(void);
InputBuffer* new_input_buffer(void);
void read_input(InputBuffer*);
void close_input_buffer(InputBuffer*);


// --- function definitions --- //

InputBuffer* new_input_buffer(void) {
  // malloc returns void*, so it's good practice to do type casting
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));

  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt(void) {
  printf("ldb > ");
}

void read_input(InputBuffer* input_buffer) {
  // first arg is char** because getline() might need to reallocate memory in
  // the case of a long string.
  ssize_t bytes_read =
    getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read -1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer); // frees the char array
  free(input_buffer);         // frees the InputBuffer struct
}


// --- main function --- //

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognised command '%s'.\n", input_buffer->buffer);
    }
  }
}

