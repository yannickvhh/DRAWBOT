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

    //Test Led CLignotement:
    //Rajout test Moteur droit:
void setup(){
    //config broches
    pinMode(LEDU1, OUTPUT);

    pinMode(EN_D, OUTPUT);//moteur droit
    pinMode(IN_1_D, OUTPUT);//def droit arriere
    pinMode(IN_2_D, OUTPUT);//def droit avant
    
    pinMode(EN_G, OUTPUT);// moteur gauche
    pinMode(IN_1_G, OUTPUT);//def gauche avant
    pinMode(IN_1_G, OUTPUT);//def gauche arriere

    //activation moteur :
    digitalWrite(EN_D, HIGH);//envoi courant au moteur droit
    digitalWrite(EN_G,HIGH);//envoi courant moteur gauche
}

void loop(){
    //test clignotement led 2fois:
    digitalWrite(LEDU1, HIGH);
    delay(500);
    digitalWrite(LEDU1, LOW);
    delay(500);
    digitalWrite(LEDU1, HIGH);
    delay(500);
    digitalWrite(LEDU1, LOW);
    delay(500);
}
