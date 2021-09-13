#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i = 6;
    int* p = &i;

    printf("%p\n", &i);
    return 0;
}

