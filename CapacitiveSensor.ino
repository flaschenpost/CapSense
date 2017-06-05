// Library  LED- Output
#include "LedControl.h" 
// Library  ADCTouch
#include <ADCTouch.h>

/*
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

// initialer Wert des linken Sensors
int links = 0;
// initialer Wert des rechten Sensors
int rechts = 0;
// nicht jede Aenderung soll am Display rumflackern
#define SCHWELLE 3

// Initialisierung des Displays aus einem Bibliotheksbeispiel
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,1);
  /* and clear the display */
  lc.clearDisplay(0);
}



void schreibeSensorwerte(int links, int rechts){
  lc.clearDisplay(0);
  byte pos = 0;
  while (links > 0 && pos < 4){
    lc.setDigit(0, 4+pos, links%10, false);
    links /= 10;  
    pos++;
  }
  pos = 0;
  while(rechts > 0 && pos < 4){
    lc.setDigit(0, pos, rechts%10, false);
    rechts /= 10; 
    pos++;
  }
}

void loop() {
  int neulinks = ADCTouch.read(A0, 70);
  int neurechts = ADCTouch.read(A1, 70);
  byte geaendert = 0;
  if(neulinks < links-SCHWELLE || neulinks > links+SCHWELLE){
    links = neulinks;
    geaendert = 1;
  }
  if(neurechts < rechts-SCHWELLE || neurechts> rechts+SCHWELLE){
    rechts = neurechts;
    geaendert = 1;
  }
  if(geaendert){
    schreibeSensorwerte(links, rechts); 
  }
}
