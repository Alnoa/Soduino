//   soduino 03/05/2014
//http://www.alnoa.fr


#include <VirtualWire.h> // inclusion de la librairie VirtualWire
 int led1 = 8;
 int led2 = 7;
const int inter = 6;
const char *msg = "alex"; // clef 
const int infra = 10;
int etatinfra = 0;
int etatsilence = 0;

void setup() // Fonction setup()
{  
    pinMode(infra, INPUT);
    pinMode(inter, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Soduino bootup");
  
  vw_setup(1000);     // initialisation de la librairie VirtualWire à 1000 bauds 
  delay(2000);
  
  //test envoi demarrage
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
  
  if(etatsilence == LOW)
  {
    digitalWrite(led1,HIGH);
    Serial.println("mode silencieux");
    }
    else
    {
      digitalWrite(led1,LOW);
      Serial.println("mode normal");
      }
  
    if(etatinfra == HIGH)
    {
    digitalWrite(13,HIGH);
    tone(8, 900);
    delay(500);
    noTone(8);
  
      if(etatsilence == HIGH) // on déclenche l'alarme du tx si le bouton du silencieux est activé
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
          alarme();
        }
    Serial.println("réussi");
    delay(10000);
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
