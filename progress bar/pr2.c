#include <stdio.h>


int main() {
    int i = 0;
    for (i = 0; i <1000 ; i++) {
        printf("Loading %d", i/100);
    }
    printf("\n");
    return 0;

}