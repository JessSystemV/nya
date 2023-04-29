#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* list[] = {"nya", "nya~", "mew", "meow", "mrrp", ":3", "meowmeow", "mow"};
int list_size = sizeof(list) / sizeof(char*);

char* get_string(int length) {
    char* str = malloc(length * 20 * sizeof(char)); // allocate memory for the string
    int i;
    srand(time(NULL)); // seed the random number generator
    for (i = 0; i < length; i++) {
        int index = rand() % list_size; // get a random index
        strcat(str, list[index]); // concatenate the selected string from the list
        strcat(str, " "); // add a space between words
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
