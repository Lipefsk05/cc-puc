#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int N;

    while (scanf("%d", &N) != EOF) {
        int gridLarg[N];
        int posIni[N];

        for(int i = 0; i < N ; i++) {
            scanf("%d", &gridLarg[i]);
           
            posIni[gridLarg[i]] = i;
        }

        int ordCheg[N];

      
        for(int i = 0; i < N ; i++) {
            scanf("%d", &ordCheg[i]);
        }

        int overtakes = 0;

       
        for(int i = 0; i < N; i++) {
            for(int j = i + 1; j < N; j++) {
               
                if(posIni[ordCheg[i]] > posIni[ordCheg[j]]) {
                 overtakes++;
                }
            }
        }
        
        printf("%d\n", overtakes);
    }

    

    return 0;
}