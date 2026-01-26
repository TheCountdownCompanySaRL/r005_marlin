#include "linencoder.h"

#if ENABLED(LIN_ENC_FEATURE)

    void linenco_init() {
        SET_INPUT(LIN_ENC_PIN);
        head_encoder.set_calibration(0.0);
    }

    //class specific functions

    void LinearEncoder::sample(const raw_adc_t value) {
        this->acc += value;
        this->sample_count++;
    }

    void LinearEncoder::echo() {
        SERIAL_ECHOLNPGM("linear_encoder raw: ",this->raw);
    }

    void LinearEncoder::update_mm() {
        if (this->sample_count) {
            this->raw = this->acc / this->sample_count;
            this->acc = 0;
            this->sample_count = 0;
        }
   
        // Convert raw ADC value to position in um
        this->pos_mm = (this->raw*0.02961942 - 5.51229823);// calibration from testing
    }

    void LinearEncoder::set_calibration(float zero_force){
        this->zero_offset = zero_force;
    }

    int16_t LinearEncoder::getraw() { return this->raw; }
    float   LinearEncoder::getPos_noOff() { return (this->pos_mm); }
    float   LinearEncoder::getPos_mm() { return (this->pos_mm - this->zero_offset); }

    // declare encoder
    LinearEncoder head_encoder;

#endif // LIN_ENC_FEATURE
