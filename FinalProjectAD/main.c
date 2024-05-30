#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Lobster
{
    int id;
    int length;
    int value;
};
float valuePerUnit(struct Lobster Lobsters)
{
    return Lobsters.value / (Lobsters.length * 1.0);
}
void sortLobsters(struct Lobster *Lobsters, int noLobsters)
{
    int iterator1;
    int iterator2;
    int indexMin;
    int auxSize;
    int auxId;
    int auxValue;

    for(iterator1 = 0; iterator1 < noLobsters - 1; iterator1++){
        indexMin = iterator1;
        for(iterator2 = iterator1 + 1; iterator2 < noLobsters; iterator2++){
            if (valuePerUnit(Lobsters[indexMin]) < valuePerUnit(Lobsters[iterator2]) ){
                indexMin = iterator2;
            }
        }
        if (indexMin != iterator1){
            auxSize = Lobsters[indexMin].length;
            auxId = Lobsters[indexMin].id;
            auxValue = Lobsters[indexMin].value;
            Lobsters[indexMin].length = Lobsters[iterator1].length;
            Lobsters[indexMin].id = Lobsters[iterator1].id;
            Lobsters[indexMin].value = Lobsters[iterator1].value;
            Lobsters[iterator1].length = auxSize;
            Lobsters[iterator1].id = auxId;
            Lobsters[iterator1].value = auxValue;
        }
    }
}
void repartizareLobsters(struct Lobster *Lobsters, int noLobsters, int netSize)
{
    int iterator = 0;
    int currentNetSize = netSize;
    float valueNet = 0.0;

    for(iterator = 0; iterator < noLobsters && currentNetSize > 0; iterator++){
        if(Lobsters[iterator].length <= currentNetSize){
            printf("\nThe lobster no.%d has been chosen, with the value of %d and the length of %d",Lobsters[iterator].id,Lobsters[iterator].value,Lobsters[iterator].length);
            valueNet += Lobsters[iterator].value;
            currentNetSize -= Lobsters[iterator].length;
        }
    }
    printf("\nThe maximum value obtained is %f", valueNet);
}

void generareLobsters(struct Lobster *Lobsters, int noLobsters)
{
    int iterator;
    for(iterator = 0; iterator < noLobsters; iterator++)
    {
        Lobsters[iterator].id = iterator;
        Lobsters[iterator].length = rand()%500+1;
        Lobsters[iterator].value = rand()%500+1;
    }
}
int generateNumbers()
{
    int generatedNumber=rand()%10000+1;
    return generatedNumber;
}

int main()
{
    srand(time(NULL));
    clock_t tic = clock();
    struct Lobster *Lobsters;
    int noLobsters=generateNumbers();
    int netSize=generateNumbers();
    Lobsters = malloc(noLobsters * sizeof(struct Lobster));
    generareLobsters(Lobsters, noLobsters);


    printf("  Number of lobsters:%d\n  Net size:%d", noLobsters, netSize);
    printf("\n------Selected lobsters------  ");
    sortLobsters(Lobsters, noLobsters);
    repartizareLobsters(Lobsters, noLobsters, netSize);
    clock_t toc = clock();
    printf("\nElapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}
