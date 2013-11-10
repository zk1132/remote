#ifndef REGISTER_H_
#define REGISTER_H_

#define GPIO_INPUT  0x0
#define GPIO_OUTPUT 0x1

static volatile unsigned int *gpio;
void gpio_init();
void gpio_configure(int pin, int mode);
void gpio_set(int pin);
void gpio_clear(int pin);
int gpio_read(int pin);

#endif
