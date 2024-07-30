//crossfunc.c
//name: katie massman
//assignment: lab 8, functions file

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "crossfunc.h"
#include <stdbool.h>

//function for checking if alphabet
int ifalpha(char inputword[]){
   for (int i=0;i<strlen(inputword); i++){
      if (isalpha(inputword[i])==0)return 0;
      else continue;
   }
   return 1;
}

//function for reading in file
int readin(FILE*fp, Word words[]){
      int wordcount = 0;
      char inputword[wordsize]; //only 15 letters each
      while (wordcount<max && fscanf(fp, "%s", inputword) != EOF){
           if (strcmp(inputword, ".") ==0) break; //end at period
           if (strlen(inputword)<2 || strlen(inputword)>15) continue; //restart for loop if <2 or >15
           if (ifalpha(inputword)){ //calls boolean function to check if alpha
               for (int i=0; i<strlen(inputword);i++){ //copy into array, make uppercase
                  inputword[i] = toupper(inputword[i]);
               }
               strcpy(words[wordcount].word,inputword); //copy into word struct
               words[wordcount].length = strlen(inputword); //copy into length struct 
               wordcount ++;
            }  
            else continue;
         }
      return wordcount;
}

//function for reordering words
void sortwords(Word words[], int wordcount){
   
   for (int i=0;i<wordcount-1;i++){
      for (int j=0;j<wordcount-i-1;j++){
         if (strlen(words[j].word)<strlen(words[j+1].word)){
            char temp[wordsize];
            strcpy(temp,words[j+1].word);
            strcpy(words[j+1].word,words[j].word);
            strcpy(words[j].word,temp); 
            
            words[j+1].length = strlen(words[j+1].word); //update stringlength
            words[j].length = strlen(words[j].word);
         }
         else if(strlen(words[j].word) == strlen(words[j].word)) continue; // same length dont change
         else if(strlen(words[j].word)>strlen(words[j+1].word)) continue; // already in order dont change
      }  
   }
}

//function for filling board with periods
void sinitialize(char board[][size]){
   int x,y;
   for (int i=0; i<size; i++){
      for (int j=0; j<size;j++){
         board[i][j] = '.';
      }
   }
}
//function for filling board with hashtags
void pinitialize(char board[][size]){
   int x, y;
   for (int i=0;i<size;i++){
      for (int j=0; j<size;j++){
         board[i][j] = '#';
      }
   }
}

//function for printing board to another file
void temptofile(FILE *fp2,char board[][size]){
   //print top border
   for (int i=0; i<size+4;i++){
      fprintf(fp2,"-");
   }
   fprintf(fp2,"\n");
   //print sides
   for (int i=0; i<size;i++){
      for (int j=0; j<size;j++){
         if (j==0){
            fprintf(fp2,"| %c", board[i][j]);
         }
         else if(j ==size-1){
            fprintf(fp2,"%c |", board[i][j]);
         }
         else {
            fprintf(fp2,"%c", board[i][j]);
         }
      }
   fprintf(fp2,"\n");
   }
   //print bottom
   for (int i =0; i<size+4; i++){
      fprintf(fp2,"-");
   }
   fprintf(fp2,"\n");
}

//function for displaying current board
void temp(char board[][size]){
   //print top border
   for (int i=0; i<size+4;i++){
      printf("-");
   }
   printf("\n");
   //print sides
   for (int i=0; i<size;i++){
      for (int j=0; j<size;j++){
         if (j==0){
            printf("| %c", board[i][j]);
         }
         else if(j ==size-1){
            printf("%c |", board[i][j]);
         }
         else {
            printf("%c", board[i][j]);
         }
      }
   printf("\n");
   }
   //print bottom
   for (int i =0; i<size+4; i++){
      printf("-");
   }
   printf("\n");
}

//function for placing first word
void placeword(char board[][size], Word word[]){
   int startingposition = (size-word[0].length)/2;
   for (int i=0; i<word[0].length;i++){
      board[size/2][startingposition+i]=word[0].word[i];
   }
   word[0].x = startingposition+1;
   word[0].y = size/2+1;
   word[0].direction='a';
   word[0].placed =1;
}

//function for checking for end and beginning of words horizontally
void hneighbors(char board[][size], Word words[], int i, int r, int c, int j, int *keeptrying){
   int f;
   f = c-j + words[i].length;
   if (board[r][f] != '.' || board [r][c-j-1] !='.'){
      *keeptrying = 4;
   }
   else {
      *keeptrying;
   }
}


//function for checking end and beginning of words vertically
void vneighbors(char board [][size], Word words[], int i, int r, int c, int j, int *keeptrying){
   int f;
   f = r-j + words[i].length;
   if (board[f][c] != '.'|| board [r-j-1][c] != '.'){
      *keeptrying = 4;
   }
   else {
      *keeptrying;
   }
}

//function for placing the rest of the words
void placewords(char board[][size], int wordcount, Word words[]){
   for (int i=1; i<wordcount;i++){           //loop thru all words
      words[i].placed = 0;
      for (int j=0; j<words[i].length;j++){  //loop thru all letters 
          for (int r=0; r<size;r++){          //loop thru rows of board
              for (int c=0;c<size;c++){        //loop thru columns of board
                  if (words[i].word[j] == board[r][c]){  //check to see if match
                     //if the word can fit VERTICALLY
                     if (board[r-1][c] == '.' && board[r+1][c]== '.'
                        && board[r-1][c+1]=='.' && board[r+1][c-1]=='.'
                        && board[r-1][c-1] =='.' && board[r+1][c+1]=='.'
                        && r-j+1>0 && r-j+words[i].length-1<size){

                        //make sure no letters are already in the column, and check diagonal
                        int keeptrying = 0;
                        
                       for (int x=0;x<words[i].length;x++){
                           if (board[r-j+x][c-1] != '.')keeptrying++;
                           if (board[r-j+x][c+1] !='.') keeptrying++;
                           if (board[r-j+x][c] !='.') keeptrying++;
                       }

                       //function that check beginning and end of word
                       vneighbors(board, words, i, r, c, j, &keeptrying);
                       //place word VERTICALLY
                       if (keeptrying <4 ){ //can only touch at most 3 letters bc diagonal
                       words[i].direction = 'd';
                       words[i].x = c+1;
                       words[i].y = r-j+1;
                       for (int x=0; x<words[i].length;x++){
                           board[r-j+x][c]=words[i].word[x];
                           
                        }
                        words[i].placed++;
                        }  
                         }
                        //if the word can fit HORIZONTALLY
                     else if (board[r][c+1]=='.' && board[r][c-1]=='.'
                        && board[r+1][c-1] =='.'&& board[r-1][c+1]=='.'
                        && board[r-1][c-1] =='.'&& board[r+1][c+1]=='.'
                        && c-j+1>0 && c-j+words[i].length-1<size){

                        //make sure no words already in that row, and check diagonal
                        int keeptrying = 0;
                        for (int x =0;x<words[i].length;x++){
                           if (board[r-1][c-j+x] != '.') keeptrying++;
                           if  (board[r+1][c-j+x] != '.') keeptrying++;
                           if  (board[r][c-j+x] !='.') keeptrying++;
                        }
                      //check beginning and end of word
                        hneighbors(board, words, i, r, c, j, &keeptrying);
                        if (keeptrying <4){ //can only have at most 3 neighboring letters
                        words[i].direction = 'a';
                        words[i].x = c-j+1;
                        words[i].y=r+1;
                        for (int x=0;x<words[i].length;x++){
                           board[r][c-j+x]=words[i].word[x];
                        }
                        words[i].placed++;
                        }
                     }
                     if (words[i].placed >0) break;
                 }
                 if (words[i].placed> 0) break;
             }
         }
      } 
   }
}


//function for erasing words
void eraseword(char pboard[][size], Word words[], char sboard[][size]){
   for (int i=0;i<size;i++){
      for (int j=0;j<size;j++){
         if (sboard[i][j] != '.'){
            pboard[i][j] = ' ';
         }
         else {
            continue;
         }
      }
   }
}

//function for displaying clues
void dispclues(Word words[], int wordcount, Clue clues[]){
   printf("CLUES:\n");
   printf("Location|  Direction\t| Anagram\n");
   for (int i=0;i<wordcount;i++){
      if (words[i].placed !=0){
         printf("%d,%d\t|", words[i].x,words[i].y);
         if (words[i].direction == 'd') printf("\tDown\t|");
         else if (words[i].direction == 'a') printf("\tAcross\t|");
         strcpy(clues[i].clue, strfry(words[i].word));
         printf("%s\n", clues[i].clue);
      }
   }
}

//function for printing clues to file
void cluestofile(FILE *fp2,Word words[], int wordcount, Clue clues[]){
   fprintf(fp2, "CLUES:\n");
   fprintf(fp2, "Location |  Direction| Anagram\n");
   for (int i=0;i<wordcount;i++){
      if (words[i].placed !=0){
         fprintf(fp2, "%d,%d\t\t|", words[i].x,words[i].y);
         if (words[i].direction == 'd') fprintf(fp2,"\tDown\t\t|");
         else if (words[i].direction == 'a') fprintf(fp2,"\tAcross\t|");
         strcpy(clues[i].clue, strfry(words[i].word));
         fprintf(fp2, "%s\n", clues[i].clue);
      }
   }
}

//function for displaying words you cannot place
void cantplace(Word words[], int wordcount){
   for (int i=0;i<wordcount;i++){
      if (words[i].placed == 0){
         printf("could not place %s\n", words[i].word);
      }
   }
   printf("\n");
}

//function for diplaying words you cannot place to file
void filecantplace(FILE *fp2, Word words[], int wordcount){
   for (int i=0;i<wordcount;i++){
      if (words[i].placed == 0){
         fprintf(fp2, "could not place %s\n", words[i].word);
      }
   }
   fprintf(fp2, "\n");
}

//EXTRACREDIT FUNCTION
void extracredit(char board [][size],Word words[], int wordcount){
   for (int i=1; i<wordcount;i++){           //loop thru all words that are not yet placed
      if (words[i].placed == 0){
      for (int j=0; j<words[i].length;j++){  //loop thru all letters 
          for (int r=0; r<size;r++){          //loop thru rows of board
              for (int c=0;c<size;c++){        //loop thru columns of board
                  if (words[i].word[j] == board[r][c]){  //check to see if match
                     //if the word can fit VERTICALLY
                     if (board[r-1][c] == '.' && board[r+1][c]== '.'
                        && board[r-1][c+1]=='.' && board[r+1][c-1]=='.'
                        && board[r-1][c-1] =='.' && board[r+1][c+1]=='.'
                        && r-j+1>0 && r-j+words[i].length-1<size){

                        //make sure no letters are already in the column
                        int keeptrying = 0;
                        
                       for (int x=0;x<words[i].length;x++){
                           if (board[r-j+x][c-1] != '.')keeptrying++;
                           if (board[r-j+x][c+1] !='.') keeptrying++;
                           if (board[r-j+x][c] !='.') keeptrying++;
                       }

                       //function that check beginning and end of word
                       vneighbors(board, words, i, r, c, j, &keeptrying);
                       //place word
                       if (keeptrying <4 ){
                       words[i].direction = 'd';
                       words[i].x = c+1;
                       words[i].y = r-j+1;
                       for (int x=0; x<words[i].length;x++){
                           board[r-j+x][c]=words[i].word[x];
                           
                        }
                        words[i].placed++;
                        }  
                         }
                        //if the word can fit HORIZONTALLY
                     else if (board[r][c+1]=='.' && board[r][c-1]=='.'
                        && board[r+1][c-1] =='.'&& board[r-1][c+1]=='.'
                        && board[r-1][c-1] =='.'&& board[r+1][c+1]=='.'
                        && c-j+1>0 && c-j+words[i].length-1<size){

                        //make sure no words already in that row
                        int keeptrying = 0;
                        for (int x =0;x<words[i].length;x++){
                           if (board[r-1][c-j+x] != '.') keeptrying++;
                           if  (board[r+1][c-j+x] != '.') keeptrying++;
                           if  (board[r][c-j+x] !='.') keeptrying++;
                        }
                      //check beginning and end of word
                        hneighbors(board, words, i, r, c, j, &keeptrying);
                        if (keeptrying <4){
                        words[i].direction = 'a';
                        words[i].x = c-j+1;
                        words[i].y=r+1;
                        for (int x=0;x<words[i].length;x++){
                           board[r][c-j+x]=words[i].word[x];
                        }
                        words[i].placed++;
                        }
                     }
                     if (words[i].placed >0) break;
                 }
                 if (words[i].placed> 0) break;
             }
         }
      } 
   }
   }
}
