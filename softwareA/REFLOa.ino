// ============================================
//  Base design http://simblee.com
//  Language Reference http://arduino.cc/en/Reference/HomePage
//  24kRAM, 128kROM
// ============================================
//  FILE INCLUDE 
// ============================================
  #include "FastLED.h"                // RGB LED
  #include "SimbleeForMobile.h"       // BLE
  #include "SPI.h"                    // Thermocouple
  #include "para.h"                   //     

  CRGB leds[1];                       // RGB LED buffer   
// ============================================
//  SETUP
// ============================================
void setup() {
  Serial.begin(9600);                         // for Serial Monitor
  SPI.begin();                                // SPI CLK:17 SPI MISO:16 (MOSI:30)
  pinMode(15, OUTPUT);                        // LED    
  pinMode(19, OUTPUT);  digitalWrite(19, 1);  // SPI CS
  pinMode( 7,  INPUT);                        // TACT SW
  pinMode( 8, OUTPUT);  digitalWrite(8,  0); // FAN PH
  pinMode( 9, OUTPUT);  digitalWrite(9,  0);  // FAN ENABLE
  pinMode(23, OUTPUT);  digitalWrite(23, 0);  // HEATER  
  pinMode(28, OUTPUT);  digitalWrite(28, 1);  // DOOR PH
  pinMode(29, OUTPUT);  digitalWrite(29, 0);  // DOOR ENABLE

  FastLED.addLeds<NEOPIXEL, 11>(leds, 1);     // FastLED setup for RGB LEDs      
  StatusLED();
  
  SimbleeForMobile.deviceName = "REFLOa";         // device name
  SimbleeForMobile.advertisementData = "V0.8";    // firmware version
  SimbleeForMobile.begin();                       // Formobile start  

  manualmodeSetup(); 
}
// ============================================
//  LOOP (SLIDER1:FAN, SLIDER2:HEATER, SLIDER3:TARGET)
  long itime1, itimeS;              // Timer controll
  int  Tdiff;                       // Temp difference    
  int  SFan;                        // Count
  int  Scnt;                        // 
// ============================================ 
void loop() {
  if(DOOR) { solenoid(); } SimbleeForMobile.process();     
  FanHeat(SLIDER1, SLIDER2);                          // fan/heater control    
  if(millis() - itimeS > 300) { itimeS = millis();    // stirrer fan control flg
    int stir = Ftable[SQpnt]; 
    if(!stir) { SFan = 0; } else { Scnt++; if(Scnt > stir) { Scnt = 0; SFan = 1; } if(Scnt > 2) { SFan = 0; } }
  }
  if(millis() - itime1 > 1000) { itime1 = millis();   // 1sec timer control
    StatusLED(); 
    TCtemp = Rtemp(); Tdiff = SLIDER3 - TCtemp;
    if(Tdiff > 0) { SLIDER1 = 0; /*14;*/             SLIDER2 = min(abs(Tdiff)*12, 64); } // heating
    else          { SLIDER1 = min(abs(Tdiff)*5, 64); SLIDER2 = 0;                      } // cooling    
    if(TCtemp < 70) { SLIDER1 = 0; }                // idle
    if(Autoreq) { automodeSetup(); Autoreq = 0; delay(1000); }       // selector change event 
    if(SELECT0 != 0) { // AUTO sequence mode ----------------------------------------          
       SQSQ--; if(!SQSQ) {
          if(SQpnt == 3 || SQpnt == 5 || SQpnt == 7) { loadNext(); } // load next table
          else { 
            if(SQpnt < countof(seqname) - 1 && TCtemp < SLIDER3 - 2) { SQSQ++; } else { loadNext(); } // postpone until reach to target temp
          }
       } if(!SQpnt && TCtemp < 90 && SQcnt > 0) { SQcnt--; pp = "[AUTO MODE warmup]"; } // warmup mode @cold start  
    }  uiupdate(); SQupdate();
  }
}
void loadNext() { 
  if(SQpnt < countof(seqname)) { SQpnt++; SLIDER3=Ttable[SQpnt]; SQSQ=Stable[SQpnt]; pp=seqname[SQpnt]; LAP=SQcnt; } 
}
void SQupdate() { SQcnt++; if(SQcnt > 540) { SQcnt = 0; if(SELECT0 != 0) { manualmodeSetup(); }}} // sequence control

