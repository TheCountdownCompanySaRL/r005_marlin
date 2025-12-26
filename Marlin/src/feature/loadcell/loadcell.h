#pragma once

#include "../../inc/MarlinConfig.h"

#if ENABLED(LC_FEATURE)

#define COMP_LC_PIN AUX2_03_PIN // Analog input A5
#define TENS_LC_PIN AUX1_07_PIN // Analog input A4
#define COMP_ADC_CH 5
#define TENS_ADC_CH 4



void lc_init();                // setup pin
void set_filename(char* filename); // set log filename

class ForceSensor {
public:
  void sample(const raw_adc_t value); // accumulate ADC samples
  void update_newton();                // convert from averaged raw to force in Newtons
  int16_t getraw();           // get averaged raw value
  float getForce();           // return force in Newtons
  float getForce_noOff();           // return force in Newtons without offset
  void set_calibration(float zero_force);
  void echo(uint16_t value,uint8_t loadcellnb); // print raw value (for testing)

private:
  int32_t acc;
  int16_t raw;
  float   forceN;
  float   zero_offset;
  uint8_t sample_count;
  bool    activated;
  float   target;
};

extern ForceSensor compSensor;
extern ForceSensor tensSensor;
extern char logs_filename[64];

#endif