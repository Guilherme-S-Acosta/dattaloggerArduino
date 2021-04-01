#include "max6675.h" //INCLUSÃO DE BIBLIOTECA TERMOPAR
#include <SPI.h>//INCLUSÃO DE BIBLIOTECA DO DATALOGGER
#include <SD.h>

/*
 * ENTRADAS DO MODULO DO SDCARD
 ** MOSI - PINO DIGITAL 11
 ** MISO - PINO DIGITAL 12
 ** CLK - PINO DIGITAL 13
 ** CS - PINO DIGITAL 4
 */

//VARIAVEIS DE CONFIGURAÇÃO DO TERMOPAR
int ktcSO = 8; //PINO DIGITAL 8 (SO) 
int ktcCS = 9; //PINO DIGITAL 9 (CS)
int ktcCLK = 10; //PINO DIGITAL 10 (CLK / SCK)
//VARIAVEIS DOS DADOS
int tempo = 1;
float temperatura;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)
File dados;
  
void setup()
{
  if (!SD.begin(4)) 
  { //TESTE DO CARTÃO SD
    Serial.println("initialization failed!");
    while (1);
  }
  //CRIAÇÃO DO CABEÇALHO NO ARQUIVO DO DATALOGGER
  dados = SD.open("teste.txt", FILE_WRITE);
  dados.println("Tempo(s);Temperatura sensor(°C)");
  dados.close();
  //Serial.begin(9600); //INICIA O MONITOR SERIAL
  delay(1000); //INTERVALO DE 1000 MILISSEGUNDOS
}

void loop()
{
  dados = SD.open("teste.txt", FILE_WRITE);
  //Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  temperatura = ktc.readCelsius(); //GRAVA A TEMPERATURA NA VARIAVEL
  //Serial.print(temperatura); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  //Serial.println("*C \n\n"); //IMPRIME O TEXTO NO MONITOR SERIAL
  //GRAVAÇÃO DOS DADOS NO DATALOGGER
  dados.print(tempo); 
  dados.print(";");
  dados.print(temperatura);
  dados.println();
  dados.close();
  tempo=tempo+1;
  delay(1000); //INTERVALO DE 1000 MILISSEGUNDOS
}
