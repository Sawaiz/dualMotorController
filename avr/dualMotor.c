//Dual Motor Controller.
//Sawaiz Syed

#include <avr/io.h>
#include <util/delay.h>

#define PWM_FREQ 48000
#define PWM_RESOLUTION (F_CPU / PWM_FREQ)
#define MIN_DUTY_CYCLE 0.40
#define MAX_DUTY_CYCLE 0.80
const uint8_t MIN_PWM_LEVEL = PWM_RESOLUTION * MIN_DUTY_CYCLE;
const uint8_t MAX_PWM_LEVEL = PWM_RESOLUTION * MAX_DUTY_CYCLE;

#define VREF 1.1
#define DESIRED_VOUT 20.0
#define DIVIDER_RATIO 30.0
#define DESIRED_ADC_IN_V (DESIRED_VOUT / DIVIDER_RATIO)

const uint8_t DESIRED_ADC_RESULT = 255 * DESIRED_ADC_IN_V / VREF;

#define ADC_ENABLE() (ADCSRA |= _BV(ADEN))
#define ADC_START_CONVERSION() (ADCSRA |= _BV(ADSC))

int main(void) {
 //set OC0 (PB0,PB1) as output
 DDRB |= (1<<PB0);
 DDRB |= (1<<PB1);
 //fast pwm
 TCCR0A |= (1<<WGM00);
 TCCR0A |= (1<<WGM01);
 TCCR0B |= (1<<WGM02);
 //clear OC0A on compare match, clear at top.
 TCCR0A |= (1<<COM0A0);
 TCCR0A &= ~(1<<COM0A1);
 TCCR0A &= ~(1<<COM0B0);
 TCCR0A |= (1<<COM0B1);
 //Set starting pwm freqency
 OCR0A = PWM_RESOLUTION;
 //Set intital duty cycle
 OCR0B = (uint8_t)(PWM_RESOLUTION*0.10);
 //no prescaling clock, start timer
 TCCR0B |= (1<<CS00);
 TCCR0B &= ~(1<<CS01);
 TCCR0B &= ~(1<<CS02);

 //Setup ADC
 //Vcc is refrence Voltage
 ADMUX &= ~(1<<REFS0);
 //Left shift ADC data, allowing 8b precision
 ADMUX |= (1<<ADLAR);
 //Analog chanel on PB4
 ADMUX |= (1<<MUX1);
 ADMUX &= ~(1<<MUX0);
 //Prescaler = 16
 ADCSRA &= ~(1<<ADPS0);
 ADCSRA &= ~(1<<ADPS1);
 ADCSRA |= (1<<ADPS2);
 //Enable ADC
 ADCSRA |= (1<<ADEN);

 while (1) {
  //Start a conversion
  ADCSRA |= (1<<ADSC);
  //Wait until convesrion finishes
  loop_until_bit_is_clear(ADCSRA, ADSC);
  //Get top byte from conversion
  uint8_t adc_result = ADCH;
  //Set Duty cycle
  OCR0B = adc_result;
  //_delay_ms(10);
 }
}
