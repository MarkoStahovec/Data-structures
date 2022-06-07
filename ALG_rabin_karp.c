#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define d 256


void rk_search(char txt[], char pat[]) {
    int k = 101;
    int pat_len = strlen(pat);
    int txt_len = strlen(txt);
    int hp = 0; // hash value for pattern
    int ht = 0; // hash value for text
    int h = 1;

    // initial hash of our pattern
    for (int i = 0; i < pat_len-1; i++) {
        h = (h * d) % k;
    }


    for (int i = 0; i < pat_len; i++) {
        hp = (d * hp + pat[i]) % k;
        ht = (d * ht + txt[i]) % k;
    }


    for (int i = 0; i <= txt_len - pat_len; i++) {
        if (hp == ht) {
            for (int j = 0; j < pat_len; j++) {
                if (txt[i+j] != pat[j]) {
                    break;
                }
                if ((j+1) == pat_len) {
                    printf("Pattern found at: %d\n", i);
                }
            }
        }

        ht = (d*(ht - txt[i]*h) + (txt[i+pat_len])) % k;

        if (ht < 0) {
            ht += k;
        }
    }

}


int main(void) {
    char txt[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been "
                 "the industry's standard dummy text ever since the 1500s, when an unknown "
                 "printer took a galley of type and scrambled it to make a type specimen book.";

    char pattern[] = "dummy";

    rk_search(txt, pattern);


    return 0;
}

