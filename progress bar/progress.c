#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

int main() {
    const char spin_chars[] = "|\\/-";
    int spin_index = 0;
    printf("Loading ");
    fflush(stdout);

    for (int i = 0; i <=100; i++){

        if (i%10==0){
            putchar('-');
            fflush(stdout);
        }

        printf("/r");
        printf("Loading ");
        fflush(stdout);
        
        for(int j = 0; j<i/10; j++){
            putchar('-');
        }

        putchar(spin_chars[spin_index++]);
        fflush(stdout);

        printf("%3d%%", i);
        fflush(stdout);

        usleep(100000);

        putchar('\b');

        if (spin_index == sizeof(spin_chars) - 1) {
            spin_index = 0;
        }
    }
    
    putchar('\n');
    printf("Done!\n");
    return 0;

}