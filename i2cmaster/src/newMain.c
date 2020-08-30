#include <util/delay.h>
#include "USART.h"

// I2C-Master-Routinen von Peter Fleury verwenden
// siehe http://homepage.hispeed.ch/peterfleury/avr-software.html#libs
// Hier sind auch die Dateien: i2cmaster.h und twimaster.c zu finden, die benötigt werden
// Letztes Update des Codes 5. April 2010 durch HannoHupmann

#include <avr/io.h>
#include "i2cmaster.h"
#define SLAVE_ADRESSE 0x50

uint8_t byte1 = 42;
uint8_t byte2 = 43;
uint8_t byte3 = 44;
uint8_t byte11 = 0;
uint8_t byte21 = 0;
uint8_t byte31 = 0;
uint8_t byte41 = 0;

int main(void)
{
    i2c_init(); // init I2C interface
    initUSART();

    if (!(i2c_start(SLAVE_ADRESSE + I2C_WRITE))) //Slave bereit zum schreiben?
    {
        i2c_write(0x00);  // Buffer Startadresse setzen
        i2c_write(byte1); // Drei Bytes schreiben...
        i2c_write(byte2);
        i2c_write(byte3);
        i2c_stop(); // Zugriff beenden
    }
    else
    {
        /* Hier könnte eine Fehlermeldung ausgegeben werden... */
    }

    if (!(i2c_start(SLAVE_ADRESSE + I2C_WRITE))) //Slave bereit zum lesen?
    {
        i2c_write(0x00);                         //Buffer Startadresse zum Auslesen
        i2c_rep_start(SLAVE_ADRESSE + I2C_READ); //Lesen beginnen

        byte11 = i2c_readAck(); // Bytes lesen...
        transmitByte(byte11);
        byte21 = i2c_readAck();
        transmitByte(byte21);
        byte31 = i2c_readAck();
        transmitByte(byte31);
        byte41 = i2c_readNak(); // letztes Byte lesen, darum kein ACK
        transmitByte(byte41);
        i2c_stop(); // Zugriff beenden
    }
    else
    {
        /* Hier könnte eine Fehlermeldung ausgegeben werden... */
    }

    if ((byte1 != 42) || (byte2 != 43) || (byte3 != 44))
    {
        /* Die Bytes wurden nicht korrekt übertragen und wieder gelesen! */
    }
    for (;;)
        ;
}

// Code wurde von HannoHupmann auf einem Mega32 getestet