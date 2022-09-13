#include <stdio.h>
#include <stdlib.h>
static unsigned long int next = 1;

int rand1(void)
{
    printf("rand1()::next = %ld\n", next);
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65546) % 32768;
}

void srand1(unsigned int seed)
{
    next = seed;
}

int main()
{
    int count;
    unsigned seed;

    printf("Please Enter your choice for seed.\n");
    while (scanf("%u", &seed)==1)
    {
        srand1(seed);
        for (count=0; count<5; count++)
            printf("%d\n", rand1());
        
        printf("Please enter next seed (q to quit):\n");
    }
    printf("Done\n");

    return 0;
}