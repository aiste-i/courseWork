#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_FOR_ARRAY_SIZE 6
#define MAX_FOR_ELEMENT_LENGHT 10
#define ARRAY_CAPACITY 99999
int numberOfArrayElements();
int getArrayElements(int numberOfElementsNeeded, unsigned long *dataForTheArray);
int getMinMaxElements( int numberOfElementsInArray,  unsigned long *arrayElements, unsigned long *minElementAddress, unsigned long *maxElementAdress);
int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements, char *message);
int checkForRightDigitInput(int *element, int lenghtMax);



int main(){
    int arraySize = 0;
    unsigned long minElement, maxElement;
    unsigned long userInputArray[ARRAY_CAPACITY] = {0};
    char *textForFirstInterval = "\nMasyvo reiksmes, kurios atitinka I intervalo [MIN, MIN + (MAX - MIN)/3] salyga:\n\n";
    char *textForSecondInterval = "\n\nMasyvo reiksmes, kurios atitinka II intervalo [MIN + (MAX - MIN)/3, MIN + (MAX - MIN)*2/3] salyga:\n\n";
    char *textForThirdInterval = "\n\nMasyvo reiksmes, kurios atitinka III intervalo [MIN + (MAX - MIN)*2/3, MAX] salyga:\n\n";
    //nusiunčiama į funkciją, kurioje gaunama masyvo dydžio reikšmė
    arraySize = numberOfArrayElements();
    // nusiunčiama į funkciją gauti masyvo elementus, patikrinama ar neįvyko klaida
    if (getArrayElements(arraySize, userInputArray) != 0)
        printf("Problem with input of array elements.\n");
    // nusiunčiama į funkciją gauti MIN ir MAX reikšmes, patikrinama ar neįvyko klaida
    if (getMinMaxElements(arraySize, userInputArray, &minElement, &maxElement) != 0)
        printf("Problem with evaluating MIN and MAX elements.\n");
    // nusiunčiama į funkciją gauti I intervalo reikšmes, patikrinama ar neįvyko klaida
    if(intervalElements( minElement, minElement + (maxElement - minElement)/3, arraySize, userInputArray, textForFirstInterval) != 0)
        printf("Problem with checking I interval.\n");
    // nusiunčiama į funkciją gauti II intervalo reikšmes, patikrinama ar neįvyko klaida
    if(intervalElements( minElement + (maxElement - minElement)/3, minElement + (maxElement - minElement)*2/3, arraySize, userInputArray, textForSecondInterval) != 0)
        printf("Problem with checking II interval.\n");
    // nusiunčiama į funkciją gauti III intervalo reikšmes, patikrinama ar neįvyko klaida
    if(intervalElements( minElement + (maxElement - minElement)*2/3, maxElement, arraySize, userInputArray, textForThirdInterval) != 0)
        printf("Problem with checking III interval.\n");

    return 0;
}

int numberOfArrayElements(){
    int sizeOfArray = 0;
    char arraySizeHolder[MAX_FOR_ARRAY_SIZE] = "";
    int arraySizeLenght = 0;
    int arraySizeErrCount = 0;
    printf("Iveskite viena sveika naturaluji skaiciu: ");
    if(fgets(arraySizeHolder, SHRT_MAX, stdin) != NULL){
        if(checkIfRightDigit(arraySizeHolder, MAX_FOR_ARRAY_SIZE) < 1){
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu. Ivestis gali buti iki 5 skaitmenu.\n");
            return 0 + numberOfArrayElements();
        }else{
            sizeOfArray = atoi(arraySizeHolder);
        }
             
    }
/*
    }
    //patikrinama ar ivestis nėra per didelė naudojant simbolių skiačių
    if(arraySizeLenght > MAX_FOR_ARRAY_SIZE){
            ++arraySizeErrCount;
            printf("\nIvestis per didele.\n");
            return 0 + numberOfArrayElements();
    }
    else{
        //patikrinama count, ar atitinka skaičiaus apribojimus
        if(arraySizeErrCount >= 2 || arraySizeErrCount == arraySizeLenght){
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu.\n");
            //jeigu ne, funkcija vėl kviečia save
            return 0 + numberOfArrayElements();
        }else{
            sizeOfArray = atoi(arraySizeHolder);
            return sizeOfArray;
        }
    }
    */
}

int checkForRightDigitInput(int *element, int lenghtMax){
    int dataLenght = 0;
    int dataErrCount = 0;
    //gaunamas simbolių skaičius
    dataLenght = strlen(element);
    //[patikrinama kiek simbolių yra ne skaičiai
    for(int i = 0; i < dataLenght; i++){
        if(isdigit(element[i]) == '\0')
            ++dataErrCount;
    }
    //patikrinama ar atitinka ilgio apribojimus
    if(dataLenght > lenghtMax){
        // jei ne pridedamas 1 prie error count
        ++dataErrCount;
    }
    return 
}

int getArrayElements(int numberOfElementsNeeded, unsigned long *dataForTheArray){
    for(int i = 0; i < numberOfElementsNeeded; i++){
        //prašoma įvesti elemento reikšmę
        printf("\nIveskite %d masyvo nari, kuris yra sveikas naturalusis skaicius: ", i + 1);
        char dataHolder[MAX_FOR_ELEMENT_LENGHT];
        int dataLenght;
        int dataErrCount;
        do{
            dataLenght = 0;
            dataErrCount = 0;
            fgets(dataHolder, SHRT_MAX, stdin);
            //gaunamas simbolių skaičius
            dataLenght = strlen(dataHolder);
            //[patikrinama kiek simbolių yra ne skaičiai
            for(int i = 0; i < dataLenght; i++){
                if(isdigit(dataHolder[i]) == '\0')
                    ++dataErrCount;
            }
            //patikrinama ar atitinka ilgio apribojimus
            if(dataLenght > MAX_FOR_ELEMENT_LENGHT){
                // jei ne pridedamas 1 prie error count
                ++dataErrCount;
                printf("\nIvestas skaicius per didelis.\nBandykite is naujo.\n");
                // patikrinama ar error nėra per daug ir ar ivestis nebuvo enter
            }else if(dataErrCount > 1 || dataErrCount == dataLenght)
                    printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu.\nBandykite is naujo.\n");
        }while(dataErrCount > 1 || dataErrCount == dataLenght);
        dataForTheArray[i] = atoi(dataHolder);
    }
    return 0;
}

int getMinMaxElements( int numberOfElementsInArray,  unsigned long *arrayElements, unsigned long *minElementAddress, unsigned long *maxElementAdress){
    //MIN ir MAX reikšmėms priskiriama pirmo elemento reikšmė
    *minElementAddress = arrayElements[0];
    *maxElementAdress = arrayElements[0];
    for(int i = 0; numberOfElementsInArray > i; i++){
        // jei masyvo reikšmė didesnė/mažesnė už MAX/MIN dabartinę reikšmę, ji priskiriama kaip nauja 
        if(*minElementAddress > arrayElements[i])
            *minElementAddress = arrayElements[i];
        if(*maxElementAdress < arrayElements[i])
            *maxElementAdress = arrayElements[i];
    }
    return 0;
}

int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements, char *message){
    // išvedama žinutė, pasakanti kurio intervalo reikšmės bus rodomos
    printf("%s", message);
    int printingCount = 0;
    for(int i = 0; i < numberOfElementsToBeChecked; i++){
        //tikrinama, kurie masyvo elementai atitinka intervalą
        if(arrayElements[i] >= minValue && arrayElements[i] <= maxValue ){
            printf("%-10lu", arrayElements[i]);
            //skaičiuoja kiek kartų atitiko intervalą
            ++printingCount;
        }
    }
    // jei nei vienas masyvo elementas neatitiko intervalo išvedama žinutė
    if(printingCount == 0)
            printf("Siam intervalui atitinkanciu skaitmenu nera.\n");
    return 0;
}
