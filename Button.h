/*
 * Button.h
 *
 *  Created on: 20.06.2015
 *      Author: Moritz Scholjegerdes
 *
 *      Checking if a button was pressed long or short with debounce for active low Buttons with use of the internal pullups.
 *
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
#include "../Timer/Timer.h"

class Button
{
public:
  Button (byte pin, unsigned int debounce_delay, unsigned int long_delay);
  void
  check_button_state (void);
  byte
  button_pressed_long (void);
  byte
  button_press_long (void);
  byte
  button_pressed_short (void);
  void
  button_reset (void);
private:
  byte _pin;
  byte b_press; 	// button is pressing
  byte long_press; 	// button is pressing long
  byte long_pressed; 	// button was pressed long
  byte short_pressed;	// button was pressed short
  byte long_first;
  Timer t1;
  Timer t2;
  unsigned int _debounce_delay;
  unsigned int _long_delay;
  byte button_state_0;
  byte button_state_1;
};

#endif /* BUTTON_H_ */
