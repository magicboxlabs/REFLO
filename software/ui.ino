// ============================================
//  UI update
    #define rt 26/54
// ============================================
void uiupdate() {
   if(SimbleeForMobile.updatable) { // iOS ui update      
      SimbleeForMobile.updateValue(select0, SELECT0); // mode slector update       
      SimbleeForMobile.updateValue(slider1, SLIDER1); // FAN slider position update
      SimbleeForMobile.updateValue(slider2, SLIDER2); // HEATER slider position update
      SimbleeForMobile.updateValue(slider3, SLIDER3); // TEMP slider position update
      SimbleeForMobile.updateValue(text1, TCtemp);    // temp display
      SimbleeForMobile.updateValue(text2, SQcnt);     // time elaps
      SimbleeForMobile.updateText (text3, pp);        // stage display
      SimbleeForMobile.updateValue(text4, SLIDER3);   // target temp 
      if(SELECT0 != 0) { // auto mode
        SimbleeForMobile.drawRect(30+SQcnt*rt, 380-TCtemp*1/2, 2, 2, rgba( 244,122, 66,  1)); // temp chart         
        switch (SQpnt) { // draw target square                
          case 0: SimbleeForMobile.updateRect(b0, 30+LAP*rt, 380-Ttable[0]*1/2, (SQcnt-LAP)*rt, abs((Ttable[0]-30))*1/2);         break;  
          case 1: SimbleeForMobile.updateRect(b1, 30+LAP*rt, 380-Ttable[1]*1/2, (SQcnt-LAP)*rt, abs((Ttable[1]-Ttable[0]))*1/2);  break;     
          case 2: SimbleeForMobile.updateRect(b2, 30+LAP*rt, 380-Ttable[2]*1/2, (SQcnt-LAP)*rt, abs((Ttable[2]-Ttable[1]))*1/2);  break;
          case 3: SimbleeForMobile.updateRect(b3, 30+LAP*rt, 380-Ttable[3]*1/2, (SQcnt-LAP)*rt, abs((Ttable[3]-Ttable[1]))*1/2);  break;
          case 4: SimbleeForMobile.updateRect(b4, 30+LAP*rt, 380-Ttable[4]*1/2, (SQcnt-LAP)*rt, abs((Ttable[4]-Ttable[3]))*1/2);  break;    
          case 5: SimbleeForMobile.updateRect(b5, 30+LAP*rt, 380-Ttable[5]*1/2+4, (SQcnt-LAP)*rt, abs((Ttable[5]-Ttable[4]))*1/2+4);  break;
          case 6: SimbleeForMobile.updateRect(b6, 30+LAP*rt, 380-Ttable[6]*1/2, (SQcnt-LAP)*rt, abs((Ttable[6]-Ttable[4]))*1/2);  break;  
          case 7: SimbleeForMobile.updateRect(b7, 30+LAP*rt, 380-Ttable[7]*1/2, (SQcnt-LAP)*rt, abs((Ttable[7]-Ttable[4]))*1/2);  break;            
          case 8: SimbleeForMobile.updateRect(b8, 30+LAP*rt, 380-Ttable[4]*1/2, (SQcnt-LAP)*rt, abs((Ttable[8]-Ttable[4]))*1/2);  break;
          case 9: SimbleeForMobile.updateRect(b9, 30+LAP*rt, 380-Ttable[4]*1/2, (SQcnt-LAP)*rt, abs((Ttable[8]-Ttable[4]))*1/2);  break;
        }       
      } else {    SimbleeForMobile.drawRect(30+SQcnt*rt, 380-SLIDER3*1/2, 2, 2, rgba( 209, 31, 31,  1)); 
                  SimbleeForMobile.drawRect(30+SQcnt*rt, 380-TCtemp*1/2, 2, 2, GRAY); // temp chart      
      } // manual mode target temp chart 
   }     
}
//void  updateRect(uint8_t  id, uint16_t  x,  uint16_t  y,  uint16_t  w,  uint16_t  h);
// ============================================
//  UI
// ============================================
void ui() {
  SimbleeForMobile.beginScreen(BLACK, PORTRAIT);  // ---

    char *titles0[] = { "Manual", "250", "230", "180" };
    select0 = SimbleeForMobile.drawSegment(30, 390, 260, titles0, countof(titles0), rgb(65, 139, 244));

    SimbleeForMobile.drawText(60,     135, "Current temp", GRAY, 18);        
    SimbleeForMobile.drawText(60+110, 135, "Target temp", GRAY, 18);
    SimbleeForMobile.drawText(60+110, 135+45,    "Door", GRAY, 18);
    SimbleeForMobile.drawText(60+110, 135+45+14, "o/c", GRAY, 18);
    
    text1 = SimbleeForMobile.drawText(60, 150, "000", WHITE, 26);    // temp   
    SimbleeForMobile.drawText(104, 150+3, "[deg]", GRAY, 20);     
    text2 = SimbleeForMobile.drawText(60, 150+25, "000", WHITE, 26); // elaps time
    SimbleeForMobile.drawText(104, 150+25+3, "[sec]", GRAY, 20); 

    doorbtn = SimbleeForMobile.drawSwitch(208, 210-25, WHITE);       // FAN direction set button
    
    text3 = SimbleeForMobile.drawText(60-30, 150+67, "[MANUAL MODE]", rgb(124, 239, 159), 20); // stage name
    text4 = SimbleeForMobile.drawText(60+110, 150, "000", rgba(209, 31,  31, 0.1), 26);        // temp
    SimbleeForMobile.drawText(104+110, 150+3, "[deg]", GRAY, 20); 

    SimbleeForMobile.drawText(143-1,   60-9, "FAN",    rgba(65, 139, 244, 0.1), 20);
    SimbleeForMobile.drawText(143-12, 100-9, "HEATER", rgba(244, 65, 157, 0.1), 20);
    text0 = SimbleeForMobile.drawText(143-12-26, 440-9-5, "TARGET TEMP", rgba(209, 31,  31, 0.1), 20);
    slider1 = SimbleeForMobile.drawSlider(30, 60,  260,  0 ,64);                                    // FAN 
    slider2 = SimbleeForMobile.drawSlider(30, 100, 260,  0 , 64, rgba(244, 65, 157, 0.1));          // HEATER
    slider3 = SimbleeForMobile.drawSlider(30, 440-5, 260, 30 ,270, rgba(209, 31,  31, 0.1));        // TARGET TEMP   
    SimbleeForMobile.setEvents(slider1, EVENT_DRAG | EVENT_RELEASE); 
    SimbleeForMobile.setEvents(slider2, EVENT_DRAG | EVENT_RELEASE);  
    SimbleeForMobile.setEvents(slider3, EVENT_DRAG | EVENT_RELEASE);   
    pane();

  SimbleeForMobile.endScreen(); // ---------------------     
  SimbleeForMobile.updateValue(select0, SELECT0);  
}
int pane() {
     SimbleeForMobile.drawRect(29, 375-130, 262, 130, rgb(41, 41, 41)); // gray chart pane
     SimbleeForMobile.drawRect(29, 375-100*1/2, 262, 1, BLACK);         // 100 degree line      
     SimbleeForMobile.drawRect(29, 375-200*1/2, 262, 1, BLACK);         // 200 degree line 
     b0 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(65, 244, 196, 0.1)); // target block 0
     b1 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(65, 244, 196, 0.1)); // target block 1
     b2 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(244, 65, 157, 0.1)); // target block 2
     b3 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(244, 65, 157, 0.1)); // target block 3
     b4 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(65, 244, 196, 0.1)); // target block 4
     b5 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(244, 65, 157, 0.1)); // target block 5
     b6 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(244, 65, 157, 0.1)); // target block 6
     b7 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(244, 65, 157, 0.1)); // target block 7
     b8 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(65, 244, 196, 0.1)); // target block 8  
     b9 = SimbleeForMobile.drawRect(0, 0, 1, 1, rgba(220,220, 220, 0.1)); // target block 9
}
// ============================================
//  UI event
// ============================================
void ui_event(event_t &event) {
  if(event.id == select0) { SELECT0 = event.value; Autoreq = 1; }
  if(event.id == slider1 && event.type == EVENT_DRAG) { SLIDER1 = event.value; }  
  if(event.id == slider2 && event.type == EVENT_DRAG) { SLIDER2 = event.value; }  
  if(event.id == slider3 && event.type == EVENT_DRAG) { SLIDER3 = event.value; 
    if(SLIDER3 == 30) { SimbleeForMobile.updateColor(text0, GRAY); 
                        SimbleeForMobile.updateColor(text4, GRAY); }
    else {  SimbleeForMobile.updateColor(text0, rgba(209, 31, 31, 0.1));
            SimbleeForMobile.updateColor(text4, rgba(209, 31, 31, 0.1)); }
    SimbleeForMobile.updateValue(text4, SLIDER3);   // target temp
  } 
  if(event.id == doorbtn) { DOOR = event.value; }
}
