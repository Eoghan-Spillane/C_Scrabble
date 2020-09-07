//Author: Eoghan Spillane
//R00175214

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int letterCounter(char *letters, int arrayIndex){
    int counter = 1;
    //Letter counter function checks how often a letter appears in the random letter array
    for(int x = 0; x < 7; x++){
        if(letters[arrayIndex] == letters[x] && arrayIndex != x){
            counter++;
        }
        else{
            continue;
        }
    }
    return counter;
}

int charCounter(char *letters, char Char){
    int counter = 0;
    //Letter counter function checks how often a letter appears in the random letter array
    for(int x = 0; x < 7; x++){
        //printf_s("%c == %c\n", letters[x], Char);
        if(letters[x] == Char){
            //printf_s("%c == %c\n", letters[x], Char);
            counter++;
        }
    }
    return counter;
}

int getPoints(int *values, char *letters, char *guess, char *tmpLetter){
    int total = 0;

    for(int i = 0; i < strlen(guess); i++){
        for(int x = 0; x < 7; x++){

            if(guess[i] == tmpLetter[x]){
                for(int g = 0; g < 7; g++){
                    //printf("%d\n", g);
                    if(guess[i] == letters[g]){
                        //printf("%d", g);
                        if(charCounter(guess, letters[g]) <= charCounter(letters, letters[g])){
                            //printf("Boop  = %d\n", values[x]);
                            total += values[x];
                        }   else{
                            //printf("Not enough Letters\n");
                        }
                        break;
                    }
                }
            }

        }
    }
    return total;
}

int estPoints(int *values, char *guess){
    int total = 0;
    char alphabet[26]= {'a', 'b', 'c' , 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for(int x = 0; x < strlen(guess); x++) {
        for (int i = 0; i < 26; i++) {
            if(guess[x] == alphabet[i]){
                total += values[i];
            }
        }
    }

    return total;
}

void generate_letters(int number, char *destination) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    int i;
    unsigned int rand_seed;// = time(NULL);
    printf("Number < 1000:\n");
    scanf("%d", &rand_seed); // initialise the PRNG
    getchar();
    srand(rand_seed);

    // Half of the letters should be vowels
    for (i=0;i<number/2;i++, destination++) *destination = vowels[rand()%5];
    for (;i<number;i++, destination++) *destination = rand()%26+'a';
}

int read_array_from_file(const char* filepath, int *array, int array_length){
    FILE *file;
    int i;

    if ((file = fopen(filepath, "r")) == NULL) return -1;
    for (i=0;i<array_length;i++){
        if (fscanf(file, "%d", &array[i]) == EOF) break;
    }

    return i;
}


int main() {
    char letters[7]; //    letters a l
    int letterValues[8];
    char geussedWords[200][8];
    int geussWordCounter = 0;
    int geussedWordScore[10];
    int geussedWordScoreCounter = 0;
    int letterPoints[26];
    char tmpLetter[8];
    int grandTotal = 0;
    int letterCount = 0;

    generate_letters(7, letters);
//    for(int u = 0; u < 7; u++){
//        printf("%c", letters[u]);
//    }
    printf("\n");

    read_array_from_file("C:\\Users\\Eoghan Spillane\\CLionProjects\\Assignment_1\\letter_values", letterPoints, 26);

    for(int i = 0; i < 7; i++){
        int change = letters[i] - 97;
        letterValues[i] = letterPoints[change];
    }

    //Debug for loop to print the value of the random letters
//    for(int i = 0; i < 7; i++){
//        printf("letter: %c -------> score: %d\n", letters[i], letterValues[i]);
//    }

//    printf("word: %s. points: %d.", geuss, getPoints(letterValues, letters, geuss, tmpLetter));
//    printf(" estTotal: %d.", estPoints(letterPoints, geuss));

    printf("Welcome To Scrabble\n");
    memset(tmpLetter, 0, 8);
    printf("\nYour Letters (and their count) are: \n");
    for(int i = 0; i < 7; i++) {
        if(memchr(tmpLetter, letters[i], sizeof(tmpLetter))){
            //Do Nothing
        } else{
            tmpLetter[i] = letters[i];
            printf("%c --> %d\n", letters[i], letterCounter(letters, i));
            //printf("%c\n", tmpLetter[i]);
        }
    }



    while(1) {
        char geuss[8] = "";
        printf("Enter Your Word: \n");
        scanf("%s", geuss);
        getchar();


        if (estPoints(letterPoints, strlwr(geuss)) == getPoints(letterValues, letters, strlwr(geuss), tmpLetter)) {
            printf("word: %s. points: %d.", geuss, getPoints(letterValues, letters, strlwr(geuss), tmpLetter));
            grandTotal += getPoints(letterValues, letters, strlwr(geuss), tmpLetter);
            printf(" grandTotal: %d\n\n", grandTotal);
            int i = 0;

            while (geuss[i] != '\0') {
                geussedWords[geussWordCounter][i] = geuss[i];
                geussedWords[geussWordCounter][i + 1] = '\0';

                i++;
            }

            letterCount += strlen(geuss);
            geussedWordScore[geussedWordScoreCounter] = getPoints(letterValues, letters, strlwr(geuss), tmpLetter);
            geuss[i] = '\0';
            geussWordCounter++;
            geussedWordScoreCounter++;

        }  // else if(estPoints(letterPoints, geuss) >= getPoints(letterValues, letters, geuss, tmpLetter)){
            //printf("Incorrect Amount of Letters");

        //}
        else{
            printf("Invalid Letters (Or Too Many)\n");

            //Debug
            //printf("estimated: %d  actual: %d\n", estPoints(letterPoints, strlwr(geuss)), getPoints(letterValues, letters, strlwr(geuss), tmpLetter));
        }


        char choice[1];// = time(NULL);
        printf("Try Again? (y/n): \n");
        scanf("%s", choice); // initialise the PRNG

        if(*choice == 'n'){
            break;
        }
        getchar();

    }

    printf("\n--------------------------------------\n");
    printf("You entered %d letters\n", letterCount);
    printf("The Words you entered (and their points) were:\n");
    for(int i = 0; i < geussWordCounter; i++){
        printf("%s --> %d\n", geussedWords[i], geussedWordScore[i]);
    }
    printf("Your Grand Total Score is: %d\n", grandTotal);


    return 0;
}
