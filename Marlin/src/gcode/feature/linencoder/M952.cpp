#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../feature/linencoder/linencoder.h"

/**
 * M952 : calibrate linear offset encoder
 */

 void GcodeSuite::M952() {

    float headpos = head_encoder.getPos_noOff();
    head_encoder.set_calibration(headpos);
    SERIAL_ECHOLNPGM("head linear encoder calibrated");
 }