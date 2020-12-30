#include <LiquidCrystal.h>
 //Tre LCD-skjermer og deres porter
  LiquidCrystal lcd1(12, 5, 7, 8, 9, 10);
  LiquidCrystal lcd2(12, 4, 7, 8, 9, 10);
  LiquidCrystal lcd3(12, 3, 7, 8, 9, 10);
 //Porter for resten av komponenter.
  const int nestePers = 11;
  const int seRes = 13;
  const int piezo = 2;
  const int slide1 = A1;
  const int slide2 = A2;
  const int slide3 = A3;
//Variabler som brukes til utregning av gjennomsnitt av avgitte svar
  int antallSpillere = 0;
  int resultat1 = 0;
  int resultat2 = 0;
  int resultat3 = 0;
    
void setup() 
{
//Setter opp tre LCD-skjermer
  lcd1.begin(16,2);
  lcd2.begin(16,2);
  lcd3.begin(16,2);

//Setter opp tre Slidepotensiometre
  pinMode(slide1, INPUT);
  pinMode(slide2, INPUT);
  pinMode(slide3, INPUT);

//Setter opp knappene Neste-Spiller og Se-Resultat
  pinMode(nestePers, INPUT);
  pinMode(seRes, INPUT);

//Setter opp Piezo element
  pinMode(piezo, OUTPUT);

//Spiller oppstartmelodi
  oppstartLyd(piezo);
}

void loop() {
  if (erTrykket(nestePers))
  {
		//Når en trykker på knappen nestePers trykkes:
    lesAv();    
    nesteLyd(piezo);
		//Viser det som er trykker på LCD-skjermene
    lcd1.print(analogRead(slide1)/100.3);
    lcd2.print(analogRead(slide2)/100.3);
    lcd3.print(analogRead(slide3)/100.3);
    delay(2000);
    lcd1.clear();
    lcd2.clear();
    lcd3.clear();
  }

  if(erTrykket(seRes))
  {
		//Når en trykker på knappen seRes
    ferdigLyd(piezo);
    resultater();
  }
}

boolean erTrykket(int pin){
//Sjekker om en knapp er trykket paa
  return digitalRead(pin);
}

void lesAv(){
//Leser av slidepotensiometerne og legger til totalresultatene, teller antall svar avgitt
  resultat1 = resultat1 + analogRead(slide1)/100.3;
  resultat2 = resultat2 + analogRead(slide2)/100.3;
  resultat3 = resultat3 + analogRead(slide3)/100.3;
  antallSpillere = antallSpillere + 1;
  delay(2000); }
      
int gjennomsnitt(int svar, int spillere){
 //Regner ut gjennomsnittet mellom svar og antall spillere
     int gj = 0;
     gj = svar/spillere;
     return gj;}

void resultater(){
//Henter gjennomsnittet av alle resultatene og skriver riktig gjennomsnitt til riktig LCD-skjerm
  int gj1 = gjennomsnitt(resultat1, antallSpillere);
  int gj2 = gjennomsnitt(resultat2, antallSpillere);
  int gj3 = gjennomsnitt(resultat3, antallSpillere);
  
  //LCD 1 – utskrift
  lcd1.print("Gj.snittet er: ");
  lcd1.setCursor(0, 1);
  lcd1.print(gj1);

  //LCD 2 – utskrift
  lcd2.print("Gj.snittet er: ");
  lcd2.setCursor(0, 1);
  lcd2.print(gj2);

  //LCD 3 – utskrift
  lcd3.print("Gj.snittet er: ");
  lcd3.setCursor(0, 1);
  lcd3.print(gj3);

  //Gjennomsnittet blir staaende i 10 sekunder, for det fjernes fra skjermene
  delay(10000);
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  
//Resultatene og antall svare nullstilles og kan brukes på nytt. 
  resultat1 = 0;
  resultat2 = 0;
  resultat3 = 0;
  antallSpillere = 0;
}

void oppstartLyd(int pin){
//Melodi som feedback for oppstart av Arduino
  tone(pin, 500, 200);
  delay(200);
  tone(pin, 1000, 200);
  delay(200);
  tone(pin, 1500, 200);
}

void nesteLyd(int pin){
//Melodi som gir feedback paa at Neste-Knappen er trykket paa  
  tone(pin, 750, 150);
  delay(150);
  tone(pin, 1500, 200);
}

void ferdigLyd(int pin){
//Melodi som gir feedback paa at Se-resultat-knappen er trykket paa.
  tone(pin, 500, 200);
  delay(300);
  tone(pin, 500, 200);
  delay(300);
  tone(pin, 500, 200);
  delay(300);
}
