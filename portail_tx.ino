/* ___SODUINO TX_____
  Partie émétteur
  http://www.alnoa.fr
  v2.0 06/08/2014
  ___________________
  */

#include <Bounce2.h>// librairie qui simplifie la prise en charge des bouttons 
#include <VirtualWire.h>


const char *clef = "alex";//CLEF transmisdigitalWrite(pin, value);e à Soduino RX, doit y être identique, sinon cela ne sonne pas
int ledrouge = 8;
int ledblanche = 7;
int inter = 6;//BOUTON DE SELECTION DE MODE : NORMAL ou SILENCIEUX
int etatinfra = 0;
int etatsilence = 0;
int ledinterne = 13;
int BUTTON_PIN = 10;//BARRIERE INFRAROUGE
int BTSORTIE = 4; //bouton retardant pour libre passage interieur >> exterieur 
// création de l'objet à debounce cf:librairie bounce2
Bounce debouncer = Bounce(); 
Bounce debouncerST = Bounce();

//_____________________INITIALISATION____________________________
void setup() {
  //initialisation de la liaison série
  Serial.begin(9600);
  //paramétrage des  boutons en mode pull up
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(inter, INPUT_PULLUP);
  pinMode(BTSORTIE, INPUT_PULLUP);
  //paramétrage du  debouncer cf:librairie bounce2
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(350);
  debouncerST.attach(BTSORTIE);
  debouncerST.interval(75);
  //paramétrage des leds
  pinMode(ledinterne,OUTPUT);
  digitalWrite(ledinterne, HIGH );// mise à l'etat HAUT le temps de l'initialisation
  pinMode(ledrouge, OUTPUT);
  pinMode(ledblanche, OUTPUT);
  
  // Initialisation radio (pin12 data) et changement du pin ptt (pin 10 par défaut) car on l’utilise pour BUTTON_PIN
  vw_set_ptt_pin(5);// /!/ CHANGEMENT DU ptt_pin vers le 5
  vw_setup(1000);
  delay(2000);

  //envoie de la clef pour tester la liaison au démarrage
  vw_send((uint8_t *)clef, strlen(clef));
  vw_wait_tx();// attente que l'envoie soit bien fini
  
  //activation de l'alarme pour vérification du bon fonctionnement
  alarme();
  
  Serial.println("Test fait...");
  // bip et extinction de la del13 annonçant la fin du setup
  tone(9, 900, 250);
  digitalWrite(ledinterne,LOW);
}

//______________________BOUCLE__________________________________
void loop() {
 //Mise à jour du debouncer, 
 debouncer.update();
 debouncerST.update();
//Lecture et affichage du mode (normal et silence)
etatsilence = digitalRead(inter);
digitalWrite(ledrouge, !etatsilence);
 //Lecture du debouncer 
 int value = debouncer.read();

 int retardant = debouncerST.read();
 if (retardant == LOW)
 {
  retardateur();
  retardant = HIGH;
}

if (value == LOW)//si la barrière passe à l'état bas
{
    if (etatsilence == LOW)//si en mode silence
    {
      Serial.println("mode silence");
      digitalWrite(ledblanche, HIGH);
      tone(9,900);
      delay(500);
      noTone(9);
      digitalWrite(ledblanche, LOW);
      value = HIGH;
    }
    else//si en mode normal
    {
      Serial.println("mode normal");
      Serial.print("envoie ..");// On envoie plusieurs fois le message au cas où la portée du signal doit être grande et/ou affectée par les parasites.
      vw_send((uint8_t *)clef, strlen(clef)); // On envoie le message
      vw_wait_tx(); // On attend la fin de l'envoi
      Serial.print("1");
      vw_send((uint8_t *)clef, strlen(clef)); // On envoie le message
      vw_wait_tx();
      Serial.print(",2");
      vw_send((uint8_t *)clef, strlen(clef)); // On envoie le message
      vw_wait_tx();
      Serial.print(",3");
      vw_send((uint8_t *)clef, strlen(clef)); // On envoie le message
      vw_wait_tx();
      Serial.println(",4.");

      alarme(); //voir void alarme()

      Serial.println("réussi");
      value = HIGH;
    }
  }
}


void alarme() //sous-programme qui traite le son et les lumières de l'alarme
{
  Serial.println("alarme !");
  
  for(int comt=0; comt<7; comt++)
  {
    digitalWrite(ledrouge, HIGH);
    tone(9,5000);
    delay(250);
    digitalWrite(ledrouge, LOW);
    digitalWrite(ledblanche, HIGH);
    tone(9, 400);
    delay(250);
    digitalWrite(ledblanche, LOW);
    noTone(9);
  } 

  
  digitalWrite(ledblanche, HIGH);
  Serial.print("anti-flood...");
  delay(10000);
  Serial.println("ok");
  
  digitalWrite(ledblanche, LOW);
}

void retardateur()
{
  digitalWrite(ledblanche, HIGH);
  tone(9, 500);
  delay(750);
  tone(9,4500);
  delay(100);
  noTone(9);
  // boucle de retardateur de 3min
  for(int e=0;e<180;e++)
  {
    digitalWrite(ledblanche,LOW);
    delay(500);
    digitalWrite(ledblanche,HIGH);
    delay(500);
    }
  for(int z=0; z<4;z++)
  { 
    
    tone(9, 3500);
    delay(450);
    noTone(9);
    delay(250);
    
  }
  digitalWrite(ledblanche, LOW);
}
// Merci d'avoir téléchargé ce programme sur http://www.alnoa.fr
