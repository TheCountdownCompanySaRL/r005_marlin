#pragma once

#include "../../inc/MarlinConfig.h"

#if ENABLED(LIN_ENC_FEATURE)

// analog input
#define LIN_ENC_PIN AUX2_09_PIN 
#define LIN_ENC_ADC_CH 12
// inverted analog input
// #define LIN_ENC_PIN AUX2_10_PIN 
// #define LIN_ENC_ADC_CH 11

void linenco_init();                // setup pin

class LinearEncoder {
public:
  void sample(const raw_adc_t value); // accumulate ADC samples
  void update_mm();                // convert from averaged raw to force in Newtons
  int16_t getraw();           // get averaged raw value
  float getPos_mm();           // return force in Newtons
  float getPos_noOff();           // return force in Newtons without offset
  void set_calibration(float zero_force);
  void echo();

private:
  int32_t acc;
  int16_t raw;
  float   pos_mm;
  float   zero_offset;
  uint8_t sample_count;
  bool    activated;
  float   target;
};


extern LinearEncoder head_encoder;

#endif