/*

exercise 1:

Read a text file full of double values and convert it into a binary file.
Write code that converts it back to double values as a text file.

1. Read the file as a text file (for instance using fscanf) - Check
2. Write each double into a new file where you save the double in binary format (writing sizeof(double) bytes)

Then read the binary file and create a new file where you save the numbers in a text-file (should result in the same file as your original file)


*/

#include <stdio.h>

int main(int argc, char* argv[]){

    FILE *pTextFile = NULL;
    FILE *pBinaryFile = NULL;

    double dNumberRead = 0;
    double dTextFileNumber = 0;

    //Return a file pointer
    pTextFile = fopen("lecture-6/double.txt","w");

    //Checking if the pointer isn't ot null
    if(pTextFile != NULL){

        //Printing 100 double values
        for(int i = 0; i < 100; i++){
            dTextFileNumber = (double ) i;
            fprintf(pTextFile,"%f\n",dTextFileNumber);
        }

        //Closing file handler
        fclose(pTextFile);

    }

    //Reassigning file handler to read mode for reading double values.
    pTextFile = fopen("lecture-6/double.txt","r");
    pBinaryFile = fopen("lecture-6/double.dat","wb");

    if(pTextFile != NULL){

        //Checking for end of file
        while (!feof(pTextFile)){
            //Reading each double value storing it in variable dNumberRead.
            //If It's 1, it means we got another double to write to binary file.
            if(fscanf(pTextFile,"%lf", &dNumberRead) == 1){
                fwrite(&dNumberRead,sizeof (double ),1,pBinaryFile);
            }
        }

        //Closing both file handlers.
        fclose(pTextFile);
        fclose(pBinaryFile);

    }

    pBinaryFile = fopen("lecture-6/double.dat","rb");
    pTextFile = fopen("lecture-6/double.txt","r");

    if(pBinaryFile != NULL){

        double binaryDouble = 0;

        while (!feof(pBinaryFile)){
            if(fread(&binaryDouble,sizeof (double),1,pBinaryFile) == 1){
                printf("\n|Binary number printed: %lf|\n",binaryDouble);
            }

            if(fscanf(pTextFile,"%lf", &dNumberRead) == 1){
                printf("\n|Double (text) number printed: %lf|\n", dNumberRead);
                printf("\n-----------------------------------------------\n");
            }


        }

        fclose(pBinaryFile);
        fclose(pTextFile);

    }




}