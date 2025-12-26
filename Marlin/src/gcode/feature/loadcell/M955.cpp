#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../module/motion.h"
#include "../../../module/temperature.h"
#include "../../../feature/loadcell/loadcell.h"
#include "../../../module/servo.h"

#if ENABLED(SDSUPPORT)

#include "../../../sd/cardreader.h"

void GcodeSuite::M955() {
  double pidx = 0.0;
  if (parser.seen('O')){
    if (!card.isMounted()) {
      SERIAL_ECHOLN("SD not mounted");
      return;
    }
    char buff[64];
    strncpy(buff, parser.string_arg, sizeof(buff));
    set_filename(buff+1);               // skip leading 'O'
    char buf[] = "TS,P,X,Y,Z,E,Tnoz,FComp,FTens,PCut,Vfeed";
    card.openFileAppend(logs_filename,true);        // opens or creates log.txt for append 
    card.append(buf, strlen(buf));      // appends text to log.txt
    card.closefile(); 
  }
  if (parser.seen('P')){
    pidx = parser.value_float(); //if trasnmitted by cs8c, update progress value idx
  }
  if (parser.seen('T')){ // used to store internal data at timestamp
    if (!card.isMounted()) {
      SERIAL_ECHOLN("SD not mounted");
      return;
    }
    xyze_pos_t pos = current_position.asLogical(); //actual last values transmitted by robot using G92
    double tstamp = parser.value_float();
    char tbuf[10], pidxbuf[10], xbuf[10], ybuf[10], zbuf[10], ebuf[10] ,tnbuf[10] ,cbuf[10], t2buf[10], servbuf[10], feedbuf[10];
    dtostrf(tstamp,        6, 2, tbuf);
    dtostrf(pidx,          6, 2, pidxbuf);
    dtostrf(pos.x,         6, 2, xbuf);
    dtostrf(pos.y,         6, 2, ybuf);
    dtostrf(pos.z,         6, 2, zbuf);
    dtostrf(pos.e,         6, 2, ebuf);
    dtostrf(thermalManager.degHotend(0),6, 2, tnbuf);
    dtostrf(compSensor.getForce(), 6, 2, cbuf);
    dtostrf(tensSensor.getForce(), 6, 2, t2buf);
    dtostrf(servo[0].read(),       6, 2, servbuf);
    dtostrf(feedrate_mm_s,         6, 2, feedbuf);

    char buffer[255];
    snprintf(buffer, sizeof(buffer),"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",tbuf, xbuf, ybuf, zbuf, ebuf, tnbuf, cbuf, t2buf,servbuf, feedbuf);
    card.openFileAppend(logs_filename,true);        // opens or creates log.txt for append 
    card.append(buffer, strlen(buffer));      // appends text to log.txt
    card.closefile();   

  }else{
    if (!parser.seen('A')) {
      SERIAL_ECHOLN("Error: Missing A parameter");
      return;
    }
    char *text = parser.string_arg;
    if (!card.isMounted()) {
      SERIAL_ECHOLN("SD not mounted");
      return;
    }
    card.openFileAppend(logs_filename,true);        // opens or creates log.txt for append
    if (text[0] == 'A') text++;               // skip leading A   
    card.append(text, strlen(text));      // appends text to log.txt
    card.closefile();                     // save & close
  }
}

#endif