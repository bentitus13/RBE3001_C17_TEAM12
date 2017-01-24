/*
 * ADC.c
 *
 *  Created on: Jan 22, 2017
 *      Author: Rayyan Khan, Ben Titus, Ryan Wiesenberg
 */

#include <RBELib/RBELib.h>
#include <avr/io.h>


void initADC(int channel) {
	cli();
	DDRA &= ~(1 << channel);
	ADMUX = (1 << REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) ;
	sei();
}


void clearADC(int channel) {
	ADCSRA &= ~(1 << ADEN);
	ADC = 0;
}


unsigned short getADC(int channel) {
	ADMUX &= ~(0x1F);
	ADMUX |= (channel & 0x001F);	// set channel
	ADCSRA |= (1 << ADSC); // start conversion

	while(ADCSRA & (1 << ADSC)); // poll for cleared start-conversion bit

	return ADC;
}


void changeADC(int channel) {
	ADMUX &= ~31;
	ADMUX |= channel;
}
