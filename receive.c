#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "register.h"

#define BUF_SIZE (1024*1024)

int main(){
  char buf[BUF_SIZE];
  int buf_index = 0;
  int diff_usec = 13157;
  int loop_second = 2;
  int loop_count = (loop_second * 1000 * 1000) / (diff_usec / 1000);
  struct timespec start, end;
  int infrared_pulse = 1;
  gpio_init();
  gpio_configure(27, GPIO_INPUT);
  while(loop_count--){
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

  buf[buf_index] = '\0';
  puts(buf);
  return 0;
}
