typedef unsigned char *PUINT8;
typedef unsigned char __xdata *PUINT8X;
typedef const unsigned char __code *PUINT8C;
typedef unsigned char __xdata UINT8X;
typedef unsigned char  __data             UINT8D;

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "CH559.h"
#include "util.h"
#include "USBHost.h"

void main() {
    initClock();
    initUART0(115200, 1);
    DEBUG_OUT("Startup\n");
    initUSB_Host();
    DEBUG_OUT("Ready\n");
    while(1) {
        if(!(P4_IN & (1 << 6))) { runBootloader(); }
        checkRootHubConnections();
    }
}
