//crossword.c
//name: katie massman
//assignment: lab 8, main driver

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "crossfunc.h"

int main (int argc, char *argv[]){
   if (argc > 3) {
      printf("invalid input");
      return 1;
   }

   //create board
   if (argc ==1) {
      //initialize array of words, max 20 words, 16 letter
      int wordcount = 0;
      char inputword[wordsize]; //only 15 letters each
      Word words[max]; //maximum 20 words
   
      printf("Anagram Crossword Puzzle Generator\n");
      printf("----------------------------------\n");
   
      //read in all words, rejecting non valid words
      
      printf("Enter a list of words: \n");
      
      //scan words into array
      while (wordcount<max){ //while list of words less than 20
         scanf("%s", inputword);
         if (strcmp(inputword, ".") ==0) break; //end at period
         if (strlen(inputword)<2 || strlen(inputword)>15) { //restart for loop if <2
            printf("word not valid\n");   
            continue;
         }
         if (ifalpha(inputword)){ //calls boolean function to check if alpha
            for (int i=0; i<strlen(inputword);i++){ //copy into array, make uppercase
               inputword[i] = toupper(inputword[i]);
            }
            strcpy(words[wordcount].word,inputword); //copy into word struct
            words[wordcount].length = strlen(inputword); //copy into length struct 
            wordcount ++;
         }
         else {
            printf("word not valid\n");
            continue;
         }
      }
      
      //sort words in descending order
      sortwords(words, wordcount);

      //initialize boards
      char sboard[size][size];
      sinitialize(sboard);

      char pboard[size][size];
      pinitialize(pboard);

      //place and erase words
      placeword(sboard,words);
      placewords(sboard, wordcount, words);
      extracredit(sboard, words, wordcount); //go back to words could not place
      eraseword(pboard, words, sboard);
      

      //display words
      printf("Solution:\n");
      temp(sboard);
      printf("Crossword puzzle:\n");
      temp(pboard);
      //display if certain words cant place
      cantplace(words, wordcount);
      //call function to make clues
      Clue clues[wordcount];
      dispclues(words, wordcount, clues);
   }
  
   //interactive mode
   //command line input ==2
   else if (argc ==2){
      FILE *fp = fopen(argv[1], "r");
      if (fp ==NULL){
         printf("error opening file\n");
         return 1;
      }
      Word words[max];
      int wordcount = readin(fp, words);
   
      //sort words in descending order
      sortwords(words, wordcount);

      //initialize boards
      char sboard[size][size];
      sinitialize(sboard);
      char pboard[size][size];
      pinitialize(pboard);

      //place and erase words
      placeword(sboard,words);
      placewords(sboard, wordcount, words);
      extracredit(sboard,words,wordcount); //go back to words count not place
      eraseword(pboard, words, sboard);

      //display if cant place
      cantplace(words, wordcount);

      //display words
      printf("Solution:\n");
      temp(sboard);
      printf("Crossword puzzle:\n");
      temp(pboard);

      //call function to make clues
      Clue clues[wordcount];
      dispclues(words, wordcount, clues);
   }
   //command line input ==3
   else if (argc ==3){
      FILE *fp = fopen(argv[1], "r");
      if (fp ==NULL){
         printf("error opening file\n");
         return 1;
      }
      FILE *fp2 = fopen(argv[2], "w");
      if (fp2==NULL){
         printf("error opening file\n");
         return 1;
      }

      Word words[max];
      int wordcount = readin(fp, words);
   
      //sort words in descending order
      sortwords(words, wordcount);

      //initialize boards
      char sboard[size][size];
      sinitialize(sboard);
      char pboard[size][size];
      pinitialize(pboard);

      //place and erase words
      placeword(sboard,words);
      placewords(sboard, wordcount, words);
      extracredit(sboard, words, wordcount);//go back to words could not placed
      eraseword(pboard, words, sboard);

      //display words
      fprintf(fp2, "Solution:\n");
      temptofile(fp2, sboard);
      fprintf(fp2,"Crossword puzzle:\n");
      temptofile(fp2, pboard);

      //display if certain words cant place
      filecantplace(fp2, words, wordcount);
      //call function to make clues
      Clue clues[wordcount];
      cluestofile(fp2, words, wordcount,clues);
      fclose(fp);
      fclose(fp2);
   }
return 0;

}
