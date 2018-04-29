// ============================================
//  IDE setup
// ============================================
//https://www.simblee.com/Simblee_Quickstart_Guide_v1.1.0.pdf
//Arduino/Contets/Java/portable/packages/Simblee/hardware/Simblee/1.0.0/variants/Simblee/variant.h     
//  #define SPI_INTERFACE        NRF_SPI0
//  #define PIN_SPI_SS           (18u) // not used
//  #define PIN_SPI_MOSI         (30u) // not used
//  #define PIN_SPI_MISO         (16u) //
//  #define PIN_SPI_SCK          (17u) //
// ============================================
//  IO assignment
// ============================================
// IO16:SO IO17:SCK IO19:CS(SPI)
// IO07:TACT SWITCH
// IO11:RGB LED
// IO15:LED
// IO08:FAN CONTROL PH
// IO09:FAN CONTROL EN
// IO23:HEATER CONTROL
// IO28:DOOR CONTROL PH
// IO29:DOOR CONTROL EN
// ============================================
//  Thermocoupe
// ============================================
  int  TCtemp;              // TEMP
  int  SQcnt = 0;           // SEQUENCE time(sec)
  int  SQpnt = 0;           // SEQ table pointer (0 to 7)
  int  oldSQpnt = 99;       // old SEQ table pointer
  int  SQSQ;                // for count down at each stage
  int  LAP;                 // current time stamp
  int  Autoreq = 0;         // Auto mode request
  char *pp;                 // disicription text explanation  
  
// ============================================
//  UI
// ============================================  
  byte select0;                            // mode selector
  byte text0, text1, text2, text3, text4;  // 
  byte slider1, slider2, slider3;          // fan/heat/target temp
  byte b0,b1,b2,b3,b4,b5,b6,b7,b8,b9;      // door openner
  byte doorbtn;

  int  SELECT0 = 0;         // MODE SELECTOR
  int  SLIDER1 = 0;         // FAN SLIDER 0-64
  int  SLIDER2 = 0;         // HEATER SLIDER 0-64
  int  SLIDER3 = 30;        // TEMP SLIDER 30-250
  int  DOOR = 0;            // DOOR

  int wid = 26/60;  // 26/45
// ============================================
//  TABLE  
// ============================================
  char* seqname[]={
    "[ PREPARATION ]",      // 0:preparation 
    "[ RAMP TO SOAK ]",     // 1:rampup
    "[ PREHEAT 1st HALF ]", // 2:pre heat
    "[ PREHEAT 2nd HALF ]", // 3:pre heat 
    "[ RAMP TO PEAK ]",     // 4:rampup2 
    "[ REFLOW 1/3 ]",       // 5:1st half
    "[ REFLOW 2/3 ]",       // 6:2nd half
    "[ REFLOW 3/3 ]",       // 7:2nd half
    "[ COOLING ]",          // 8:cooldown   
    "[ OPEN ]"              // 9:door open     
  };
  int Stable[12]; // Time(in Second) table
  int Ttable[12]; // TEMP table  
  int Ftable[12]; // FAN control table  
  //                                          5    6    7
  //                                     4          
  //                           2    3                       8    9
  //                      1
  //                 0    
  int Stable1[] = {  2,  30,  35,  35,  50,  30,  30,  10, 150, 200 };  // Time(in Second) table
  int Ttable1[] = { 90, 150, 180, 195, 230, 240, 250, 240,  85,  85 };  // TEMP table 217 melting point
  int Ftable1[] = {  0,   0,   0,  20,   0,  20,   0,  20,   0,   0 };  // FAN control table

  int Stable2[] = {  2,  30,  35,  35,  35,  20,  30,  10, 150, 200 };  // Time(in Second) table
  int Ttable2[] = { 90, 100, 135, 150, 220, 235, 235, 235,  85,  85 };  // TEMP table 183 melting point
  int Ftable2[] = {  0,   0,   0,  20,   0,  20,   0,  20,   0,   0 };  // FAN control table

  int Stable3[] = {  2,  30,  35,  35,  25,  30,  30,  10, 150, 200 };  // Time(in Second) table
  int Ttable3[] = { 90,  90, 115, 130, 175, 180, 185, 185,  85,  85 };  // TEMP table 137 melting point
  int Ftable3[] = {  0,   0,   0,  20,   0,  20,   0,  20,   0,   0 };  // FAN control table  


  
