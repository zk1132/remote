#include <time.h>
#include "register.h"

int main(){
  int diff_usec = 13157;
  struct timespec start, end;
  int infrared_pulse = 1;
  gpio_init();
  gpio_configure(17, GPIO_OUTPUT);
  gpio_configure(27, GPIO_INPUT);
  while(1){
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    int pin = !gpio_read(27);
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
