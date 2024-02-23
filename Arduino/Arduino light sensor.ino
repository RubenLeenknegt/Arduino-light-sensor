int piezo = 11;
int input = A0;

int datapoints;
int sensor;
int value; 
int average;
int oldaverage; 

/*
   Unsigned long wordt hier gebruikt in plaats van int omdat
   de max waarde van int binnen 32 seconden bereikt zou worden door de millis() functie.
*/
const unsigned long interval = 15000;
unsigned long previousTime = 0;

void setup() {
  //De serial monitor wordt beruikt om de berekende waarde door te sturen naar processing.
  Serial.begin(9600);
  pinMode(input, OUTPUT);  
  pinMode(input, INPUT);
  pinMode(piezo, OUTPUT); 
}

void loop() {
  
  unsigned long currentTime = millis();
  
/*
  Deze functie wordt gebruikt om data in de serial monitor te zetten
  zodat processing kan stoppen met bufferen en de initialisatie kan afronden. 
  
  Dit heeft te maken met de “bufferUntil('\n');” functie in de setup van processing
*/
  if(currentTime < 1000){
      Serial.print(200);
      Serial.print('\n');  
  }

  
/*
  Deze if statement zorgt ervoor dat er iedere 15 seconde een meeting wordt gedaan van de licht sterkte.
  Als deze meting wordt gedaan maakt het piezo element een geluidje.
*/  
  if(currentTime - previousTime >= interval){
      
      previousTime = currentTime;
      
      datapoints++;
      sensor = analogRead(input);
      
      value += sensor;
      tone(piezo, 1000, 200);  
  }


  
/*
    Deze if statement deelt de totale opsomming van alle meetwaarden door
    de hoeveelheid gemaakte metingen om op een gemiddelde licht sterkte uit te komen.
    Na dat dit gebeurd is worden alle variabele terug naar 0 gezet.  
*/
  if(datapoints == 60){
     
     oldaverage =  average;
     average = 0;
     average = value / 60;
     value = 0;
     datapoints = 0;


 /* 
    Dit zorgt ervoor dat het nieuwe berekende gemiddelde nooit hetzelfde kan zijn als de vorige.
    Dit voorkomt dat processing de nieuwe meeting negeert en niet opneemt in de grafiek. 
 */
      if(average == oldaverage){
        average++;
        Serial.println(average); 
        tone(piezo, 2000, 300);    
      }
      else{
        Serial.println(average); 
        tone(piezo, 2000, 300);  
      }
  }


/* 
    Deze if statement houdt de totaal verstreken tijd bij en als er 24 uur (+ 5 minuten voor een error marge) 
    verstreken is start er een delay van 24 uur zodat er niet over de gemeten waarden heen geschreven kan worden. 
*/
  if(currentTime >= 86700000){

     tone(piezo, 4000, 600);
     delay(1000);
     tone(piezo, 5000, 600);
     delay(86400000);   
  }
  
}
