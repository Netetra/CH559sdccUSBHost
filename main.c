typedef unsigned char *PUINT8;
typedef unsigned char __xdata *PUINT8X;
typedef const unsigned char __code *PUINT8C;
typedef unsigned char __xdata UINT8X;
typedef unsigned char  __data             UINT8D;

#include <stdint.h>
#include <stdio.h>
#include <string.h>
// #include "CH559.h"
#include "register.h"
#include "util.h"
#include "USBHost.h"

void main(void) {
    clock_init();
    uart0_init(115200, 1);
    DEBUG("Startup\n");
    initUSB_Host();
    DEBUG("Ready\n");
    while(1) {
        checkRootHubConnections();
    }
}
