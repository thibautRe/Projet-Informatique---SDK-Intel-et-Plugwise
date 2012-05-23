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
    char *port ="/dev/ttyUSB0";
    
    fd = -1;
    while(fd == -1){
      printf("fd=%d\n",fd);
      fd = open(port, O_RDWR);
    }
    
    initDone = 1;
  }
}

float pulseToKWH(int pulses)
{
  return((pulses/1.0)/468.9385193);
}

float pulseToWatt(int pulses)
{
  return(pulseToKWH(pulses)*1000);
}

float getPowerInfo(Plugwise *pl)
{
  float corrected;
  char *result;
  int resultint;
  init();
  printf("init ok\n");
sendCommand(POWERINFOCODE, pl->macaddress); 
  result=getResult(pl , POWERINFORESPONSECODE);
  resultint=hexToInt(&result[4],4);
  return(pulseToWatt(resultint));
}

char *getCRC16(char *command)
{
  char result[5];
  unsigned short Checksum = calcString(command);
  sprintf(result, "%04X", Checksum);
  return(result);
}

int hexToInt(char *hexstr, int len)
{
  char tmp[64];
  strncpy(tmp, hexstr,len);
  tmp[len] = '\0';
  return strtoul(tmp, NULL, 16);
}

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
  printf("to send:%s\n",toSend);
  serialWrite(toSend);
  printf("to send ok\n");
}

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
      // or do{}while (readReturn != 1) ?;
      readReturn = read(fd, data + alreadyRead, 1);
    }
    
    alreadyRead++;
  }while(ends(data,responsecode));
  
  serialRead(data, readbytes);
  data[readbytes] = '\0';
  return &data[16];
}



void serialWrite(char *toWrite)
{
  int check = -1;
  while(check == -1){
    check = write(fd, toWrite, strlen(toWrite));
  }
}

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
