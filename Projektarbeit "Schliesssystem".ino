/*===============================================================
  Descprition: RFID-Schliesssystem
  Author     : D.Niedhart
  Date       : 19.1.23
  Version    : V01.00.00
===============================================================*/
  
//RFID-Empfänger

  #include <SPI.h>
  #include <MFRC522.h>
  #include "arduino_config_PA.h"
  MFRC522 mfrc522(SS_PIN, RST_PIN);

//LCD-Display


  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>

  LiquidCrystal_I2C lcd(0x27, 16, 2); //16 Zeichen, 2 Zeilen und HEX-Adresse (Erkennung des Display)

void setup() {
  //RFID-Empfänger
      Serial.begin(9600);
      SPI.begin(); //SPI-Verbindung aufbauen
      mfrc522.PCD_Init(); //Initialisierung des RFID-Empfängers

  //LCD-Display
      lcd.init(); //Start des Display
      lcd.backlight(); //Hintergrundbeleuchtung wird eingeschaltet, lcd.nobacklight(); schaltet ab.

  //Relais
      pinMode(Relais, OUTPUT);
  }

void loop() {

  //RFID-Empfänger
    if ( ! mfrc522.PICC_IsNewCardPresent()) // (!) Called Logical NOT Operator. Use to reverses the logical state of its operand. If a condition is true, then Logical NOT operator will make false.
      {
    return;
      }
    if ( ! mfrc522.PICC_ReadCardSerial())
      {
    return;
      }
    long RFIDCard=0;

    for (byte i = 0; i < mfrc522.uid.size; i++) // (++) Increment operator, increases integer value by one
      {
      RFIDCard=((RFIDCard+mfrc522.uid.uidByte[i])*10);
      } 
    Serial.print("Diese Kartennummer lautet:");
    Serial.println(RFIDCard);
      
  //Relais + LCD-Display

    if (RFIDCard==435310 or RFIDCard==2552560) {
      lcd.setCursor(0, 0);
      lcd.print("ACCESS GRANTED");
      digitalWrite(Relais, HIGH);
      delay(3000);
      digitalWrite(Relais, LOW);
      lcd.clear();
      
        }
      else {
        lcd.setCursor(0, 0);
        lcd.print("ACCESS DENIED");
        delay(5000);
        lcd.clear();

        }
        
          

  }
    

