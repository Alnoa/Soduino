/*   Soduino 

Made by Alnoa
http://www.alnoa.fr

*/

#include <VirtualWire.h> // initialisation de la librairie VirtualWire

int led1 = 8;
int led2 = 7;
int inter = 6;
int infra = 10;
int etatinfra = 0;
int etatsilence = 0;

const char *msg = "alex"; // clef, /!\ Mettre la même dans le programme Rx /!\

void setup() // Fonction setup()
{  
    pinMode(infra, INPUT);
    pinMode(inter, INPUT_PULLUP); //pullup,le pin de l'arduino est au +5V donc le bouton doit etre relié au pin et au GND
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
  
  Serial.begin(9600);// initialisation comunication du port série pour debug et voir le bon fonctionnement du code via le moniteur série de L'IDE ARDUINO
  Serial.println("Soduino bootup");
  
  vw_setup(1000);     // initialisation de la librairie VirtualWire à 1000 bauds 
  delay(2000);
  
  //test: envoi de la clef au démarrage
  vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message 
  vw_wait_tx(); // On attend la fin de l'envoi
 
  alarme();//on teste l'alarme
  Serial.println("test fait");
  delay(2000);
}
 
void loop() 
{
  etatinfra = digitalRead(infra);
  etatsilence = digitalRead(inter);  
  
  if(etatsilence == LOW)// gère la led pour afficher l'état "silencieux" sur le boitier.
  {
    digitalWrite(led1,HIGH);
    Serial.println("mode silencieux");
    }
    else
    {
      digitalWrite(led1,LOW);
      Serial.println("mode normal");
      }
  
    if(etatinfra == HIGH)// surveille l'état du capteur (ici un optocoupleur, similaire à un simple bouton avec pullup) et déclenche l'envoie de la clef 
    {
    digitalWrite(13,HIGH);
    tone(8, 900);
    delay(400);
    noTone(8);
  
      if(etatsilence == HIGH && etatinfra == HIGH) // on déclenche l'alarme boitier du tx si le bouton du silencieux est inactif
        {
          Serial.print("envoie ..");// on envoie plusieurs fois le message au cas ou la portée du signal doit étre grande et/ou affectée par les parasites.
            vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message 
            vw_wait_tx(); // On attend la fin de l'envoi
            vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message 
            vw_wait_tx();
            vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message 
            vw_wait_tx();
            vw_send((uint8_t *)msg, strlen(msg)); // On envoie le message 
            vw_wait_tx();
          
            alarme(); //voir void alarme()
        }
    Serial.println("réussi");
    delay(10000);//delais de 10sc pour ne pas flooder (innonder) les ondes , brouiller la fréquence, pour vos voisins !
    digitalWrite(13,LOW);
    }
}
void alarme() //sous programme qui traite le son et les lumiéres de l'alarme
{
  tone(9, 5000);
  digitalWrite(led1,HIGH);
  delay(250);
  noTone(9);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(500);
  noTone(9);  
  digitalWrite(led1,HIGH);
     digitalWrite(led2,LOW);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(250);
  noTone(9);
    digitalWrite(led2,LOW);
      digitalWrite(led1,HIGH);
  tone(9, 400);
  delay(250);
  noTone(9);
    digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
  tone(9, 5000);
  delay(500);
  noTone(9);
    Serial.println("alarme");
    digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
}
