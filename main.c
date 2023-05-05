#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   

typedef struct {
    char name[50];
    int score;
    int num_plays;
} Score;
Score scores[100];

int i,j,p,q,z,k=0,r,e=0,counter,del,pass,gen,points,hintmat[9][9],copy1,copy2,ques[9][9]
,check,ctr1,ctr2,hint,cl,ctr=0,l=0,c,o,d,b,value,a[9][9],m[50],v[50],w[50],n[50],org[9][9]
,finalctr=0,choice,multiplier,colour,level,option,helpexit=0,blank,store,hintcount,t,u;

char name[100], line[100];

float time1; 

void generator(void);
void scorecard(void);
void timedelay(void);
void play(void);
void print(void);
void help(void);
void sudoku(void);
void game(void);

void setScore(){ //this function made for test score error
  int score_input;
  printf("Enter your score: ");
  scanf("%d", &score_input);
  printf("Enter the multiplier: ");
  scanf("%d", &multiplier);
  printf("Enter the pass score: ");
  scanf("%d", &pass);
  points += score_input * multiplier;
  printf("Your updated score is %d.\n", points);
  printf("Your pass score is %d.\n", pass);}

void print() {//this function made for print sudoku grid on terminal
  printf("COL-->| 0 1 2 | 3 4 5 | 6 7 8 |");
  printf ("\n-------------------------------\n");
  for(p=0;p<9;p++){ 
    printf("ROW %d | ",p);
		for(q=0;q<9;q++){
       if(q==3||q==6){
       printf("| ");}
      if(a[p][q]!=0){
        printf("%d ",a[p][q]);}
      else{
        printf("_ ");}}
    printf("|");
    if(p==2||p==5){
       printf("\n-------------------------------");}
    printf("\n");}
  printf("-------------------------------\n");}

void sudoku(){ //this function made for check all can't be same numbers in row col and 3x3 for 
  for (k=0;k<i;k++){ 
  if(i==0){
    break;}
  if(a[k][j]==a[i][j]){
   a [i][j]=(rand()%9)+1;
   ctr++;
   if(ctr==100){
   ctr=0;
   for(j=0;j<9;j++)
   a[i][j]=0;
   j=0;
   a[i][j]=(rand()%9)+1;
   sudoku(); }
  sudoku();}}
for (l=0;l<j;l++){
  if(j==0){
  break;}
 if(a[i][j]==a[i][l]){
  a [i][j]=(rand()%9)+1;
  sudoku();}}
o=0;
for (c=0;c<=6;c+=3)
{if(i>=c&&i<(c+3)){
  r=c;
  break;}}
for(d=0;d<=6;d+=3){
 if (j>=d&&j<(d+3)){
  cl=d;
  break;}}
for (r=c;r<(c+3);r++){
 for(cl=d;cl<(d+3);cl++){
   if(cl==j&&r==i){
      o=1;
      break;}
 if(a[r][cl]==a[i][j]){
  a[i][j]=(rand()%9)+1;
  sudoku();}}
 if(o==1)
    break;}}

void dighole(){ //this function made for make space on sudoku grid
  for(z=0;z<blank;z++){
  e=0;
  i=rand()%9;
  m[z]=i;
  j=rand()%9;;
  n[z]=j;
  if(z!=0){	
    for(l=2;l<z;l++){
    if(i==m[l]&&j==n[l]){
      z=z-1; 
      e=1;
      break;}}}
  if(e!=1)
  a[i][j]=0;}
  for(copy1=0;copy1<9;copy1++){
  for(copy2=0;copy2<9;copy2++){
  ques[copy1][copy2]=a[copy1][copy2];}}}

void help(){ //this function made for option how to play
  system("cls");
  printf("\t**RULES AND INSTRUCTIONS***\n");
  printf("Hi %s, welcome to sudoku help. Even if you are completely new to sudoku, you can learn it from the beginning here.\n",name);
  printf("Sudoku is a game of numbers which will test your intelligence. Basically,it consists of a 9x9 grid.");
  printf("The grid will have certain numbers which are already given and serve as clues to the player.You have to fill the grid");
  printf("with every row and column consisting of numbers from 1 to 9.Every 3x3 block must also consist of numbers from 1 to 9.\n");
  printf("So, %s, you will have to complete the entire 9x9 grid of 81 numbers without violating these rules.",name);
  printf("And %s,you will have to look into the locations and give the location of the cell you want to enter the number into.",name);
  printf("For example, 0 2 or 3 4 etc.\n");
  printf("There will be 5 levels of difficulty.\n");
  printf("In the beginner mode 1 point.\n");
  printf("In the easy mode,2 points.\nin the medium mode 3 points.\n");
  printf(",in the difficult mode 4 points.\n"); 
  printf("in the professional mode 5 points .\nfor each correct answer");
  printf("That's all are the rules for playing this simple game. Enjoy playing sudoku, i will guarantee you that you will have a great time playing sudoku here.\n");
  printf("Enter a character to see a sample sudoku\n");
  getch();
  system("cls");
  printf("HERE IS A SAMPLE SUDOKU FILLED GRID\n");
  print();
  printf("Enter a character to continue once you have seen the grid and return to previous menu.\n");
  getch();
  system("cls");
  helpexit=1;}

void saveToFile(char* name, int score){ //this function made for save name and score to file
  FILE* file;
  file = fopen("scores.txt", "a");
     if (file == NULL) {
        printf("Error opening file!\n");
        return;}
  fprintf(file, "%s ", name);
  fprintf(file, "%d", score);
  fprintf(file, "\n");
  fclose(file);}


void ranking() {
    int num_scores = 0;
    FILE* file = fopen("scores.txt", "r");
    if (file == NULL) {
        printf("Error: could not open file\n");
        return;}
    while (fgets(line, sizeof(line), file)) {
        char* name = strtok(line, " ");
        int score = atoi(strtok(NULL, " "));
        // Check if the user already exists in the scores array
        int user_index = -1;
        for (int i = 0; i < num_scores; i++) {
            if (strcmp(scores[i].name, name) == 0) {
                user_index = i;
                break;}}
        if (user_index != -1) {
            scores[user_index].score += score;
            scores[user_index].num_plays++;} 
        else {
            strcpy(scores[num_scores].name, name);
            scores[num_scores].score = score;
            scores[num_scores].num_plays = 1;
            num_scores++;}}
    fclose(file);
    for (int i = 0; i < num_scores - 1; i++) {
        for (int j = i + 1; j < num_scores; j++) {
            if (scores[i].score < scores[j].score) {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;}}}
    system("cls");
    printf("|Rank   Name     Score    Plays|\n");
    printf("|==============================|\n");
    for (int i = 0; i < num_scores; i++) {
        printf(" %-6d %-9s %d        %d\n", i+1, scores[i].name, scores[i].score, scores[i].num_plays);}
    printf("|==============================|\n");
    printf("Enter a character to return previous menu.\n");
    getch();
    system("cls");
    helpexit=1; }

void game() {//main function for game, option, level
  system("cls");
  if(helpexit!=1){
     printf("Enter your name here..\n");
     gets(name);}
  do{
	for(t=0;t<9;t++)
 	{
	 for(u=0;u<9;u++)
	{
		hintmat[t][u]=0;
	}
	}
	hintcount=0;
	generator();
  system("cls");
	printf("*** Welcome to SUDOKU Games ***\n");
	printf("*** MENU ***\n");
	printf("1. PLAY SUDOKU\n");
	printf("2. LEARN TO PLAY SUDOKU\n");
  printf("3. SCORE BOARD\n");
	printf("4. EXIT\n");
	printf("Please enter number of menu.\n");
	scanf("%d",&choice);
	switch(choice){
	case 1: system("cls"); 
    printf("*** Select Level ***\n");
		printf("1. BEGINNER\n");
		printf("2. EASY\n");
		printf("3. MEDIUM\n");
		printf("4. DIFFICULT\n");
		printf("5. PROFESSIONAL\n");
		printf("Please enter number of level or 0 to back. %s \n",name);
		scanf("%d",&level);
		switch(level){ 
      case 0:system("cls");
        helpexit=1;  
        break;
			case 1: blank=5;
				dighole();
				timedelay();
				play();
				scorecard();
        saveToFile(name, points);
				break;
			case 2: blank=20;
				dighole();
				timedelay();
				play();
				scorecard();
        saveToFile(name, points);
				break;
			case 3: blank=30;
				dighole();
				timedelay();
				play();
				scorecard();
        saveToFile(name, points);
				break;
			case 4: blank=80;
				dighole();
				timedelay();
				play();
				scorecard();
        saveToFile(name, points);
				break;
			case 5: blank=50;
				dighole();
				timedelay();
				play();
				scorecard();
        saveToFile(name, points);
				break;
      case 6: blank=1;
				printf("*** Select option ***\n");
        printf("1. BABY LEVEL\n");
        printf("2. Test Set Score\n");
		    printf("Please enter number of option or 0 to back. %s \n",name);
		    scanf("%d",&option);
        switch (option){
        case 0:system("cls");
          helpexit=1;  
          break;
        case 1: blank=1;
				  dighole();
				  timedelay();
				  play();
				  scorecard();
          saveToFile(name, points);
          break;
        case 2: 
          setScore();
          scorecard();        
          saveToFile(name, points);
        default:printf("Please select the proper option. You will be redirected to previous menu\n");
          break;}
				break;
			default:printf("Please select the proper level of difficulty. You will be redirected to previous menu\n");
			  break;}
		  break;
		case 2: help();
			break;
    case 3: ranking();
      break;
		case 4: printf("THANK YOU FOR PLAYING %s\n",name);
			getch();
			exit(0);
	  default:printf("Please select the proper number.\n");
			break;}}while(choice!=4);}

void generator(){ //this function made for generate all numbers for sudoku puzzle
 for(i=0;i<9;i++){
  for(j=0;j<9;j++){
    a[i][j]=0;}}
 for(i=0;i<9;i++){
  for(j=0;j<9;j++){
	b=rand();
	value=(b%9)+1;
	a[i][j]=value;
	if ((i==j)&&(i==0))
	 {if ((k==l)&&(k==0)){
	    continue;}}
    else{
	    sudoku();}}}
 for(i=0;i<9;i++){
  for(j=0;j<9;j++){
    org[i][j]=a[i][j]; }}}

void play(){ //this function made for play terminal
  print();
  while(1){
  gen=0;
  hint=-1;
  printf("%s, Enter position of cell(row column) or Enter 10 10 to summit \n",name);
  scanf("%d%d",&i,&j);
  if(i<=8&&j<=8){
  if(ques[i][j]!=0){
    gen=1;
    printf("This is a generated number. You cannot change it.Enter a character to continue.\n",name);
    getch();
    system("cls");
    print();}
  if(gen!=1){
  if(hintmat[i][j]!=0){
    printf("You have taken a hint for this number.Do not try to change it .Enter a character to continue.\n",name);
    getch();
    system("cls");
    print();
    continue;}
  v[counter]=i;
  w[counter]=j;
  counter++;
  printf("If you want a hint,type 0 otherwise type 1\n");
  scanf("%d",&hint);
  if(hint==0){
   hintcount++;
   a[i][j]=org[i][j];
   hintmat[i][j]=a[i][j];
   system("cls");
   print();}
  else if(hint==1){
   printf("Enter a number from 1-9 or enter 0 to erase.\n");
   scanf("%d",&store);
   if(store==0&&hintmat[i][j]==0){ 
    a[i][j]=0;
    system("cls");
    print();
    continue;}
  if(store>=1&&store<=9){
   a[i][j]=store;
   if(store==org[i][j]){
     points++;}
  system("cls");
  print();}
 else{ 
  printf("**********Enter a valid number %s**********\n",name);
  printf("Enter any character to continue.If you have any doubts,refer help.\n");
  getch();
  system("cls");
  print();}}}}
  else{
    if(i==10&&j==10)
      break;
    else{
     printf("INVALID ELEMENT LOCATION ENTERED!\n");
     system("cls");
     print();}}}
printf("Thank you for playing %s ",name);}

void timedelay(){ //this function made for generate time in terminal
	for(del=1,l=0;del<=25;del++)
	{system("cls");
	printf("This might take a while.Please do not exit!\n");
	printf("GENERATING THE SUDOKU AS PER YOUR REQUIREMENTS.   ");
	printf(" %d%% Complete",++l);
	for(time1=0;time1<250000;time1++);
	system("cls");
	printf("This might take a while.Please do not exit!\n");
	printf("GENERATING THE SUDOKU AS PER YOUR REQUIREMENTS..  ");
	printf(" %d%% Complete",++l);
	for(time1=0;time1<250000;time1++);
	system("cls");
	printf("This might take a while.Please do not exit!\n");
	printf("GENERATING THE SUDOKU AS PER YOUR REQUIREMENTS... ");
	printf(" %d%% Complete",++l);
	for(time1=0;time1<250000;time1++);
	system("cls");
	printf("This might take a while.Please do not exit!\n");
	printf("GENERATING THE SUDOKU AS PER YOUR REQUIREMENTS....");
	printf(" %d%% Complete\n",++l);
	for(time1=0;time1<250000;time1++);}}

void scorecard(){ //this function made for score board in final
  system("cls");
  if(points==blank) printf("THAT'S GREAT!!..You solved the entire sudoku correctly..You played really well %s\n",name);
  if(level==2)points*=2;
  else if(level==3)points*=3;
  else if(level==4)points*=4;
  else if(level==5)points*=5;
printf("Please wait while your scorecard is being generated...\n");
for(time1=0;time1<5000000;time1++);
printf("\n--------------------------------------------------\n");
printf("NAME OF THE PLAYER: %s \n",name);
if(level==1){ 
  printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: BEGINNER \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 5\n");
  printf("Number of blanks you filled correctly : %d\n",points);
  if(points>3)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(level==2){
  printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: EASY \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 20\n");
  printf("Number of blanks you filled correctly : %d\n",(points)/2);
  if(points>36)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(level==3){
  printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: MEDIUM \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 30\n");
  printf("Number of blanks you filled correctly : %d\n",(points)/3);
  if(points>85)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(level==4)
 {printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: DIFFICULT \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 40\n");
  printf("Number of blanks you filled correctly : %d\n",(points)/4);
  if(points>100)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(level==5){
  printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: PROFESSIONAL \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 50\n");
  printf("Number of blanks you filled correctly : %d\n",(points)/5);
  if(points>110)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(option==1){
  printf("LEVEL OF DIFFICULTY CHOSEN FOR SUDOKU GAME: BABY \n");
  printf("Number of blanks you were supposed to fill to complete the sudoku puzzle: 1\n");
  printf("Number of blanks you filled correctly : %d\n",points);
  if(points>0)printf("YOU PLAYED REALLY WELL %s\n",name);}
else if(option==2){
  printf("THIS IS SCORE TEST \n");
  printf("You points is: %d\n",(points/multiplier));
  printf("You scored is: %d\n",points);
  if(points>pass)printf("YOU PLAYED REALLY WELL (More than pass score.)%s\n",name);}
printf("POINTS SCORED: %d\n",points);
if(points>0)
printf("----------------------------------------------------\n");
printf("Enter a character\n");
getch();
system("cls");
printf("YOUR SUDOKU\n");
print();
for(time1=0;time1<10000000;time1++);
printf("SOLVED SUDOKU\n");
for(ctr1=0;ctr1<9;ctr1++){
 for(ctr2=0;ctr2<9;ctr2++){
	a[ctr1][ctr2]=org[ctr1][ctr2];}}}

int main(){
  srand(time(NULL));
  system("cls");
  generator();
  game();
  return 0;}
