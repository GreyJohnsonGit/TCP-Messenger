#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
//void DiffOpen(char filename, char mode)
//{
//    char ch;
//  char fn = filename;
//    char m = mode;
//
//    FILE *fPtr;
//
//    fPtr = fopen(filename,mode);
//
//    if (fPtr == NULL){
//        printf("error, file doesnt exist");
//
//    }
//
//    printf("file opened, contents info: \n");
//
//    do{
//        ch = fgetc(fPtr);
//
//        putchar(ch);
//    }while(ch != EOF);
//
//    fclose(fPtr);
//
//}

int main() {
//
//    char filename[100] = "C:/Users/drago/Desktop/FileOpen/test.txt";
//
//    char mode[5] = "r";

   // DiffOpen((char)filename,(char)mode);



    FILE *fPtr;

    char ch;

    //Dummy path here for testing but entering correct path will open the file
    fPtr = fopen("C:/Users/drago/Desktop/FileOpen/test.txt", "r");

    if (fPtr == NULL){
        printf("error, file doesnt exist");
        return 1;
    }

    printf("file opened, contents info: \n");


    //This displays the content of the file; does so character by character
    do{
        ch = fgetc(fPtr);

        putchar(ch);
    }while(ch != EOF);

    fclose(fPtr);
    
    return 0;
}