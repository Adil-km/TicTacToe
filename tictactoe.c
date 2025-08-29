#include <stdio.h>
#include <stdlib.h>
char board[3][3] ={
                    {'-','-','-'},
                    {'-','-','-'},
                    {'-','-','-'}
                };

int playCount = 0;
void displayBorad(){
    // system("cls");
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf(" %c ",board[i][j]);
        }
        printf("\n");
    }
}

void play(char symbol,int row, int col){
    if(board[row][col] == '-'){
        board[row][col] = symbol;
        playCount++;
    }else{
        printf("Board position already marked\n");
    }
}

int ifWon(){
    char player1 = 'X', player2 = 'O';
    for(int i=0;i<3;i++){
        
        // check rows
        if(board[i][0] == player1 && board[i][1] == player1 && board[i][2] == player1){
            printf("Player %c won the game\n",player1);
            return 1;
        }
        if(board[i][0] == player2 && board[i][1] == player2 && board[i][2] == player2){
            printf("Player %c won the game\n",player2);
            return 1;
        }
        // check coloumns
        if(board[0][i] == player1 && board[1][i] == player1 && board[2][i] == player1){
            printf("Player %c won the game\n",player1);
            return 1;
        }
        if(board[0][i] == player2 && board[1][i] == player2 && board[2][i] == player2){
            printf("Player %c won the game\n",player2);
            return 1;
        }
        
    }

    // check diagonals
    if((board[0][0] == player1 && board[1][1] == player1 && board[2][2] == player1)|| (board[0][2] == player1 && board[1][1] == player1 && board[2][0] == player1)){
        printf("Player %c won the game\n",player1);
        return 1;
    }
    if((board[0][0] == player2 && board[1][1] == player2 && board[2][2] == player2)|| (board[0][2] == player2 && board[1][1] == player2 && board[2][0] == player2)){
        printf("Player %c won the game\n",player2);
        return 1;
    }
    return 0;
}
void getPosition(int pos[]){
    while (1){
        printf("Choose row postion ( 0 or 1 or 2 )\n");
        scanf("%d",&pos[0]);
        printf("Choose column postion ( 0 or 1 or 2 )\n");
        scanf("%d",&pos[1]);
        if(pos[0] < 0 || pos[0] >= 3 || pos[1] < 0 || pos[1] >= 3){
            printf("Out of board position\n");
        }else{
            break;
        }
    }
}

int main(){
    char player1 = 'X', player2 = 'O';
    displayBorad();
    for(int i =0;playCount!=9;i++){
        int row,col;
        if(i%2==0){
            printf("Player One move ( X )\n");
            int RowCol[] = {-1,-1};
            getPosition(RowCol);
            play(player1,RowCol[0],RowCol[1]);
            displayBorad();
            if(ifWon()) return 0;
            
        }else{
            printf("Player Two move ( O )\n");
            int RowCol[] = {-1,-1};
            getPosition(RowCol);
            play(player2,RowCol[0],RowCol[1]);
            displayBorad();
            if(ifWon()) return 0;
        }
    }
    printf("Draw!!!\n");
    

    // printf("%d , %d", RowCol[0],RowCol[1]);


    return 0;
}