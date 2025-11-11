#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../feature/loadcell/loadcell.h"

/**
 * M950: request loadcell reading
 *   L<loadcell_index> - specify loadcell index (default 0)
 */

 void GcodeSuite::M950() {
    const uint8_t lc_index = parser.seenval('L') ? parser.value_byte() : 0;
    float cload = compSensor.getForce();
    float tload = tensSensor.getForce();
    SERIAL_ECHOLNPGM("compression= ",cload, "[N] tension= ", tload, " [N]");
    #warning "M950 loadcell readings implemented"
 }