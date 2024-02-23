//Importeert de serial monitor library.
import processing.serial.*;
Serial get; 

String start;
String trim;
int input; 


int oldinput = 200; 

int newX;
int oldX = 0;

int newY;
int oldY = 800;

void setup(){
  size(1200, 1050);  
  background(#D3D3D3);
  
  
/*
   Vind de usb poort waar de arduino aan vast gekoppeld zit.
   Als dit gevonden is wordt er een nieuwe connectie aan gemaakt.
   Het programma buffert dan tot er een “/n” door de serial monitor wordt ontvangen  
*/
  String portName = Serial.list()[0];
  get = new Serial(this, portName, 9600);
  delay(5000);
  get.bufferUntil('\n');
  
  
  
}
void draw(){
 
  
  
/* 
    Probeert data uit de serial monitor te lezen als er data beschikbaar is en dit niet gelijk is aan null. 
    De white space wordt dan aan beide kanten van de input weggehaald door de trim() functie zodat de input kan worden omgezet tot een int.
*/    
 if ( get.available() > 1) {
      start = get.readStringUntil('\n');
        if(start != null){
        trim = trim(start);
        input=Integer.parseInt(trim);       
    }
  } 
  
/* 
    Als de nieuwe input niet gelijk is aan de oude input wordt er een lijn getekend van de vorige coordinaten naar de nieuwe.
    De conditie van de if statement word zo gedaan omdat de draw() functie van processing continu herhaald word en dus ook de waarde van de input. 
    Ik zocht dus iets wat hier mee kon werken zonder meerdere data input via de serial monitor door te sturen. Dit was de beste oplossing die ik kon bedenken.    
*/ 
  if(input != oldinput){
    
    
    newY = 1050 - input;
    newX = oldX + 12;
    
    stroke(#FF0000);
    strokeWeight(2);
    line(oldX,oldY,newX,newY);
    
    oldX += 12;
    oldY = newY;
    oldinput = input;
   
  } 
  
//Dit wordt gebruikt om de grafiek er iets beter eruit te laten zien 
  textSize(25);
  fill(0,0,0);
  text("0",0,1040);
  text("1023",0,27);

  
}
