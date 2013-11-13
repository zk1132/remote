#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "register.h"

#define PERI_BASE 0x20000000
#define GPIO_BASE (PERI_BASE + 0x200000)
#define BLOCK_SIZE 4096

static volatile unsigned int *gpio;
void gpio_init(){
  int fd;
  void *gpio_map;
  fd = open("/dev/mem", O_RDWR | O_SYNC);
  gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
  close(fd);
  gpio = (unsigned int *)gpio_map;
}

void gpio_configure(int pin, int mode){
  int index = pin / 10;
  unsigned int mask = ~(0x7 << ((pin%10) * 3));
  gpio[index] = (gpio[index] & mask) | ((mode & 0x7) << ((pin % 10) * 3));
}

void gpio_set(int pin){
  gpio[7] = 0x1 << pin;
}

void gpio_clear(int pin){
  gpio[10] = 0x1 << pin;
}

int gpio_read(int pin){
  return (gpio[13] & (0x1 << pin)) != 0;
}
