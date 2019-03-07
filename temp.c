#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swapPlayer(currentPlayer) ((currentPlayer=='R')?'B':'R')
#define charToNum(letter) (letter=='R')?1:(letter=='B')?2:0

int dim;
int maxProfiles=10;

void PrintBoard(char board[dim][dim]) {
for(int l=dim-1; l>=0; l--){
	for( int r=0; r<dim; r++){
		printf("%c ", board[l][r]);
    }
	printf("\n");
    }
}

int ColHeight(char board[dim][dim], int col){
int x=0;
for(; (x<dim)&&(board[x][col]!=' '); x++);
return x;
}

int checkForFull(char board[dim][dim]){
for(int i=0; i<dim;i++){
if(ColHeight(board, i)!=dim) return 0;
}
return 1;
}

int checkForWiner(char board[dim][dim]){
int winner=0;
for(int i=0; i<dim; i++){
for(int j=0; j<dim; j++){
if((j+3<dim)&&(board[i][j]==board[i][j+1])&&(board[i][j]==board[i][j+2])&&(board[i][j]==board[i][j+3]))winner=charToNum(board[i][j]);
else if((i+3<dim)&&(board[i][j]==board[i+1][j])&&(board[i][j]==board[i+2][j])&&(board[i][j]==board[i+3][j]))winner=charToNum(board[i][j]);
else if((j+3<dim)&&(i+3<dim)&&(board[i][j]==board[i+1][j+1])&&(board[i][j]==board[i+2][j+2])&&(board[i][j]==board[i+3][j+3]))winner=charToNum(board[i][j]);
else if((i+3<dim)&&(j+3<dim)&&(board[i][j+3]==board[i+1][j+2])&&(board[i][j+3]==board[i+2][j+1])&&(board[i][j+3]==board[i+3][j]))winner=charToNum(board[i][j+3]);
if(winner!=0) return winner;
}
}
if(checkForFull(board)==1) return -1;
return winner;
}

int whichProfile(char profileNames[maxProfiles][10], int numCreated, char name[10]){
for(int i=0; i<numCreated; i++){
if(strcmp(profileNames[i], name)==0) return i;
}
return -1;
}

int totalGames(char profileNames[maxProfiles][10], int profileData[10][3], int numCreated, char name[10]){
    int x=whichProfile(profileNames, numCreated, name);
    if(x==-1) return -1;
    return profileData[x][0]+profileData[x][1]+profileData[x][2];
}

int AIMove(char board[dim][dim]){
return 0;
}

int main(void){
dim=1;
char again[1];
char profileNames[maxProfiles][10];
int profileData[maxProfiles][3];
int col=1, playerNum=0, numCreated=0; p1W=0, p2W=0, gameNum=0;
char name1[10], name2[10]="Computer", type[10];
for(int i=0; i<maxProfiles; i++){
for(int j=0; j<3; j++){
profileData[i][j]=0;
}
}
//name2="Computer";
char userID='R';
do{
printf("Enter the size of the board:  \n *Board size must be greater than 3* \n *Board sizes over 40 may cause display issues*\n");
scanf("%d", &dim);
if (dim < 4){
	return 0;
}
char board[dim][dim];
for(int i=0; i<dim; i++){
	for( int j=0; j<dim; j++){
		board[i][j]= ' ';
    }
}
printf("Enter User name less than ten Characters in length:\n");
scanf("%s", name1);
do{
 printf("Playing against Computer or Player?\n");
scanf("%s", type);
printf("%s\n", type);
if(strcmp(type, "Computer")==0){
playerNum=1;
}
else if(strcmp(type, "Player")==0){
playerNum=2;
printf("Enter player 2 name:\n");
scanf("%s", name2);
}
}
while (strcmp(type, "Computer")!=0 && strcmp(type, "Player")!=0);
//printf("Invalid input: try again.\n"));

int up;
PrintBoard(board);
char currentPlayer='R';
while(checkForWiner(board)==0){
 if(currentPlayer=='R'){
	printf("%s\n", name1);
}
else{
	printf("%s\n", name2);
}
do{

    printf("Make a move by entering the column number you would like to drop a tile in.\n");
    scanf("%d", &col);
	up=((col>=0)&&(col<dim))?ColHeight(board, col):dim;
}
while (up==dim);

    board[up][col]=currentPlayer;
currentPlayer=swapPlayer(currentPlayer);
PrintBoard(board);

}
if(checkForWiner(board)==1){
    printf("%s Wins!\n", name1);
    if(whichProfile(profileNames, numCreated, name1)==-1){
        profileNames[numCreated]=name1;
        profileData[numCreated][0]++;
        numCreated++;
    }
    else{
        profileData[whichProfile(profileNames, numCreated, name1)][0]++;
    }
    if(playerNum==2){
        if(whichProfile(profileNames, numCreated, name2)==-1){
            profileNames[numCreated]=name2;
            profileData[numCreated][1]++;
            numCreated++;
        }
        else{
            profileData[whichProfile(profileNames, numCreated, name2)][1]++;
        }
    }
    printf("%s's record is %d out of %d!\n", name1, profileData[whichProfile(profileNames, numCreated, name1)][0], totalGames(profileNames, profileData, numCreated, name1);
}
else if(checkForWiner(board)==2){
printf("%s Wins!\n", name2);
if(playerNum==2){
if(whichProfile(profileNames, numCreated, name2)==-1){
profileNames[numCreated]=name2;
profileData[numCreated][0]++;
numCreated++;
}
else{
profileData[whichProfile(profileNames, numCreated, name2)][0]++;
}
}
if(whichProfile(profileNames, numCreated, name1)==-1){
profileNames[numCreated]=name1;
profileData[numCreated][1]++;
numCreated++;
}
else{
profileData[whichProfile(profileNames, numCreated, name1)][1]++;
}
printf("%s's record is %d out of %d!\n", name2, profileData[whichProfile(profileNames, numCreated, name2)][0], totalGames(profileNames, profileData, numCreated, name2);
}
else if(checkForWiner(board)==-1){
    printf("No one wins!\n");
    if(whichProfile(profileNames, numCreated, name1)==-1){
        profileNames[numCreated]=name1;
        profileData[numCreated][2]++;
        numCreated++;
    }
    else{
        profileData[whichProfile(profileNames, numCreated, name1)][2]++;
    }
    if(playerNum==2){
        if(whichProfile(profileNames, numCreated, name2)==-1){
            profileNames[numCreated]=name2;
            profileData[numCreated][2]++;
            numCreated++;
        }
        else{
            profileData[whichProfile(profileNames, numCreated, name2)][2]++;
        }
    }
}

printf("Play Again? y/n\n");
scanf("%s", again);
do{
if(strcmp(again,"y")){
printf("Run again");
gameNum++;
}
else if(strcmp(again,"n")) return 0;
}
while(strcmp(again, "y")!=0 && strcmp(again,"n")!=0);
}
while(strcmp(again,"y")!=0);
return 0;
}

