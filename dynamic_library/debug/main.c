#include <stdlib.h>
#include <stdio.h>
#include "pol.h"
#include "crc.h"


int main() {
  Plugwise initplugwise ={"000D6F000072914B"};
  Plugwise *ppl=&initplugwise;
  float Power= getPowerInfo(ppl);
  printf("Power=%f\n",Power);
  return EXIT_SUCCESS;
}
