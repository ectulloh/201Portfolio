#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define swapPlayer(currentPlayer) ((currentPlayer=='R')?'B':'R')
#define charToNum(letter) (letter=='R')?1:(letter=='B')?2:0

int dim;
int maxProfiles=10;         //Max number of profiles was set to 10 as a basis. It could be expanded.

void PrintBoard(char board[dim][dim]) {    //Print board does what it says on the tin, it prints the board into the command line
    for(int l=dim-1; l>=0; l--){
        for( int r=0; r<dim; r++){
            printf("%c ", board[l][r]);
        }
        printf("\n");
    }
}

int ColHeight(char board[dim][dim], int col){       //This one calculates the height of a given column, to check if they are full
    int x=0;
    for(; (x<dim)&&(board[x][col]!=' '); x++);
    return x;
}

int checkForFull(char board[dim][dim]){             //This checks the whole array to see if the board is full
    for(int i=0; i<dim;i++){
        if(ColHeight(board, i)!=dim) return 0;
    }
    return 1;
}

int checkForWiner(char board[dim][dim]){            //This one sees if anyone has won the game if it has, it returns the int that goes with the winner. If the board has filled up, it sends the tie game flag.
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

int whichProfile(char profileNames[maxProfiles][10], int numCreated, char name[10]){    //This function returns which slot in the list of profiles a given username is, or returns that the name is not in the list.
    for(int i=0; i<numCreated; i++){
        if(strcmp(profileNames[i], name)==0) return i;
    }
    return -1;
}

int totalGames(char profileNames[maxProfiles][10], int profileData[10][3], int numCreated, char name[10]){    //This uses the recorded Win/Loss/Tie statics to determine the total number of games a user has played.
    int x=whichProfile(profileNames, numCreated, name);
    if(x==-1) return -1;
    return profileData[x][0]+profileData[x][1]+profileData[x][2];
}

typedef struct Node{            //This is the basis of the graph. It was going to be much more complex, but I simplified. Rather than create a graph of all of the spaces, I made one of the columns.
    /*Node West;
    Node East;
    Node North;
    Node South;
    Node SouthWest;
    Node SouthEast;
    Node NorthWest;
    Node NorthEast;
    */
    struct Node *next;
    struct Node *prev;
    int state;
}node;

int getNodeState(node *node_t){   //this function returns the state of the column.
	return node_t->state;
}

typedef struct Graph{ //Starts the graph
    int size;
    node *head;
    node *tail;
}graph;

int getGraphSize(graph *items){ //tells the size of the graph
	return items->size;
}

graph *newGraph() {    //builds new graph
    graph *items=malloc(sizeof(graph));
    items->head=NULL;
    items->tail=NULL;
    items->size=0;
    return items;
}

void insertGraph(graph *items, int value) {    //Adds items to the graph
    node *point=malloc(sizeof(node));
    point->state=value;
    point->next=NULL;
    if(items->size==0) {
        items->head=point;
        point->prev=NULL;
    }
    else{
        items->tail->next=point;
        point->prev=items->tail;
    }
    items->tail=point;
    items->size++;
}

void freeGraph(graph *dll){         //Frees the data used by graph
while(dll->head!=NULL){
	node *ptr=dll->head;
	dll->head=dll->head->next;
	free(ptr);
}
free(dll);
}

int depthFirstSearch(node *current, char board[dim][dim], bool used[dim]);  //allows the function to recurse

int depthFirstSearch(node *current, char board[dim][dim], bool used[dim]){  //searches the graph for the next best move
    int x=current->state;
    if(used[current->state]==false){
        used[current->state]=true;
        if(current->next!=NULL){
            int n=depthFirstSearch(current->next, board, used);         //Dives through the graph for the column heights
            x=ColHeight(board, x)<=ColHeight(board, n)?x:n;
        }
        if(current->prev!=NULL){
            int p=depthFirstSearch(current->prev, board, used);
            x=ColHeight(board, x)<=ColHeight(board, p)?x:p;
        }
    }
    return x;
}

int AIMove(char board[dim][dim]){ //"best move" is emptiest column AI isn't too bright, but it is persistent. It never gives up.
    graph *dll;
    dll=newGraph();
    bool used[dim];
    for(int i=0; i<dim; i++){
        insertGraph(dll, i);
        used[i]=false;
    }
    int x=depthFirstSearch(dll->head, board, used);
    freeGraph(dll);
    return x;
}

int main(void){
    dim=4;
    char again[1];
    char profileNames[maxProfiles][10];
    int profileData[maxProfiles][3];
    int col=1, playerNum=0, numCreated=0, p1W=0, p2W=0, gameNum=0;
    char name1[10], type[10];
    for(int i=0; i<maxProfiles; i++){
        for(int j=0; j<3; j++){
            profileData[i][j]=0;
        }
    }                                               //The basic initialization is a 4x4 game board playing against the computer.
    printf("Welcome to Connect 4: Ultimate Edition!\n");
    printf("All inputs must match exactly\n");
    char userID='R';
    do{
    char name2[10]="Computer";
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
    printf("Enter a User name less than ten Characters in length:\n");          //ten char to a userID is for space and since the array is only ten names long, provides plenty of uniqueness
    scanf("%s", name1);
    do{
    	printf("Are you playing against the Computer or another Player?\n");
    	scanf("%s", type);
    	printf("%s\n", type);
    	if(strcmp(type, "Computer")==0){
    		playerNum=1;
    	}
    	else if(strcmp(type, "Player")==0){
    		playerNum=2;
    		printf("Enter player 2 name:\n");               //Player 2 ID is also recorded for statistics
    		scanf("%s", name2);
    	}
    }
    while (strcmp(type, "Computer")!=0 && strcmp(type, "Player")!=0);
    printf("**Column count starts at 0**\n");
    int up;
    PrintBoard(board);
    char currentPlayer='R';
    while(checkForWiner(board)==0){
	if((currentPlayer=='B')&&(playerNum==1)){
		col=AIMove(board);
		up=ColHeight(board, col);
	}
	else{
    if(currentPlayer=='R'){
        printf("%s\n", name1);
    }
    else{
        printf("%s\n", name2);
    }
    do{
        do{
            printf("Make a move by entering the column number you would like to drop a tile in.\n");
            scanf("%d", &col);
            }
        while((col<0) || (col>= dim));
        up=((col>=0)&&(col<dim))?ColHeight(board, col):dim;
    }
    while (up==dim);
	}
        board[up][col]=currentPlayer;
    currentPlayer=swapPlayer(currentPlayer);
    PrintBoard(board);

    }
    if(checkForWiner(board)==1){
        printf("%s Wins!\n", name1);
        if(whichProfile(profileNames, numCreated, name1)==-1){
            strncpy( profileNames[numCreated], name1, 10);
            profileData[numCreated][0]++;
            numCreated++;
        }
        else{
            profileData[whichProfile(profileNames, numCreated, name1)][0]++;
        }
        if(playerNum==2){
            if(whichProfile(profileNames, numCreated, name2)==-1){
                strncpy( profileNames[numCreated], name2, 10);
                profileData[numCreated][1]++;
                numCreated++;
            }
            else{
                profileData[whichProfile(profileNames, numCreated, name2)][1]++;
            }
        }
        printf("%s's record is %d out of %d!\n", name1, profileData[whichProfile(profileNames, numCreated, name1)][0], totalGames(profileNames, profileData, numCreated, name1));
    }
    else if(checkForWiner(board)==2){
    printf("%s Wins!\n", name2);
    if(playerNum==2){
    if(whichProfile(profileNames, numCreated, name2)==-1){
    strncpy( profileNames[numCreated], name2, 10);
    //profileNames[numCreated]=name2;
    profileData[numCreated][0]++;
    numCreated++;
    }
    else{
    profileData[whichProfile(profileNames, numCreated, name2)][0]++;
    }
    }
    if(whichProfile(profileNames, numCreated, name1)==-1){
    strncpy( profileNames[numCreated], name1, 10);
    //profileNames[numCreated]=name1;
    profileData[numCreated][1]++;
    numCreated++;
    }
    else{
    profileData[whichProfile(profileNames, numCreated, name1)][1]++;
    }
    if(playerNum==2){
    printf("%s's record is %d out of %d!\n", name2, profileData[whichProfile(profileNames, numCreated, name2)][0], totalGames(profileNames, profileData, numCreated, name2));
    }
    }
    else if(checkForWiner(board)==-1){
        printf("No one wins!\n");
        if(whichProfile(profileNames, numCreated, name1)==-1){
            strncpy( profileNames[numCreated], name1, 10);
           // profileNames[numCreated]=name1;
            profileData[numCreated][2]++;
            numCreated++;
        }
        else{
            profileData[whichProfile(profileNames, numCreated, name1)][2]++;
        }
        if(playerNum==2){
            if(whichProfile(profileNames, numCreated, name2)==-1){
                strncpy( profileNames[numCreated], name2, 10);
                //profileNames[numCreated]=name2;
                profileData[numCreated][2]++;
                numCreated++;
            }
            else{
                profileData[whichProfile(profileNames, numCreated, name2)][2]++;
            }
        }
    }

    //printf("Play Again? y/n\n");
    //scanf("%s", again);
    //printf("%s\n", again);
    do{
    //if(strcmp(again,"y")==0){
    //printf("Run again");
    //gameNum++;
    printf("Play Again? y/n\n");
    scanf("%s", again);
    }
    //else if(strcmp(again,"n")) return 0;
    //}
    while(strcmp(again, "y")!=0 && strcmp(again,"n")!=0);
    }
    while(strcmp(again,"n")!=0);
    printf("Goodbye!\n");
        return 0;
}

