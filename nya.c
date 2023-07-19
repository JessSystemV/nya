#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char* list[] = {"nya", "nya~", "mew", "meow", "mrrp", ":3", "meowmeow", "mow"};
const size_t list_lens[] = {3, 4, 3, 4, 4, 2, 8, 3};
int list_size = sizeof(list) / sizeof(char*);

char* get_string(int length) {
    char* str = malloc(length * 20 * sizeof(char)); // allocate memory for the string
    int len = 0;
    int i;
    srand(time(NULL)); // seed the random number generator
    for (i = 0; i < length; i++) {
        int index = rand() % list_size; // get a random index
        size_t next_char_size = list_lens[index]; // get the length of the gotten string
        strcat(&str[len], list[index]); // concatenate the selected string from the list
        strcat(&str[len], " "); // add a space between words
        len += next_char_size + 1;
    }
    return str;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <length>\n", argv[0]);
        return 1;
    }
    int length = atoi(argv[1]);
    char* str = get_string(length);
    printf("%s\n", str);
    free(str); // free the dynamically allocated memory
    return 0;
}
