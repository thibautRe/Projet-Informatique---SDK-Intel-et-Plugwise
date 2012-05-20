#ifndef _HEADER_POL_H
#define _HEADER_POL_H

typedef struct
{
  char *macaddress;
} Plugwise;

float pulseToKWH(int pulses);
float pulseToWatt(int pulses);
float getPowerInfo(Plugwise *pl);
char *getCRC16(char *command);
int hexToInt(char *hexstr, int len);
void sendCommand(const char *code, char *macAd);
char *getResult(Plugwise *pl, char *responsecode);
int ends(char *data,char *responsecode);
void serialWrite(char *toWrite);
void serialRead(char *data, int readbytes);

#endif
