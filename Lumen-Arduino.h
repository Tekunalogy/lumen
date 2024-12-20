/* Blue Robotics Lumen LED Embedded Software
------------------------------------------------

Title: Lumen LED Light Embedded Microcontroller Software
Description: This file is used on the ATtiny45 microcontroller
on the Lumen LED Light and controls the dimming of the light. It can be
control by two methods, first is standard servo PWM pulse from
1100-1900 microseconds. The second is a logic high value on the signal
line. Additionally, a thermistor is used to sense temperature and automatically
dim the light if it is overheating.

-------------------------------
The MIT License (MIT)
Copyright (c) 2016 Blue Robotics Inc.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/

// HARDWARE PIN DEFINITIONS
#define SIGNAL_PIN      0
#define LED_PIN         1
#define TEMP_PIN        A1                  // A1

// TEMPERATURE LIMIT CHARACTERISTICS
#define ADC_MAX         1023                // max value of ADC
#define TEMP_SENSE_R    3300                // ohms
#define CELSIUS_0       273.15f             // 0 deg. Celsius in Kelvin
#define NTC_T0          298.15f             // NTC ref. temp., Kelvin
#define NTC_R0          10000.0f            // NTC resistance at ref. temp, ohms
#define NTC_B           3350.0f             // NTC equation B parameter, Kelvin
#define T_MAX           75.0f               // 80 C abs. max board temperature
#define T_CONTROL       60.0f               // dimming start temp
#define T_KP            ((N_STEPS-1)/(T_MAX-T_CONTROL))

// OUTPUT LIMIT
#define OUTPUT_MAX      230                 // 0-255 - 230 for about 15W max

// SIGNAL CHARACTERISTICS
#define PULSE_FREQ      50                  // Hz
#define PULSE_PERIOD    1000000L/PULSE_FREQ // microseconds
#define PULSE_CUTOFF    500                 // microseconds
#define PULSE_MIN       550                // microseconds
#define PULSE_MAX       1880                // microseconds
#define INPUT_TIMEOUT   0.050               // seconds


#define MANUAL_CUTOFF_DWE     1105          //microseconds
#define LUX_VARIATION_OFFSET_DWE     10          //microseconds

// INPUT FILTER CHARACTERISTICS
#define FILTER_DT       0.010f              // seconds
#define FILTER_TAU      0.100f              // seconds
#define N_STEPS         128                 // # of discrete outputs

// EXPONENTIAL MAP PARAMETERS
#define EXP_MAP_A0      0.00173f            // "exponential" map const term
#define EXP_MAP_A1      0.0345f             // "exponential" map linear term
#define EXP_MAP_A2      0.217f              // "exponential" map quadratic term
#define EXP_MAP_A3      0.451f              // "exponential" map cubic term
#define EXP_MAP_A4      0.297f              // "exponential" map quartic term

// TIMER CHARACTERISTICS
#define TIM0_PRESCALE   8                   // must match TCCR0B settings
#define TIM1_PRESCALE   4                   // must match TCCR1 settings

// HYSTERETIC ROUNDING
#define HYST_FACTOR     1.0                 // 0.5: normal rounding
