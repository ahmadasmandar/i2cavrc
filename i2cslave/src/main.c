/*
Testprogramm für den Slave 
Der Buffer wird mit Werten gefüllt. Dann wird er fortlaufend über die serielle Schnittstelle ausgegeben.
Nun kann man dort sehen, wenn der Master einen Wert ändert
*/
#include <util/twi.h>      //enthält z.B. die Bezeichnungen für die Statuscodes in TWSR
#include <avr/interrupt.h> //dient zur Behandlung der Interrupts
#include <stdint.h>        //definiert den Datentyp uint8_t
#include "i2cslave.h"
#include "USART.h"  //UART-Lib von P- Fleury
#include <stdlib.h> //nötig für Zahlumwandlung mit itoa
#include <util/delay.h>

// #define BAUD 9600          //Baudrate
#define SLAVE_ADRESSE 0x50 //Die Slave-Adresse

//Hilfsfunktion, um Zahlen über das UART auszugeben
// void printByte(const int val)
// {
//   char buffer[8];
//   printString(itoa(val, buffer, 10));
// }

int main(void)
{
  //TWI als Slave mit Adresse slaveadr starten
  init_twi_slave(SLAVE_ADRESSE);

  //i2cdatamit Werten füllen, die der Master auslesen und ändern kann
  // for (uint8_t i = 0; i < i2c_buffer_size; i++)
  // {
  i2cdata[0] = 'a';
  i2cdata[1] = 'b';
  i2cdata[2] = 'c';
  i2cdata[3] = 'd';

  // }

  //Serielle Schnittstelle aktivieren
  initUSART();
  printString("wait for command");
  // printString("I2C-Test\r\n");
  // printString("Teste I2C-Slave mit Adresse ");
  // printByte(SLAVE_ADRESSE);
  // printString("\r\n");
  // printString("\r\n"); //Leerzeile

  //in einer Endlosschleife den Inhalt der Buffer ausgeben
  while (1)
  {
    printString("i2cdata:\r\n");
    for (uint8_t i = 0; i < i2c_buffer_size; i++)
    {
      transmitByte(i2cdata[i]);
      printString("\r\n");
    }
    printString("\r\n"); //leerzeile
    _delay_ms(5000);
  } //end.while
} //end.main