#include <Arduino.h>

// User led
#define LEDU1 25
#define LEDU2 26
// Enable moteurs droit et gauche
#define EN_D 23
#define EN_G 4
// Commande PWM moteur droit
#define IN_1_D 19 //arriere
#define IN_2_D 18 //avant
// Commande PWM moteur gauche
#define IN_1_G 17 //avant
#define IN_2_G 16 //arriere
// Encodeur gauche
#define ENC_G_CH_A 32
#define ENC_G_CH_B 33
// Encodeur droit
#define ENC_D_CH_A 27
#define ENC_D_CH_B 14
// I2C
#define SDA 21
#define SCL 22
// Adresse I2C
#define ADDR_IMU 0x6B
#define ADDR_MAG 0x1E


volatile int compteurG = 0; // Compteur pour la roue gauche / volatile parceque les variables peuvent changer 
volatile int compteurD = 0; // Compteur pour la roue droite

const float circonferenceRoue = 28.27; // en cm, pour roue de 9 cm de diamètre
const int topsParTour = 1060; // nombre de tops par tour de roue (1060 pour encodeur quadrature)
int objectfif = 20; // Objectif de distance à parcourir (en cm)
bool enMarche = false; // Etat du robot (en marche ou pas)

// Interruption pour roue gauche
void IRAM_ATTR interruptionGauche() {
  if(digitalRead(ENC_G_CH_B)==HIGH){//iram_attr appele par le microcontroleur quand il detecte un top sur une des broches
  compteurG--;// decrementer le compteur gauche
}else{
  compteurG++;// incrementer le compteur gauche
}
}

// Interruption pour roue droite
void IRAM_ATTR interruptionDroite() {
  if(digitalRead(ENC_D_CH_B)==HIGH){//iram_attr appele par le microcontroleur quand il detecte un top sur une des broches
  compteurD++;// incrementer le compteur droit
}else{
  compteurD--;// decrementer le compteur droit
}
}



void setup() {
  Serial.begin(115200);// Initialiser la communication série à 115200 bauds

  //config broches
  pinMode(LEDU1, OUTPUT);

  pinMode(EN_D, OUTPUT);//moteur droit
  pinMode(IN_1_D, OUTPUT);//def droit arriere
  pinMode(IN_2_D, OUTPUT);//def droit avant
    
  pinMode(EN_G, OUTPUT);// moteur gauche
  pinMode(IN_1_G, OUTPUT);//def gauche avant
  pinMode(IN_2_G, OUTPUT);//def gauche arriere

  //activation MOTEUR :
  digitalWrite(EN_D, HIGH);//envoi courant au moteur droit
  digitalWrite(EN_G,HIGH);//envoi courant moteur gauche

  // Broches en entrée
  pinMode(ENC_G_CH_A, INPUT);// Configurer la broche de l'encodeur gauche comme entrée
  pinMode(ENC_D_CH_A, INPUT);// Configurer la broche de l'encodeur droit comme entrée
  pinMode(ENC_G_CH_B, INPUT);// Configurer la broche de l'encodeur gauche comme entrée
  pinMode(ENC_D_CH_B, INPUT);// Configurer la broche de l'encodeur droit comme entrée

  // Attacher les interruptions aux deux encodeurs (front montant)
  attachInterrupt(digitalPinToInterrupt(ENC_G_CH_A), interruptionGauche, RISING);//des que tension monte a 1 sur lune des broche 32 ou 27 on appelle la fnc intterruptionGauche
  attachInterrupt(digitalPinToInterrupt(ENC_D_CH_A), interruptionDroite, RISING);

  //calcul nbr de tops pr 20cm
  objectfif=(20.0/ circonferenceRoue)* topsParTour; // 20 cm de distance à parcourir

  digitalWrite(IN_1_D , LOW); // Moteur droit arriere
  digitalWrite(IN_2_D , HIGH); // Moteur droit avant   
  digitalWrite(IN_1_G , HIGH); // Moteur gauche avant
  digitalWrite(IN_2_G , LOW); // Moteur gauche arriere  
  enMarche  = true; // Le robot est en marche
  compteurD=0; // Initialiser le compteur droit à 0
  compteurG=0; // Initialiser le compteur gauche à 0
}

void loop() {
  if(enMarche && abs(compteurG) >= objectfif && abs(compteurD) >= objectfif) { // Si le robot a parcouru la distance souhaitée
    digitalWrite(IN_1_D , LOW); // Moteur droit arriere
    digitalWrite(IN_2_D , LOW); // Moteur droit avant   
    digitalWrite(IN_1_G , LOW); // Moteur gauche avant
    digitalWrite(IN_2_G , LOW); // Moteur gauche arriere  
    Serial.println("Objectif atteint ! Distance de 20cm atteinte !"); // Afficher un message sur le moniteur série
    enMarche = false; // Le robot s'arrête
  }
  float distanceG = (compteurG* circonferenceRoue) /topsParTour; // Calculer la distance parcourue par la roue gauche
  float distanceD = (compteurD * circonferenceRoue) / topsParTour; // Calculer la distance parcourue par la roue droite
  Serial.print("distance Gauche : ");
  Serial.print(distanceG); // Afficher la distance gauche
  Serial.print("cm | distance Droite : ");
  Serial.println(distanceD);//afficher la distance droite
  Serial.println(" cm ");
  delay(500); // Affiche toutes les 0.5 sec
}
