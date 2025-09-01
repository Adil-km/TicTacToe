#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif  

char board[3][3] ={
                    {'-','-','-'},
                    {'-','-','-'},
                    {'-','-','-'}
                };

int playCount = 0;
void displayBoard(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf(" %c ",board[i][j]);
        }
        printf("\n");
    }
}

int play(char symbol,int row, int col){
    system(CLEAR);
    if(board[row][col] == '-'){
        board[row][col] = symbol;
        playCount++;
        return 1;
    }else{
        displayBoard();
        printf("Board position already marked\n");
        return 0;
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
void getPosition(int pos[]) {
    char ch;
    while (1) {
        printf("Choose row position (1, 2, or 3): ");
        if (scanf("%d", &pos[0]) == 1) {
            pos[0] -= 1;
        } else {
            printf("Invalid input. Please enter a number.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); // clearing buffer
            continue;
        }

        // clear buffer in case of extra input on the same line
        while ((ch = getchar()) != '\n' && ch != EOF);

        printf("Choose column position (1, 2, or 3): ");
        if (scanf("%d", &pos[1]) == 1) {
            pos[1] -= 1;
        } else {
            printf("Invalid input. Please enter a number.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); // clearing buffer
            continue;
        }

        // clear buffer in case of extra input on the same line
        while ((ch = getchar()) != '\n' && ch != EOF);

        if (pos[0] < 0 || pos[0] >= 3 || pos[1] < 0 || pos[1] >= 3) {
            printf("Out of board position\n");
        } else {
            break; //exit loop if no errors
        }
    }
}

int main(){
    system(CLEAR);
    char player1 = 'X', player2 = 'O';
    char currentPlayer;
    displayBoard();
    while(playCount!=9){
        if(playCount%2 == 0){
            currentPlayer = player1;
        }
        else{
            currentPlayer = player2;
        }
        printf("Current player : %c\n\n", currentPlayer);

        int RowCol[2];
        int valid = 0;
        do
        {
            getPosition(RowCol);
            valid = play(currentPlayer,RowCol[0],RowCol[1]);

        } while (!valid);
        
        displayBoard();

        if(ifWon()){
            return 0;
        }
    }
    printf("Draw!!!\n");

    return 0;
}