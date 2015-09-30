#define IN1 PB0
#define IN2 PB1
#define IN3 PB2
#define IN4 PB3
#define INDDR DDRB
#define INR PORTB

#include <avr/io.h>
#include <util/delay.h>

moveForward(int time){
  INR |= (1<<IN1);
  INR &= ~(1<<IN2);
  INR |= (1<<IN3);
  INR &= ~(1<<IN4);
  _delay_ms(time);
  stop();
}

turnRight(int time){
  INR &= ~(1<<IN1);
  INR &= ~(1<<IN2);
  INR |= (1<<IN3);
  INR &= ~(1<<IN4);
  _delay_ms(time);
  stop();
}

turnLeft(int time){
  INR |= (1<<IN1);
  INR &= ~(1<<IN2);
  INR &= ~(1<<IN3);
  INR &= ~(1<<IN4);
  _delay_ms(time);
  stop();
}

stop(){
  INR &= ~(1<<IN1);
  INR &= ~(1<<IN2);
  INR &= ~(1<<IN3);
  INR &= ~(1<<IN4);
}
