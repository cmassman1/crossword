//crossfunc.h
//name: katie massman
//assignment: lab 8, header file
#define size 15
#define wordsize 16
#define max 20

typedef struct {
   char word[wordsize]; //maximum of 15 letters, 1 for null character
   int length;
   int x;
   int y;
   char direction;
   int placed;
} Word;

typedef struct{
  char clue[wordsize];
} Clue;

void hneighbors(char board[][size],Word words[],int i, int r, int c,int j, int *keeptrying);
void vneighbors(char board[][size], Word words[], int i, int r, int c, int j, int *keeptrying);
int readin(FILE*fp, Word words[]);
void makeclues(Word words[], int wordcount);
int ifalpha(char inputword[]);
void sortwords(Word words[], int wordcount);
void sinitialize(char board[][size]);
void pinitialize(char board[][size]);
void temptofile(FILE*fp2,char board[][size]);
void temp(char board[][size]);
void placeword(char board[][size],Word words[]);
void placewords(char board[][size],int wordcount, Word words[]);
void eraseword(char tboard[][size],Word words[], char sboard[][size]);
void dispclues(Word words[], int wordcount, Clue clues[]);
void cluestofile(FILE *fp2, Word words[],int wordcount, Clue clues[]);
void cantplace(Word words[], int wordcount);
void filecantplace(FILE *fp2, Word words[], int wordcount);
void extracredit(char board[][size], Word words[], int wordcount);
