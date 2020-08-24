#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main() {
    int i;
    int val;
    int sum_wins = 0;
    int display_size = 10;
    int number_size = 26;
    int* pDisplay = (int*)malloc(display_size * sizeof(int));
    int* pNumber =  (int*)malloc(number_size * sizeof(int));
    
    srand(time(NULL));
    
    //can run a pragma here as well where we initialise all array elements to 0 
    for(i = 0; i < number_size; i++) {
        pNumber[i] = 0;
    }
    
    #pragma omp parallel for num_threads(4) schedule(static, 2) 
    //writing pragma omp parallel for will work directly on the first for loop it sees only.
    //if we want the following for loops to run in parallel, have to specify #pragma again   
    for(i = 0; i < display_size; i++) {
        val = rand() % 25 + 1; // this will generate a random number from 0 to 24 and then add 1 to get (1, 25)
        pDisplay[i] = val;
        pNumber[val] += 1;
        //printf("display %d: %d\n", i+1, pDisplay[i]); //this will print these statements out of order because it's being run in the parallel loop
        
    }
    
    for(i = 0; i < display_size; i++) {
        printf("display %d: %d\n", i+1, pDisplay[i]);    
    }
    
    for(i = 0; i < number_size; i++) {
        //printf("number %d: %d times\n", i, pNumber[i]);
        if(pNumber[i] > 1) {
            //printf("%d appeared %d times\n", i, pNumber[i]);
            sum_wins += 1;
        }
    }
    
    printf("number of wins: %d\n", sum_wins);
    
    free(pDisplay);
    free(pNumber);
    
    return 0;
    

}
