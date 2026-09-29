#include <ctype.h>

#include "util/util.h"

int sd_is_alnum(const char* String)
{
    int i = 0;
    while (String[i] != '\0') {
        if (!isalpha(String[i]))
            return -1;

        i++;
    }

    return 0;
}
