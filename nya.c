#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

const char* NYAS[] = {"nya", "nya~", "mew", "meow", "mrrp", ":3", "meowmeow", "mow"};

const size_t NYA_AMOUNT = sizeof(NYAS) / sizeof(size_t);

size_t rnd(u_int64_t* state) {
    u_int64_t s = *state;
    *state = (s >> 8) + (s << 8);
    return s & (NYA_AMOUNT - 1);
}

void rand_merge(u_int64_t* state, u_int64_t other) {
    u_int64_t s = *state;
    s = (s << (s & 0b111)) + (s >> (s & 0b111)) ^ other;
    *state = (s >> 8) + (s << 8);
}

int main(int argc, char* argv[]) {
    char* nyas = malloc(NYA_AMOUNT * 16);
    size_t nyalens[NYA_AMOUNT];
    for (int i = 0; i < NYA_AMOUNT; i++) {
        size_t len = strlen(NYAS[i]);
        memcpy(nyas + i * 16, NYAS[i], len);
        *(nyas + i * 16 + len) = ' ';
        nyalens[i] = len + 1;
    }
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
    while(arg > 0) {
        u_int16_t n = 0;
        while(arg > 0 && n < 16370) {
            size_t i = rnd(&state);
            const char* nya = nyas + i*16;
            size_t nyalen = nyalens[i];
            memcpy(&buf[n], nya, 16);
            n = n + nyalen;
            arg -= 1;
        }

        fwrite(buf, 1, n, stdout);
    }

    fwrite("\r\n", 1, 2, stdout);

    free(nyas);
    return 0;
}
