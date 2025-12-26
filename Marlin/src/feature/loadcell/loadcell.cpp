#include "loadcell.h"

#if ENABLED(LC_FEATURE)

    ForceSensor compSensor;   // the definitions
    ForceSensor tensSensor;
    char logs_filename[64] = "logger.txt";

    void lc_init() {
        SET_INPUT(COMP_LC_PIN);
        SET_INPUT(TENS_LC_PIN);
        compSensor.set_calibration(0.0);
        tensSensor.set_calibration(0.0);
    }

    void set_filename(char* filename){
        strncpy(logs_filename, filename, sizeof(logs_filename));
    }

    //class specific functions

    void ForceSensor::sample(const raw_adc_t value) {
        acc += value;
        sample_count++;
    }

    void ForceSensor::echo(uint16_t value,uint8_t loadcellnb) {
        SERIAL_ECHOLNPGM("lc",loadcellnb,": ",value);
    }

    void ForceSensor::update_newton() {
        if (sample_count) {
            raw = acc / sample_count;
            acc = 0;
            sample_count = 0;
        }
   
        // Convert raw ADC value to force in Newtons
        // map raw from 0 to 1023 to -9.81 to +9.81 N
        forceN = (raw*19.62/1023.0)-9.81;
        //SERIAL_ECHOLNPGM("LC raw: ",raw," Force[N]: ",forceN);
    }

    void ForceSensor::set_calibration(float zero_force){
        zero_offset = zero_force;
    }

    int16_t ForceSensor::getraw() { return raw; }
    float   ForceSensor::getForce_noOff() { return (forceN); }
    float   ForceSensor::getForce() { return (forceN - zero_offset); }

#endif // FORCE_SENSOR_FEATURE
