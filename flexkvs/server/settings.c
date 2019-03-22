#include <stdio.h>
#include <stdlib.h>

#include "iokvs.h"

struct settings settings;

int settings_init(int argc, char *argv[])
{
    settings.udpport = 11211;
    settings.verbose = 1;
    settings.segsize = 256 * 1024;
    settings.segmaxnum = 4096;
    settings.segcqsize = 32 * 1024;
    settings.clean_ratio = 0.8;

    if (argc != 3) {
        fprintf(stderr, "Usage: flexkvs CONFIG THREADS\n");
        return -1;
    }

    settings.numcores = atoi(argv[2]);
    settings.config_file = argv[1];
    return 0;
}
