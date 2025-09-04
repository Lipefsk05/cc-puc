#include <stdio.h>
#include <string.h>

int main()
{
    char n[100];

    scanf(" %[^\n]", n);

    while (strcmp(n, "FIM") != 0)
    {
        int m = 0;

        for (int i = 0; i < strlen(n); i++)
        {
            m += n[i] - 48;
        }

        printf("%i\n", m);
        
        scanf(" %[^\n]", n);
    }
}