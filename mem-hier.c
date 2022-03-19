#include "mem-hier.h"

// Note: this code doesn't *work*. It runs, but it measures the same ns time when
// there's no lines of code between the timer start & stop. Couldn't for the life
// of me figure out why, so I'm just moving on to part 2. Hopefully it's sorta the
// right idea, just with some dumb mistake. :(

char* generate_random_buffer(int size) {
  char* buffer = (char*)malloc(sizeof(char)* size);
  for (int i=0; i<size; i++) {
    buffer[i] = rand() % 256;
  }
  return buffer;
}

long double time_read(char* buffer, int size) {
  struct timespec start, stop;
  long double time = 0;
  int r1, r2, r3, r4;
  int trick = 0;
  // randomized indices
  r1 = rand() % size;
  r2 = rand() % size;
  r3 = rand() % size;
  r4 = rand() % size;
  // measure accesses
  clock_gettime(CLOCK_MONOTONIC, &start);
  trick += buffer[r1];
  trick += buffer[r2];
  trick += buffer[r3];
  trick += buffer[r4];
  clock_gettime(CLOCK_MONOTONIC, &stop);
  // time is ns / 4 accesses
  time += ((stop.tv_sec - start.tv_sec)*pow(10, 9) + (stop.tv_nsec - start.tv_nsec))/4;
  return time;
}

// in gnuplot use: plot "data.txt" using 1:2
void write_plot(int n, long double time) {
  FILE *f = fopen("times.txt", "a");
  fprintf(f, "%d %Lf\n", n, time);
  fclose(f);
}

int main() {
  // clear file for later writing to
  FILE *f = fopen("times.txt", "w");
  fclose;
  // main main
  for (int n = 100; n < pow(10, 6); n = n*2) {
    srand(time(NULL));
    char* buffer = generate_random_buffer(n);
    long double time = time_read(buffer, n);
    write_plot(n, time);
    printf("%d    %Lf\n", n, time);
    free(buffer);
  }
}
