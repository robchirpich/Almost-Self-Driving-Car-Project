#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "eecs388_lib.h"

void servo(int gpio, int pos)
{
  int pulse = 544 + 10.31 * pos;
  gpio_write(gpio, ON);
  delay_usec(pulse + 544);
  gpio_write(gpio, OFF);
  delay_usec(20000 - pulse);
}

int main()
{
  // initialize UART channels
  ser_setup(0); // uart0 (debug)
  ser_setup(1); // uart1 (raspberry pi)

  int distance = 0;
  int angle = 0;
  int gpio = PIN_19;
  gpio_mode(gpio, OUTPUT);
  gpio_mode(RED_LED, OUTPUT);
  gpio_mode(GREEN_LED, OUTPUT);
  gpio_mode(BLUE_LED, OUTPUT);

  printf("Setup completed.\n");
  printf("Begin the main loop.\n");

  while(1) {
    if('Y' == ser_read(0) && 'Y' == ser_read(0)) {
      int8_t dist_l = ser_read(0);
      int8_t dist_h = ser_read(0);
      distance = (dist_h << 8) | (dist_l);
    }

    if(distance > 50) {
      if(ser_isready(1)) {
        angle = ser_read(1);

        if(angle <= 30 && angle >= -30) { // TURN ALL LED'S ON
          gpio_write(RED_LED, ON);
          gpio_write(GREEN_LED, ON);
          gpio_write(BLUE_LED, ON);
        } else if(angle > 30) { // TURN GREEN LED ON
          gpio_write(GREEN_LED, ON);
          gpio_write(RED_LED, OFF);
          gpio_write(BLUE_LED, OFF);
          servo(gpio, angle);
        } else if(angle < -30) { // TURN BLUE LED ON
          gpio_write(BLUE_LED, ON);
          gpio_write(RED_LED, OFF);
          gpio_write(GREEN_LED, OFF);
          servo(gpio, angle);
        }
      }

      gpio_write(RED_LED, OFF);
      gpio_write(GREEN_LED, OFF);
      gpio_write(BLUE_LED, OFF);
    } else { // TURN RED LED ON (OBJECT DETECTED WITHIN 50 CM OF LIDAR SENSOR)
      gpio_write(RED_LED, ON);
      gpio_write(GREEN_LED, OFF);
      gpio_write(BLUE_LED, OFF);
    }
  }
}
