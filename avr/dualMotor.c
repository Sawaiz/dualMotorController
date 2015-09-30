//Dual Motor Controller.
//Sawaiz Syed

#define IN1 PB0
#define IN2 PB1
#define IN3 PB2
#define IN4 PB3
#define INDDR DDRB
#define INR PORTB

#include <avr/io.h>
#include <util/delay.h>
#include "movement.h"

char commands[10] = "fffffflrff";

int main(void) {
//Set Movemnt Pins as outputs
INDDR |= (1<<IN1);
INDDR |= (1<<IN2);
INDDR |= (1<<IN3);
INDDR |= (1<<IN4);

 int i;
 for(i=0;i<(sizeof(commands)-1);i++){
  switch (commands[i]){
    case 'f':
      moveForward(500);
      break;
    case 'l':
      trunLeft(500);
      break;
    case 'r';
      turnRight(500);
      break;
  }
 }
}
