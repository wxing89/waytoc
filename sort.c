#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));
void mergeSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));
void quicksort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));
void bubbleSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));
void shellSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));

void swap(void *p1, void *p2, size_t size);

int comparStr(const void *p1, const void *p2);
int comparInt(const void *p1, const void *p2);


void *insertionSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *))
{
    int i, j;
    for (i = 1; i < nmeb; i++)
        for (j = i; j > 0; j--)
            if (compar(base + (j - 1) * size, base + j * size) > 0) {
                swap(base + (j - 1) * size, base + j * size, size);
            } else
                break;
}

void *mergeSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *))
{
    if (nmeb < 2)
        return;
    
    mergeSort(base, nmeb / 2, size, compar);
    mergeSort(base + (nmeb / 2) * size, nmeb - nmeb / 2, size, compar);

    int i, j;
    void * hold;

    hold = calloc(nmeb, size);
    if (hold == NULL) {
        exit(EXIT_FAILURE);
    }
    
    i = j = 0;
    while (i < nmeb / 2 && j < nmeb - nmeb / 2) {
        if (compar(base + i * size, base + (nmeb / 2 + j) * size) > 0) {
            memcpy(hold + (i + j) * size, base + (nmeb / 2 + j) * size, size);
            ++j;
        } else {
            memcpy(hold + (i + j) * size, base + i * size, size);
            ++i;
        }
    }

    if (i == nmeb / 2) {
        memcpy(hold + (i + j) * size, base + (nmeb / 2 + j) * size, (nmeb - nmeb / 2 - j) * size);
    } else {
        memcpy(hold + (i + j) * size, base + i * size, (nmeb / 2 - i) * size);
    }

    memcpy(base, hold, nmeb * size);
    free(hold);
}

void *quicksort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *))
{
    if (nmeb < 2)
        return;

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

    quicksort(base, i, size, compar);
    quicksort(base + i * size, nmeb - i, size, compar);
}

void *bubbleSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *))
{
    int i, j;
    for (i = 0; i < nmeb - 1; i++)
        for (j = 0; j < nmeb - 1; j++)
            if (compar(base + j, base + j + 1) > 0)
                swap(base + j, base + j + 1, size);
}

void *shellSort(void *base, size_t nmeb, size_t size, int(*compar)(const void *, const void *));

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

#define ARRSIZE 10000

int main()
{
    int i;
    int arr[ARRSIZE];
    time_t t1;
    time_t t2;

    srand(0);
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = rand();
    }

    time(&t1);
    quicksort(arr, ARRSIZE, sizeof(int), comparInt);
    time(&t2);
    printf("quicksort: %d\n", (int)(t2) - (int)t1);
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    srand(0);
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = rand();
    }

    time(&t1);
    insertionSort(arr, ARRSIZE, sizeof(int), comparInt);
    time(&t2);
    printf("insertionSort: %d\n", (int)(t2) - (int)t1);
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    srand(0);
    for (i = 0; i < ARRSIZE; ++i) {
        arr[i] = rand();
    }

    time(&t1);
    bubbleSort(arr, ARRSIZE, sizeof(int), comparInt);
    time(&t2);
    printf("bubbleSort: %d\n", (int)(t2) - (int)t1);
}

#if 0
int main(int argc, char *argv[])
{
    int i;
    int arr[5] = {4, 2, 1, 3, 5};

    printf("Integer Sort\n");
    printf("Original: ");
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n");

    quicksort(arr, 5, sizeof(int), comparInt);

    printf("Sorted  : ");
    for (i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    if (argc < 2)
        exit(EXIT_SUCCESS);

    printf("String Sort\n");
    printf("Original: ");
    for (i = 1; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    quicksort(&argv[1], argc - 1, sizeof(argv[1]), comparStr);
    printf("Sorted  : ");
    for (i = 1; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");

    exit(EXIT_SUCCESS);
}
#endif