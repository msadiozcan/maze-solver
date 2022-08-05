#include <stdio.h>
#include <stdlib.h>

char** maze;
int** visited;
int rows;
int cols;
int baslangic_r;
int baslangic_c;
int points=0;

struct stack{
	int top;
	int** array;
};
int size = 128;  // stack array'ini allocate etmek için kullanýlacak.
		
int count = 0;

void getMaze(char* file_name);
void printMaze();
void printVisited();
void allocate_init_visited();
void add_apples();
void calculate_points();
int dfs(struct stack *s,int row, int col);
int left(int row, int col);
int right(int row, int col);
int top(int row, int col);
int bottom(int row, int col);
int isFull(int sayi,struct stack *s);
int isEmpty(struct stack *s);
void push(struct stack *s, int item, int item_two, int sayi);
void pop(struct stack *s);
void printStack(struct stack *s);


int main(int argc, char *argv[]) {
	struct stack *yigin = (struct stack*)malloc(sizeof(struct stack));
	yigin->array = (int**)malloc(size*sizeof(int));
	int stackin=0;
	for(stackin=0;stackin<size;stackin++){
		yigin->array[stackin] = (int*)malloc(2*sizeof(int));
	}
	yigin->top = -1;
		
	getMaze("maze.txt");
	printf("Maze:\n");
	printMaze();
	printf("\n");
	allocate_init_visited();
	add_apples();
	printf("Visited matrix:\n");
	printVisited();
	sleep(2);
	printf("Maze after adding apples:\n");
	printMaze();
	printf("\n--------------------------------------\n");
	sleep(5);
	dfs(yigin,baslangic_r,baslangic_c);
	printf("--------------------------------------\nVisited matrix:\n");
	printVisited();
	printf("\n\nSolution:\n");
	printMaze();
	printf("\nTotal points: %d",points);
	return 0;
}

void getMaze(char* file_name){
	char c;
	char rows_c[3] = {'\0'};
	char cols_c[3] = {'\0'};
	int row = 0;
	int col = 0;
	int x=0;
	int i,j;
	
	FILE* fptr = fopen(file_name, "r");
	
	if(fptr){
		while((c = getc(fptr)) != EOF){
			if(c=='\n'){
				break;
			} 
			else if(c==','){
				x = 1;
			}
			else if(!x){
				rows_c[row] = c;
				row++;
			}
			else{
				cols_c[col] = c;
				col++;
			}
		}
	} else{
		printf("File not found!");
		return;
	}
	
	rows = atoi(rows_c);
	cols = atoi(cols_c);
	
	maze = malloc(rows * sizeof(char*));
	for (i = 0; i < rows; ++i){
		maze[i] = malloc(cols * sizeof(char*));
	}
	
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if ((c = getc(fptr)) == '\n') {
				c = getc(fptr);
			}
			maze[i][j] = c;
			if (c =='b') {
				baslangic_r = i;
				baslangic_c = j;
			}
		}
	}
	fclose(fptr);
	return;	
}

void printMaze()
{
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}	
	return;
}

void printVisited(){
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%d", visited[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	return;
}

void allocate_init_visited(){
	int i,j;
	visited = malloc(rows * sizeof(int*));
	for (i = 0; i < rows; i++){
		visited[i] = malloc(cols * sizeof(int*));
	}
	
	for (i = 0; i < rows; ++i) {
		for (j = 0; j < cols; ++j) {
			if (maze[i][j] == '+' || maze[i][j] == '-' || maze[i][j] == '|') {
				visited[i][j] = 1;					// 0 : Not visited
			} else if (maze[i][j] == 'c') {			// 1 : Wall
				visited[i][j] = 2;					// 2 : Ending point
			} else {								// 3 : Apple
				visited[i][j] = 0;  				// 4 : Visited
			}										// 5 : Visited but turned back
		}
	}
	
	return;
}

void add_apples(){
	int i,j=rows,x,y;
	if(rows>cols){
		j = cols;
	}
	srand(time(NULL));
	while(i<j){
		x = rand()%rows;
		y = rand()%cols;
		if(visited[x][y] == 0){
			maze[x][y] = 'O';
			visited[x][y] = 3;
			i++;
		}		
	}
	return;
}

int dfs(struct stack *s,int row, int col){
	Sleep(500);
	printMaze();
	printf("Current points : %d\n\n\n",points);
	int* current = &visited[row][col];
	char* currentmaze = &maze[row][col];
	int currentrow=row,currentcol=col;
	int nextrow=0,nextcol=0;
	int swap=0;
	
	if(left(currentrow,currentcol)==1){
		nextrow= currentrow;
		nextcol= currentcol-1;
		swap = 1;
	}
	if(right(currentrow,currentcol)==1){
		nextrow= currentrow;
		nextcol= currentcol+1;
		swap=1;
	}
	if(top(currentrow,currentcol)==1){
		nextrow= currentrow-1;
		nextcol= currentcol;
		swap=1;
	}
	if(bottom(currentrow,currentcol)==1){
		nextrow= currentrow+1;
		nextcol= currentcol;
		swap=1;
	}
	if(swap==0){
		if(*current==0 || *current==3){
			points-=5;
		}
	}

	if(*current == 2){
		return 1;
	}
	
	if(swap==0){
		*current = 5;
		*currentmaze = ' ';	
		if(left(currentrow,currentcol)==4){
			nextrow= currentrow;
			nextcol= currentcol-1;
		}
		if(right(currentrow,currentcol)==4){
			nextrow= currentrow;
			nextcol= currentcol+1;
		}
		if(top(currentrow,currentcol)==4){
			nextrow= currentrow-1;
			nextcol= currentcol;
		}
		if(bottom(currentrow,currentcol)==4){
			nextrow= currentrow+1;
			nextcol= currentcol;
		}	
	}
	else if(*current == 0 || *current==3){
		if(*current==3){
			points+= 10;
		}
		*current = 4;
		*currentmaze = '*';
		if(left(currentrow,currentcol)==1){
			push(s,currentrow,currentcol-1,size);
		}
		if(right(currentrow,currentcol)==1){
			push(s,currentrow,currentcol+1,size);
		}
		if(top(currentrow,currentcol)==1){
			push(s,currentrow-1,currentcol,size);
		}
		if(bottom(currentrow,currentcol)==1){
			push(s,currentrow+1,currentcol,size);
		}
		nextrow = s->array[s->top][0];
		nextcol = s->array[s->top][1];	
		pop(s);
	}

	
	dfs(s,nextrow,nextcol);
	return 0;
}

int left(int row, int col){
	if(visited[row][col-1]==0 || visited[row][col-1]==2 || visited[row][col-1]==3 ){
		return 1;
	}
	if(visited[row][col-1]==1 || visited[row][col-1]==5){
		return 0;
	}	
	if(visited[row][col-1]==4){
		return 4;
	}
}

int right(int row, int col){
	if(visited[row][col+1]==0 || visited[row][col+1]==2 || visited[row][col+1]==3 ){
		return 1;
	}
	if(visited[row][col+1]==1 || visited[row][col+1]==5){
		return 0;
	}	
	if(visited[row][col+1]==4){
		return 4;
	}
}

int top(int row, int col){
	if(visited[row-1][col]==0 || visited[row-1][col]==2 || visited[row-1][col]==3 ){
		return 1;
	}
	if(visited[row-1][col]==1 || visited[row-1][col]==5){
		return 0;
	}	
	if(visited[row-1][col]==4){
		return 4;
	}
}

int bottom(int row, int col){
	if(visited[row+1][col]==0 || visited[row+1][col]==2 || visited[row+1][col]==3 ){
		return 1;
	}
	if(visited[row+1][col]==1 || visited[row+1][col]==5){
		return 0;
	}	
	if(visited[row+1][col]==4){
		return 4;
	}
}


int isFull(int sayi,struct stack *s){
	if(s->top == sayi-1){
		return 1;
	}
	else
		return 0;
}

int isEmpty(struct stack *s){
	if(s->top == -1){
		return 1;
	}
	else
		return 0;
}

void push(struct stack *s, int item, int item_two, int size){
	if(isFull(size,s)){
		printf("Stack is full.");
		return;
	}
	else{
		s->top++;
		s->array[s->top][0] = item;
		s->array[s->top][1] = item_two;
	}
	count++;
	return;
}

void pop(struct stack *s){
	if(isEmpty(s)){
		printf("Stack is empty.");
		return;
	}
	else{
		s->top--;
	}
	count--;
	return;
}

void printStack(struct stack *s){
	int i;
	for(i=0;i<count;i++){
		printf("%d %d\n",s->array[i][0],s->array[i][1]);
	}
	return;
}

