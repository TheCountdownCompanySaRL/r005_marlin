#include "../../../inc/MarlinConfig.h"
#include "../../gcode.h"
#include "../../../module/motion.h"
#include "../../../module/temperature.h"
#include "../../../feature/loadcell/loadcell.h"
#include "../../../feature/linencoder/linencoder.h"
#include "../../../module/servo.h"
#include "../../../module/planner.h"

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
    char buf[] = "TS,P,X,Y,Z,E,zoff,zoffraw,Tnoz,FComp,FTens,PCut,Vfeed";
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
    char tbuf[10], pidxbuf[10], xbuf[10], ybuf[10], zbuf[10], ebuf[10],posbuf[10] ,tnbuf[10] ,cbuf[10], t2buf[10], servbuf[10], feedbuf[10],posrawbuf[10];
    dtostrf(tstamp,        7, 2, tbuf);
    dtostrf(pidx,          6, 2, pidxbuf);
    dtostrf(pos.x,         6, 2, xbuf);
    dtostrf(pos.y,         6, 2, ybuf);
    dtostrf(pos.z,         6, 2, zbuf);
    dtostrf(planner.get_axis_position_mm(E_AXIS),         6, 2, ebuf);
    dtostrf(head_encoder.getPos_mm(),6,3,posbuf);
    dtostrf(head_encoder.getraw(),6,0,posrawbuf);
    dtostrf(thermalManager.degHotend(0),6, 2, tnbuf);
    dtostrf(compSensor.getForce(), 6, 2, cbuf);
    dtostrf(tensSensor.getForce(), 6, 2, t2buf);
    dtostrf(servo[0].read(),       6, 2, servbuf);
    dtostrf(feedrate_mm_s,         6, 2, feedbuf);

    char buffer[255], rpibuf[255];
    snprintf(buffer, sizeof(buffer),"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",tbuf,pidxbuf, xbuf, ybuf, zbuf, ebuf, posbuf,posrawbuf, tnbuf, cbuf, t2buf,servbuf, feedbuf);
     #ifdef CUSTOM_SERIAL
     if (parser.seen('R')){ // ask for RPI image
        snprintf(rpibuf,sizeof(rpibuf),"$T%sP%sX%sY%sZ%sO%sC%sT%sE%sN%sA%sB%sC%s\n",tbuf,pidxbuf,xbuf,ybuf,zbuf,posbuf,cbuf,t2buf,ebuf,tnbuf,"0.0","0.0","0.0");
        Serial1.println(rpibuf);
     }
     #endif
    card.openFileAppend(logs_filename,true);        // opens or creates log.txt for append 
    card.append(buffer, strlen(buffer));      // appends text to log.txt
    card.closefile();   

  }else{
    if (!parser.seen('A')) { // write message to sd card
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