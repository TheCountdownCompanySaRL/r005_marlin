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
   
        // Convert raw ADC value to force in Newtons
        // map raw from 0 to 1023 to -9.81 to +9.81 N
        this->pos_mm = (this->raw*19.62/1023.0)-9.81;
        //SERIAL_ECHOLNPGM("LC raw: ",raw," Force[N]: ",forceN);
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
