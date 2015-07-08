/*
 * Button.cpp
 *
 *  Created on: 20.06.2015
 *      Author: Moritz Scholjegerdes
 */

#include "Button.h"
#include "Arduino.h"
#include "../Timer/Timer.h"

Button::Button (byte pin, unsigned int debounce_delay, unsigned int long_delay)
{
  pinMode (pin, INPUT);
  digitalWrite (pin, HIGH);
  _pin = pin;
  _debounce_delay = debounce_delay;
  _long_delay = long_delay;
  Timer t1;
  Timer t2;
  button_reset ();
}

void
Button::check_button_state ()
{
  byte button_state_new = digitalRead (_pin);
  if (button_state_0 != button_state_new)
    {
      button_state_0 = button_state_new;
      t2.restart ();
    }
  else if (button_state_0 == button_state_new
      && t2.t_since_start () >= _debounce_delay
      && button_state_1 != button_state_0)
    {
      button_state_1 = button_state_0;
      if (button_state_1 == LOW)
	{
	  t1.restart ();
	  b_press = 1;
	}
      else if (button_state_1 == HIGH)
	{
	  if (t1.t_since_start () >= _long_delay)
	    {
	      long_pressed = 1;
	    }
	  else
	    {
	      short_pressed = 1;
	    }
	  long_first = 0;
	}
    }
  if (t1.t_since_start () >= _long_delay && button_state_1 == LOW
      && long_first == 0)
    {
      long_press = 1;
      long_first = 1;
    }
}

byte
Button::button_pressed_long (void)
{
  byte pressed;
  pressed = long_pressed;
  long_pressed = 0;
  return pressed;
}

byte
Button::button_press_long (void)
{
  byte press;
  press = long_press;
  long_press = 0;
  return press;
}

byte
Button::button_pressed_short (void)
{
  byte pressed;
  pressed = short_pressed;
  short_pressed = 0;
  return pressed;
}

void
Button::button_reset (void)
{
  b_press = 0;
  long_press = 0;
  long_pressed = 0;
  short_pressed = 0;
  long_first = 0;
  button_state_0 = HIGH;
  button_state_1 = HIGH;
}
