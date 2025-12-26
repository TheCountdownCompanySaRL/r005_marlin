#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../feature/loadcell/loadcell.h"

/**
 * M951: calibrate loadcell
 */

 void GcodeSuite::M951() {

    float cload = compSensor.getForce_noOff();
    float tload = tensSensor.getForce_noOff();
    compSensor.set_calibration(cload);
    tensSensor.set_calibration(tload);
    SERIAL_ECHOLNPGM("loadcells calibrated");
 }