#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *filename = "arquivo.dat";
    int n;
    

    file = fopen(filename, "wb");



    scanf("%d", &n);



    for (int i = 0; i < n; i++) {
        double num;
        scanf("%lf", &num);
        fwrite(&num, sizeof(double), 1, file);
    }

 
    fclose(file);

    file = fopen(filename, "rb");


   

    for (int i = n - 1; i >= 0; i--) {
        double num;
        fseek(file, i * sizeof(double), SEEK_SET);
        fread(&num, sizeof(double), 1, file);
        printf("%g\n", num);
    }

 
    fclose(file);

    return EXIT_SUCCESS;
}
