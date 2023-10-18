#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

const char* NYAS = "nya     nya~    mew     meow    mrrp    :3      meowmeowmow     ";

const size_t NYALENS[] = {4, 5, 4, 5, 5, 3, 9, 4};
const size_t MAX = sizeof(NYALENS) / sizeof(size_t);

size_t rnd(u_int64_t* state) {
    u_int64_t s = *state;
    *state = (s >> 8) + (s << 8);
    return s & (MAX - 1);
}

void rand_merge(u_int64_t* state, u_int64_t other) {
    u_int64_t s = *state;
    s = (s << (s & 0b111)) + (s >> (s & 0b111)) ^ other;
    *state = (s >> 8) + (s << 8);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <length>\n", argv[0]);
        return 1;
    }
    u_int64_t arg = atoll(argv[1]);
    u_int64_t state = arg;
    for(int i = 0; i < 100; i++) {
        rand_merge(&state, time(NULL));
    }
    char buf[16384];
    memset(buf, ' ', sizeof(buf));
    while(arg > 0) {
        u_int16_t n = 0;
        while(arg > 0 && n < 16370) {
            size_t i = rnd(&state);
            const char* nya = NYAS + i*8;
            size_t nyalen = NYALENS[i];
            memcpy(&buf[n], nya, 8);
            n = n + nyalen;
            arg -= 1;
        }

        if (arg == 0) {
            // replace the last whitespace with a newline
            // to prevent breaking some terminals
            buf[n-1] = '\n';
        }
        fwrite(buf, 1, n, stdout);
        memset(buf, ' ', sizeof(buf));
    }

    (void)state;
    return 0;
}
