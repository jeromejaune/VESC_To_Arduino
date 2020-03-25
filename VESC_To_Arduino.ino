/*
  Name: VESC_To_Arduino.ino
  Autor : Roze Jerome

  Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
*/

#include <VescUart.h>
#include<SoftwareSerial.h>

#define RxD 2 /** pin 2 (connecter au TX du VESC) !!! A modifier si vous changez les pins de connection au VESC !!! */
#define TxD 3 /** pin 3 (connecter au RX du VESC) !!! A modifier si vous changez les pins de connection au VESC !!! */

/** Initiate VescUart class */
VescUart UART;

SoftwareSerial SerialVESC(RxD, TxD);

void setup() {

  /** Connexion à l'USB du PC */
  Serial.begin(9600);

  /** Connexion au VESC !!! A modifier en fonction de la vitesse de transfert de votre VESC */         
  SerialVESC.begin(115200);
  
  while (!SerialVESC) {;}

  /** Define which ports to use as UART */
  UART.setSerialPort(&SerialVESC);
}

void loop() {
  
  /** Call the function getVescValues() to acquire data from VESC */
  if ( UART.getVescValues() ) {

    Serial.print("Vitesse du moteur : ");
    Serial.println(UART.data.rpm);
    Serial.print("Voltage : ");
    Serial.println(UART.data.inpVoltage);
    Serial.print("Courant : ");
    Serial.println(UART.data.ampHours);
    Serial.print("tachometerAbs : ");
    Serial.println(UART.data.tachometerAbs);

  }
  else
  {
    Serial.println("Connexion échouée");
  }

  delay(50);
}
