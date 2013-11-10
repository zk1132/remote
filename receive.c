#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "register.h"

#define BUF_SIZE (1024*1024)
static char buf[BUF_SIZE];
static int buf_index = 0;

void last(int);

int main(){
  int diff_usec = 13157;
  struct timespec start, end;
  int infrared_pulse = 1;
  signal(SIGINT, last);
  gpio_init();
  gpio_configure(27, GPIO_INPUT);
  while(1){
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int pin = !gpio_read(27);
    buf[buf_index++] = (char)(pin + 48);
    while(1){
      clock_gettime(CLOCK_MONOTONIC_RAW, &end);
      long real_diff = (end.tv_sec - start.tv_sec) * 1000 * 1000 * 1000 + (end.tv_nsec - start.tv_nsec);
      if( real_diff > diff_usec) {
        break;
      }
    }
    infrared_pulse = 1 - infrared_pulse;
  }
  return 0;
}

void last(int n){
  int output = open("./config", O_WRONLY | O_CREAT);
  write(output, buf, buf_index);
  exit(0);
}

