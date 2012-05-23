/**
 * \file pol.c
 * \brief Plugwise dynamic library which permits to communicate with circles
 * 
 * \author File translated from Python to C by Team Telecom Sudparis 2012
 *
 * \date May 17th 2012
 * 
 * This file will permit to communicate with the circles and get some informations.
 * Function call sequence by the program :
 * <ol>
 *  <li> 1/ pulseToWatt(int pulses); </li>
 *  <li> 2/ pulseToWatt(int pulses); </li>
 *  <li> 3/ getPowerInfo(Plugwise *pl); // second call </li>
 *  <li> 4/ getCRC16(char *command); </li>
 *  <li> 5/ hexToInt(char *hexstr, int len); </li>
 *  <li> 6/ sendCommand(const char *code, char *macAd); </li>
 *  <li> 7/ getResult(Plugwise *pl, char *responsecode); </li>
 *  <li> 8/ ends(char *data,char *responsecode); </li>
 *  <li> 9/ void serialWrite(char *toWrite); </li>
 *  <li> 10/ serialRead(char *data, int readbytes) ; </li>
 * </ol>
 */

// headers inclusions
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "crc.h"
#include "pol.h"

static const char HEADER[] = {5, 5, 3, 3, 0};
const char ENDLINE[] = {0x0d, 0x0a, 0};

const char POWERINFOCODE[] = "0012";
const char POWERINFORESPONSECODE[] = "0013";

static int fd;
static void init(void);

static void init(void)
{
  static int initDone = 0;
  if (initDone == 0){
    // BUG avec port, il faut le mettre en argument  ? static char * ?
    /// it would be better if this function takes a string as a parameter
    char *port ="/dev/ttyUSB0";
    
    fd = -1;
    while(fd == -1){
      fd = open(port, O_RDWR);
    }
    
    initDone = 1;
  }
}
/** 
 * \fn pulseToKWH(int pulses)
 * \brief transforms the pulses into Power (kW).
 * \param[in] int pulses sent from the circle.
 * \return float Power (kWh).
  */
float pulseToKWH(int pulses)
{
  return((pulses/1.0)/468.9385193);
}
/** 
 * \fn pulseToWatt(int pulses)
 * \brief transforms the Power (kW) into Power (w).
 * \param[in] int pulses sent from the circle.
 * \return float Power (W).
  */
float pulseToWatt(int pulses)
{
  return(pulseToKWH(pulses)*1000);
}
/** 
 * \fn getPowerInfo(Plugwise *pl)
 * \brief receive information from the plugwise.
 * \param[in,out] Plugwise * pointer to pl.
 * \return float Power (W).
  */
float getPowerInfo(Plugwise *pl)
{
  float corrected;
  char *result;
  int resultint;
  init();
  sendCommand(POWERINFOCODE, pl->macaddress); 
  result=getResult(pl , POWERINFORESPONSECODE);
  resultint=hexToInt(&result[4],4);
  return(pulseToWatt(resultint));
}
/** 
 * \fn getCRC16(char *command)
 * \brief calculates crc of the string.
 * \param[in,out] char* pointer to command.
 * \return char * .
  */
char *getCRC16(char *command)
{
  char result[5];
  unsigned short Checksum = calcString(command);
  sprintf(result, "%04X", Checksum);
  return(result);
}
/** 
 * \fn hexToInt(char *hexstr, int len)
 * \brief transforms hex to int.
 * \param[in,out] char* pointer to hexstr.
 * \param[in] int len. 
 * \return int
  */
int hexToInt(char *hexstr, int len)
{
  char tmp[64];
  strncpy(tmp, hexstr,len);
  tmp[len] = '\0';
  return strtoul(tmp, NULL, 16);
}
/** 
 * \fn sendCommand(const char *code, char *macAd)
 * \brief construct the message to send to the circle.
 * \param[in,out] const char* pointer to code.
 * \param[in,out] char * pointer to macad. 
 * \return void
  */
void sendCommand(const char *code, char *macAd)
{
  char command[128];
  char toSend[128];
  strcpy(command, code);
  strcat(command, macAd);
  strcpy(toSend, HEADER);
  strcat(toSend, command);
  strcat(toSend, getCRC16(command));
  strcat(toSend, ENDLINE);
  
  serialWrite(toSend);
}
/** 
 * \fn getResult(Plugwise *pl, char *responsecode)
 * \brief get the results from the circles.
 * \param[in,out] Plugwise * pointer to pl.
 * \param[in,out] char * pointer to responsecode. 
 * \return char * pointer to char.
  */
char *getResult(Plugwise *pl, char *responsecode)
{
  int readbytes = 0;
  int alreadyRead;
  char data[1024];
  int readReturn;
  
  if (responsecode == POWERINFORESPONSECODE)
    readbytes = 37;
  else if (responsecode=="0000")
    readbytes = 0;
  
  alreadyRead = 0;
  memset(data, '\0', sizeof(data));
  do{
    readReturn = -1;
    while (readReturn == -1){
      readReturn = read(fd, data + alreadyRead, 1);
    }
    
    alreadyRead++;
  }while(ends(data,responsecode));
  
  serialRead(data, readbytes);
  data[readbytes] = '\0';
  return &data[16];
}



/** 
 * \fn ends(char *data,char *responsecode)
 * \brief compare two strings.
 * \param[in,out] char * pointer to data.
 * \param[in,out] char * pointer to responsecode. 
 * \return int
  */
int ends(char *data,char *responsecode)
///ends returns 0 if the end of the first string match the second and a non null value otherwise
{
  char tmp[strlen(responsecode)];
  strcpy(tmp, &data[strlen(data)-strlen(responsecode)]);
  return strcmp(tmp,responsecode);
}
/** 
 * \fn void serialWrite(char *toWrite)
 * \brief calls write. 
 * \param[in,out] char * pointer to towrite.
 * \return void
  */
void serialWrite(char *toWrite)
{
  int check = -1;
  while(check == -1){
    check = write(fd, toWrite, strlen(toWrite));
  }
}
/** 
 * \fn serialRead(char *data, int readbytes)
 * \brief calls read.
 * \param[in,out] Plugwise * pointer to data.
 * \param[in,out] char * pointer to responsecode. 
 * \return char * pointer to char.
  */
void serialRead(char *data, int readbytes)
{
  int check;
  char tmp[readbytes];
  int readReturn = -1;
  while (readReturn == -1){
    readReturn = read(fd, &tmp, readbytes);
  }
  strcpy(data ,tmp);
}
