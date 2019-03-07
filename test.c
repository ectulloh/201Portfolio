#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void){
FILE *f =fopen("UserID.txt", "w");
if (f== NULL)
{
	printf("Error opening file!\n");
	return 0;
}

char  a[10], b[10], c[10], d[10], e[10], q;
int i=0, UserNum=0, listSpot=0, count=0, k=0, rt=0;
char userID[10][10] = {0};
for (int j=0; j<10; j++){
	for (int v=0; v<10; v++){
		fscanf(f, "%c",&q);
		printf("%c   ", q);
		userID[j][v]=q;
}
}
//fread(userID, sizeof(userID),1, f);
for (int num=0; num<10; num++){
	if(userID[num][0]!=0){
		UserNum++;
	} }
//UserNum=size_t;

//strcpy(userID[0], "Ectull");
//UserNum++;
printf("Welcome to Connnect 4: Ultimate Edition!\n");
printf("Enter 'Quit' at any time to exit\n");
printf("Choose a Profile:\n");
while(i < UserNum){
printf("%s\n", userID[i]);
i++;
}
printf("Or create a Profile by entering: Create\n");
scanf("%s", b);
//IDchk(f,UserID[0])=listSpot;
//do{
//printf("Error: Invalid Input. Try Again:\n");
//scanf("%s",b);
//}
//printf("Error\n");
//while (rt!=1);{
//if(strcmp(b, "Create")==0){
//rt=1; }
//else{
for (int plo=0; plo<UserNum; plo++) {
if (strcmp(b, userID[plo])==0){
printf("User Found\n");
rt=1;
}
}
//}
if(strcmp(b, "Quit")==0){
printf("Error\n");
return 0;
}
//while (rt!=1){
if(count>0){
printf("Error\n");
printf("Error: Invalid Input. Try Again:\n");
scanf("%s",b);
}
count++;
//}
//strcmp(b, "Create")&& IDchk(b, UserID[UserNum])!=0){
//for(k=1; k<UserNum; k++){
//IDchk(b, UserID[k])=listSpot;
//}
//printf("Invalid Input: please try again\n");
//scanf("%s", b);
//}
//}
//}
if(strcmp(b, "Create")==0){
printf("Enter a userID for profile less than 10 characters in length\n");
//fgets(userID[UserNum], 10, stdin);
scanf("%s", c);
strcpy(userID[UserNum], c);
UserNum++;
}
for (k=0; k<UserNum; k++){
fprintf(f,"%s\n", userID[k]); 
}
printf("%s\n", userID[UserNum-1]);
//else if(strcmp(b, a[i])==0){
//USe profile selected
//}
//printf("Test a.0");
fclose(f);
return 0;
}
