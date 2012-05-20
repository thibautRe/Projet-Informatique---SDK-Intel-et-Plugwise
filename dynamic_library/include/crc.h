#ifndef _HEADER_CRC_H
#define _HEADER_CRC_H

#define CRC_VERSION     "1.16"
#define FALSE           0
#define TRUE            1
#define MAX_STRING_SIZE	2048

unsigned short update_crc_ccitt(unsigned short crc, char c);
unsigned short calcString(char *command);

#endif
