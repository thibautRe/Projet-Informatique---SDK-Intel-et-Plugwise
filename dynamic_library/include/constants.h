#ifndef _CONSTANTES_H
#define _CONSTANTES_H

#define DECIMALS_NUMBER 4
#define SCALE 10000.0 // 10^4

#define ORDER_SIZE (400+1)
#define UUID_SIZE (36+1)

#define BUFFER_SIZE (500+1)

#define CONFIG_NAME_SIZE (200+1)
#define ROOT_SIZE (200+1)
#define MAC_ADDRESS_SIZE (16+1)
#define COUNTER_NAME_SIZE (200+1)

#define PROCESS_SIZE (30+1)

#define MAX_POWER 100

typedef char ConfigurationName[CONFIG_NAME_SIZE];
typedef char MACaddress[MAC_ADDRESS_SIZE];

#endif
