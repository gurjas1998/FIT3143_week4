#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


int main() {
    int i;
    int val;
    int sum_wins = 0;
    int display_size = 10;
    int number_size = 26;
    int* pDisplay = (int*)malloc(display_size * sizeof(int)); // for some reason, initialising a stack array generated random number elements??
    int* pNumber = (int*)malloc(number_size * sizeof(int)); // whereas going heap method via malloc generated with 0s...
    
    srand(time(NULL));
    
    for(i = 0; i < number_size; i++) {
        printf("%d\n", pNumber[i]);
    }
    #pragma omp parallel for num_threads(4) schedule(static, 2) // if i get rid of this pragma then the code works fine, but when it's there, pNumber has random numbers????
    // where to insert the pragma stuff?
    
    
        for(i = 0; i < display_size; i++) {
            val = rand() % 25 + 1; // this will generate a random number from 0 to 24 and then add 1 to get (1, 25)
            pDisplay[i] = val;
            pNumber[val] += 1;
            //printf("pNumber[%d] is %d\n", i, pNumber[i]);
            printf("display %d: %d\n", i+1, pDisplay[i]);
        }
    
    
    
    for(i = 0; i < number_size; i++) {
        printf("number %d: %d times\n", i, pNumber[i]);
        if(pNumber[i] > 1) {
            //printf("%d appeared %d times\n", i, pNumber[i]);
            sum_wins += 1;
        }
    }
    for(i = 0; i < number_size; i++) {
        /**if(pNumber[i] > 1) {
            printf("%d appeared %d times\n", i, pNumber[i]);
        }*/
    }
    printf("number of wins: %d\n", sum_wins);
    free(pDisplay);
    free(pNumber);
    
    return 0;
    

}
