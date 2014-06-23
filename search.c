#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *quickSearch(void *base, size_t nmeb, size_t size, size_t rank, int(*compar)(const void *, const void *));
void swap(void *p1, void *p2, size_t size);

int comparStr(const void *p1, const void *p2);
int comparInt(const void *p1, const void *p2);

void *quickSearch(void *base, size_t nmeb, size_t size, size_t rank, int(*compar)(const void *, const void *))
{
    if (nmeb < 2)
        return base;

    int i, j, key;
    
    key = rand() % nmeb;
    swap(base, base + key * size, size);
    
    i = 1;
    j = nmeb - 1;
    while (i < j) {
        if (compar(base + i * size, base) > 0) {
            swap(base + i * size, base + j * size, size);
            --j;
        } else
            ++i;
    }
    

    if (compar(base, base + i * size) > 0)
        swap(base, base + i * size, size);
    
    if (i == rank)
        return base + (i - 1) * size;
    if (i > rank)
        return quickSearch(base, i, size, rank, compar);
    else
        return quickSearch(base + i * size, nmeb - i, size, rank - i, compar);
}

void swap(void *p1, void *p2, size_t size)
{
    void *temp;

    temp = malloc(size);
    if (temp == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(temp, p1, size);
    memcpy(p1, p2, size);
    memcpy(p2, temp, size);

    free(temp);
}

int comparStr(const void *p1, const void *p2)
{
    return strcmp(* (char * const *) p1, * (char * const *) p2);
}

int comparInt(const void *p1, const void *p2)
{
    return (*(const int *) p1 - *(const int *) p2);
}

int main(int argc, char const *argv[])
{
    int i, *num;
    int arr[5] = {4, 2, 1, 3, 5};

    printf("Integer Sort\n");
    printf("Original: ");
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Sorted  : ");
    for (i = 1; i <= 5; i++) {
        num = (int *)quickSearch(arr, 5, sizeof(int), i, comparInt);
        printf("%d ", *num);
    }
    printf("\n");
    return 0;
}