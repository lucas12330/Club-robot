/*
Author: Lucas Bezanilla Bou
*/

// Inclusion des librairies
#include <Adafruit_MotorShield.h>
#include <PS2X_lib.h>
#include <AFMotor.h>


// Mise en place de la connexion au shield moteur
AF_DCMotor motor(4);
// Pour une adresse I2C différente intégré l'adresse dans la fonction entre parenthèse


// creation de la classe PS2X
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

//Initialisation des variable de valeur joystick
int joyG_x;
int joyG_y;
int joyD_x;
int joyD_y;


void setup() {
  // Initialisation de i en undifined
  uint8_t i;

  // Mise en place des pins de contrôle
  error = ps2x.config_gamepad(21, 3, 20, 2, true, true);

switch(error) {
  case 0:
    Serial.println("Manette détectée avec succès. Type:150");
    Serial2.println(150);
    break;
  case 1:
    Serial.println("Aucun contrôleur trouvé, veuillez vérifier la connexion. Type:151");
    Serial2.println(151);
    break;
  case 2:
    Serial.println("Contrôleur trouvé, mais n'accepte pas les commandes. Type:152");
    Serial2.println(152);
    break;
  case 3:
    Serial.println("Contrôleur trouvé mais refuse d'entrer en pressure mode, peut-être qu'il ne le supporte pas. Type:153");
    Serial2.println(153);
    break;
}


  // Detection du type de controlleur
  type = ps2x.readType();
  switch(type){
    case 0:
      Serial.println("type de controleur inconnu. Type:255");
      Serial2.println(255);
      break;
    case 1:
      Serial.println("Dualshock controlleur trouvé. Type:255");
      Serial2.println(255);
      break;
    case 2:
      Serial.println("GuitarHero controlleur trouvé. type:255");
      Serial2.println(255);
      break;
  }


  Serial.begin(9600);    // Mise en place du moniteur série de méssage textuel
  Serial2.begin(9600);   // Mise en place du monieteur série de méssage d'erreur numérique, ou réussite
  Serial.println("Test, démarage réussi.");

  // Mise en place des variable numérique type: int des joysticks
  joyG_x = 0;
  joyG_y = 0;
  joyD_x = 0;
  joyD_y = 0;



  Serial.println("Initialisation et test termine. Type:1");
  Serial2.println(1);
}

void loop() {
  // Passer la boucle si aucun controlleur est trouvé
  if(error == 1) return;

  // Lecture de la manette
  // Lire la mannete plusieur fois dans le programme
  // pour plus de précision et de vitesse de changement ?
  ps2x.read_gamepad();

  // assignation du joystick gauche
  joyG_x = ps2x.Analog(PSS_LX);
  joyG_y = ps2x.Analog(PSS_LY);

  // Peux etre enlever si pose problème
  ps2x.read_gamepad();

  // Assignation du joystick droit
  joyD_x = ps2x.Analog(PSS_RX);
  joyD_y = ps2x.Analog(PSS_RY);

  // A enlever car programme de teste des joystick et de la lecture
  Serial.println("Valeur du joystick gauche x: " + String(joyD_x) + " y: " + String(joyD_y));
  motor1->setSpeed(255);
  motor1->fullOn();
}
