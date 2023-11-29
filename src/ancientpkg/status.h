#ifndef STATUS_H
#define STATUS_H

#include "ancientpkg.h"

int generate_status(int broken_shard_chance, DigControlFlags *dcf,
                    int *hms, // [h]as [m]issing [s]hard
                    int *bps  // [b]roken [p]ackage [s]hard
);
char *status_string(int status);

#endif /* STATUS_H */
