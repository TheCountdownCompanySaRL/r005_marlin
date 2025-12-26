#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../feature/loadcell/loadcell.h"

/**
 * M950: request loadcell readings
 */

 void GcodeSuite::M950() {
    float cload = compSensor.getForce();
    float tload = tensSensor.getForce();
    SERIAL_ECHOLNPGM("$C",cload, " T", tload);
 }