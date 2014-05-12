
/*
SODUINO
Programme Arduino pour sonnette à distance 
---PARTIE RECEPTION---
http://wp.me/p4dZn4-29

Réalisé avec à l'aide du tuto de Skywood http://skyduino.wordpress.com/2011/12/29/tutoriel-arduino-et-emetteurrecepteur-433mhz-virtualwire/
http://www.alnoa.fr
*/
#include <VirtualWire.h> // inclusion de la librairie VirtualWire
const int bouton= 8;
int boutonetat = 0;
const char* clef = "alex";//clef de réception , doit etre identique au message envoyé par le tx /!\  <<<-------
//par défault le pin 11 est le pin data radio et le  pin 7 le pin + du piezzo 
void setup()
{ 
  Serial.begin(9600);
  Serial.println("boot up");
  pinMode(bouton,INPUT);
    vw_setup(1000); // initialisation de la librairie VirtualWire à 2000 bauds (note: je n'utilise pas la broche PTT)
    vw_rx_start();  // Activation de la partie réception de la librairie VirtualWire
        tone (7,400,100);
        delay (150);
        tone (7,900,250);
        delay (250);
        tone (7,400,100);
        delay (150);
        Serial.println("test");
        test();
        
}
 
void loop() // Fonction loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Tableau qui va contenir le message reçu (de taille maximum VW_MAX_MESSAGE_LEN)
uint8_t buflen = VW_MAX_MESSAGE_LEN; // Taille maximum de notre tableau
  Serial.println("Attente de reception de la clef");
  vw_wait_rx();
  boutonetat = digitalRead(bouton);
    if (vw_wait_rx_max(200)) // Si un message est reçu dans les 200ms qui viennent
    {
        if (vw_get_message(buf, &buflen)) // On copie le message, qu'il soit corrompu ou non dans la variable buf
        {
        
        boutonetat = digitalRead(bouton);
        Serial.print("etat silencieux :");
        Serial.println(boutonetat);

        Serial.print("message recu: ");
        Serial.println((char*)buf);// conversion du message en "texte"
        delay(100);
       // comparaison du debut du message avec le mdp (si parasites en fin de message, cela n affecteras pas le declenchement)
        String charBuf = (char*)buf;
        
         if (charBuf.startsWith(clef,0) ){
         
       
       /* if (strlen(charBuf > strlen(clef))//ce morceau de code extrait le dernier caractère 
        {
        int len = strlen(charBuf);
        for (int i = 0; i < len - 1; i++) {
        Serial.print(charBuf[i]);
        }}
        
        
        if(strcmp(clef, (char*)buf) == 0) // comparaison du message(entier) reçu avec la clef du récepteur
            {*/
              Serial.println("clef valide");  
              sonnerie();
              if (boutonetat == LOW)
                  {
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                  }
            }  
        }
     }
}



void test()
{
  boutonetat = digitalRead(bouton);
digitalWrite(13,HIGH);
    piezzo();
        boutonetat = digitalRead(bouton);
        Serial.print("etat silencieux :");
        Serial.println(boutonetat);
         if (boutonetat == LOW){
        digitalWrite(5,HIGH);
        delay(750);
        digitalWrite(5,LOW);
        }
        delay(1000);
        digitalWrite(13,LOW);
}

void sonnerie() // sous-progrmme pour activer le relais de la sonnette 
{
  boutonetat = digitalRead(bouton);
  digitalWrite(13,HIGH);
    piezzo();
        
        if (boutonetat == HIGH)// relais sonette mode normal (HIGH normal, LOW silenceux ; pas de sonnette)
        {
        digitalWrite(4,HIGH);
        delay(250);
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
                    delay(75);
                    digitalWrite(5,HIGH);
                    delay(75);
                    digitalWrite(5,LOW);
        }   
        
        delay(1000);
        digitalWrite(13,LOW);
}

void piezzo() //sous-prog de la mélodie du piezzo
{
        tone (7,400);
        delay (250);
        tone (7,900,250);
        delay (250);
        tone (7,900,250);
        delay (250);
        tone (7,900,250);
        delay (250);
        tone (7,900,250);
        delay (250);
}
