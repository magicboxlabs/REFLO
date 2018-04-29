// ============================================
// status on LED
   boolean tgll;
// ============================================
void StatusLED() { leds[0] = CRGB(SLIDER2, 4, SLIDER1); FastLED.show(); digitalWrite(15, tgll); tgll = !tgll; }
// ============================================
// auto mode parameter setup
// ============================================
void manualmodeSetup() { SELECT0 = 0; // Auto mode reset
  SQpnt = 0; oldSQpnt = 99; pp = "[ MANUAL MODE ]"; 
  SLIDER1 = 0; SLIDER2 = 0; SLIDER3 = 32;
}
void automodeSetup() { //
  if(SimbleeForMobile.updatable) { // reset target temp BOX display
      SimbleeForMobile.updateRect(b1, 0, 0, 1, 1);  SimbleeForMobile.updateRect(b2, 0, 0, 1, 1);
      SimbleeForMobile.updateRect(b3, 0, 0, 1, 1);  SimbleeForMobile.updateRect(b4, 0, 0, 1, 1);
      SimbleeForMobile.updateRect(b5, 0, 0, 1, 1);  SimbleeForMobile.updateRect(b6, 0, 0, 1, 1);
      SimbleeForMobile.updateRect(b7, 0, 0, 1, 1);  SimbleeForMobile.updateRect(b8, 0, 0, 1, 1);  
      SimbleeForMobile.updateRect(b9, 0, 0, 1, 1);  
      SimbleeForMobile.updateColor(text0, rgba(209, 31, 31, 0.1)); //
      SimbleeForMobile.updateColor(text4, rgba(209, 31, 31, 0.1)); //     
  }
  if(SELECT0 != 0) {    
    if(SELECT0 == 1) { for (int n = 0; n < 9; n++) { Stable[n] = Stable1[n]; Ttable[n] = Ttable1[n]; Ftable[n] = Ftable1[n]; } }
    if(SELECT0 == 2) { for (int n = 0; n < 9; n++) { Stable[n] = Stable2[n]; Ttable[n] = Ttable2[n]; Ftable[n] = Ftable2[n]; } }
    if(SELECT0 == 3) { for (int n = 0; n < 9; n++) { Stable[n] = Stable3[n]; Ttable[n] = Ttable3[n]; Ftable[n] = Ftable3[n]; } } 
    SQcnt = 0; SQpnt = 0; LAP = 0;  
    SLIDER3 = Ttable[SQpnt]; SQSQ = Stable[SQpnt]; pp = "[AUTO MODE]"; 
  } else { pp = "[MANUAL MODE]"; SLIDER1 = 0; SLIDER2 = 0; SLIDER3 = 30; }    
}
// ============================================
//  Heater(23), Fan(9), Solenoid(29)
  long itime2, itime3; 
  int Fcnt = 0;             // 0 to 64 FAN on/off rate 
  int Hcnt = 0;             // 0 to 64 HEATER on/off rate 
  int timeup;               // 
// ============================================
void solenoid() {
  if(SimbleeForMobile.updatable) { SimbleeForMobile.updateValue(doorbtn, DOOR); }; 
  digitalWrite(29,  1); delay(1500); digitalWrite(29,  0); DOOR = 0;
  if(SimbleeForMobile.updatable) { SimbleeForMobile.updateValue(doorbtn, DOOR); };  
}
void FanHeat(int fanset, int heatset) { // fanset/heatset 0-63
  if(fanset > 20) { timeup = 300; } else { timeup = 9000; }
  if(micros() - itime2 > timeup) { itime2 = micros(); Fcnt++; if(Fcnt > 63) { Fcnt = 0; }         // FAN Control
      if(Fcnt <= fanset) { if(fanset) { digitalWrite( 9, 1); } } else { digitalWrite( 9, 0); }    // FAN ON /OFF  
  } 
  if(!fanset) { digitalWrite( 9, 0); }
  if(SFan)    { digitalWrite( 9, 1); }  // stirrer fan
  if(millis() - itime3 > 50)  { itime3 = millis(); Hcnt++; if(Hcnt > 63) { Hcnt = 0; }            // HEATER Control
    if(heatset > 10 && Hcnt <= heatset) { digitalWrite(23, 1); } else { digitalWrite(23, 0); }    // HEATER ON/OFF  
  } 
}
// ============================================
//  TEMP (Ktype -200 to 700degree)
//  D[31-18]:14bit temp (LSB = 0.25degree)
//  D[16]:fault D[17,3]:0 D[15-4]:internal temp (LSB = 0.0625degree)
//  D[2]:vcc  D[1]:gnd  D[0]:open
  SPISettings MAX31855(SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE1);
  byte MAX[4];              // MAX SPI read buffer  
// ============================================
int Rtemp() {
   int flt = 0; read31855();
   if(bitRead(MAX[2], 0) || bitRead(MAX[0], 0) || bitRead(MAX[0], 1) || bitRead(MAX[0], 2)) { flt = 1; }
   if(flt) {
      delay(300); read31855();
      if(bitRead(MAX[2], 0)) { Serial.print("Sensor FAULT"); }
      if(bitRead(MAX[0], 0)) { Serial.print("Short to VCC"); }
      if(bitRead(MAX[0], 1)) { Serial.print("Short to GND"); }
      if(bitRead(MAX[0], 2)) { Serial.print("Open circuit"); }          
   }
   return word(MAX[3], MAX[2])/16;           
}
void read31855() {
   SPI.beginTransaction(MAX31855); 
   digitalWrite(19, 0);     // CS "L"
   MAX[3] = SPI.transfer(0); MAX[2] = SPI.transfer(0); 
   MAX[1] = SPI.transfer(0); MAX[0] = SPI.transfer(0);  // read 32bit        
   digitalWrite(19, 1);     // CS "H"
   SPI.endTransaction();    //  
}

