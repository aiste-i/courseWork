/* 2022.11.06
Darbas - Aistes Ivanauskaites PS I kursas I grupe
Atlikta su - Windows 11, Visual studio Code, GCC compiler 
Uzduoties esme:
- paprašyti vartotojo įvesti natūralųjį skaičių, kurį panaudos masyvo dydžiui nustatyti;
- paprašyti vartotojo įvesi masyvo reikšmes;
- nustatyti MIN ir MAX reikšmes;
- patikrinti ir išvesti masyvo reikšmes, atitinkančias duotus intervalus; 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_FOR_ARRAY_SIZE 6
#define MAX_FOR_ELEMENT_LENGHT 10
#define ARRAY_CAPACITY 99999
#define NUMBER_OF_FORMULAS 3

int numberOfArrayElements();
int checkForRightDigitInput(char *element, int lenghtMax);
int getArrayElement( unsigned long *dataForElement);
int getMinMaxElements( int numberOfElementsInArray,  unsigned long *arrayElements, unsigned long *minElementAddress, unsigned long *maxElementAdress);
int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements);

int main(){
    int arraySize = 0;
    unsigned long minElement, maxElement;
    unsigned long userInputArray[ARRAY_CAPACITY] = {0};
    char *formulas[NUMBER_OF_FORMULAS] = {"[MIN, MIN + (MAX - MIN)/3]", "[MIN + (MAX - MIN)/3, MIN + (MAX - MIN)*2/3]", "[MIN + (MAX - MIN)*2/3, MAX]"};
    //nusiunčiama į funkciją, kurioje gaunama masyvo dydžio reikšmė
    arraySize = numberOfArrayElements();
    // nusiunčiama į funkciją gauti masyvo elementus, patikrinama ar neįvyko klaida
    for( int i = 0; i < arraySize; i++){
        printf("\nIveskite %d masyvo nari, kuris yra sveikas naturalusis skaicius: ", i + 1);
        if(getArrayElement(&userInputArray[i]) == 0)
            printf("Atlikta sekmingai. Teskite.\n");
    }
    // nusiunčiama į funkciją gauti MIN ir MAX reikšmes, patikrinama ar neįvyko klaida
    if (getMinMaxElements(arraySize, userInputArray, &minElement, &maxElement) != 0)
        printf("Problem with evaluating MIN and MAX elements.\n");
    // nusiunčiama į funkciją gauti I intervalo reikšmes, patikrinama ar neįvyko klaida
    for(int i = 0; i < NUMBER_OF_FORMULAS; i++){
        printf("\nMasyvo reiksmes, kurios atitinka %d intervalo %s salyga:\n\n", i + 1, formulas[i]);
        if(intervalElements(minElement + (maxElement - minElement)*i/3 , minElement + (maxElement - minElement)*(i + 1)/3, arraySize, userInputArray) != 0)
            printf("Problem with evaluating %d interval elements.\n", i + 1);
    }
    return 0;
}

int numberOfArrayElements(){
    int sizeOfArray = 0;
    char arraySizeHolder[MAX_FOR_ARRAY_SIZE] = "";
    printf("Iveskite viena sveika naturaluji skaiciu: ");
    if(fgets(arraySizeHolder, SHRT_MAX, stdin) != NULL){
        if(checkForRightDigitInput(arraySizeHolder, MAX_FOR_ARRAY_SIZE) > 1){
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu. Ivestis gali buti iki %d skaitmenu.\n", MAX_FOR_ARRAY_SIZE - 1);
            return 0 + numberOfArrayElements();
        }else{
            sizeOfArray = atoi(arraySizeHolder);
            return sizeOfArray;
        } 
    }
}

int checkForRightDigitInput(char *element, int lenghtMax){
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
    if(dataLenght > lenghtMax || dataLenght == dataErrCount){
        // jei ne pridedamas 1 prie error count
        ++dataErrCount;
    }
    return dataErrCount;
}

int getArrayElement( unsigned long *dataForElement){
    int counterForWhileCycle = 0;
    char dataHolder[MAX_FOR_ELEMENT_LENGHT];
    do{
        free(dataForElement);
        if(counterForWhileCycle > 0)
            printf("\nNeteisinga ivestis. Negalimi simboliai, neigiami skaiciai, skaiciai su kableliu. Ivestis gali buti iki %d skaitmenu.\n", MAX_FOR_ELEMENT_LENGHT - 1);
        ++counterForWhileCycle;
        fgets(dataHolder, SHRT_MAX, stdin);
    }while(checkForRightDigitInput(dataHolder, MAX_FOR_ELEMENT_LENGHT) > 1);
    *dataForElement = atoi(dataHolder);
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

int intervalElements( int minValue, int maxValue, int numberOfElementsToBeChecked, unsigned long *arrayElements){
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
