#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "register.h"

#define BUF_SIZE (1024*1024)
char buf[BUF_SIZE];

int main(){
  int diff_usec = 13157;
  struct timespec start, end;
  int infrared_pulse = 1;
  int buf_index = 0;
  int record = open("./config", O_RDONLY);
  int size = read(record, buf, BUF_SIZE);

  gpio_init();
  gpio_configure(17, GPIO_OUTPUT);
  gpio_configure(27, GPIO_INPUT);
  while(size--){
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int pin = (int)buf[buf_index++] - 48;
    if(infrared_pulse && pin){
      gpio_set(17);
    } else {
      gpio_clear(17);
    }
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
