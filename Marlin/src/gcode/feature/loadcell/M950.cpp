#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../feature/loadcell/loadcell.h"
#include "../../../feature/linencoder/linencoder.h"

/**
 * M950: request loadcell readings
 */

 void GcodeSuite::M950() {
   char buffer[50],cloadbuf[10],tloadbuf[10],hposbuf[10];
   dtostrf(compSensor.getForce(),6,2,cloadbuf);
   dtostrf(tensSensor.getForce(),6,2,tloadbuf);
   dtostrf(head_encoder.getPos_mm(),6,3,hposbuf);

   sprintf(buffer,"$C%sT%sP%s",cloadbuf,tloadbuf,hposbuf);
   SERIAL_ECHOLN(buffer);
  //  #ifdef CUSTOM_SERIAL
  //     Serial1.println(buffer);
  //  #endif
 }