#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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

int evaluate_board(char board[3][3]) {
    char player1 = 'X'; // Maximizer
    char player2 = 'O'; // Minimizer


    // --- 1. Check Win/Loss (+10 or -10) ---

    for (int i = 0; i < 3; i++) {
        // Check Rows
        // ... If player1 wins a row, return 10
        if(board[i][0] == player1 && board[i][1] == player1 && board[i][2] == player1){
            return 10;
        }
        // ... If player2 wins a row, return -10
        if(board[i][0] == player2 && board[i][1] == player2 && board[i][2] == player2){
            return -10;
        }
        // Check Columns
        // ... If player1 wins a column, return 10
        if(board[0][i] == player1 && board[1][i] == player1 && board[2][i] == player1){
            return 10;
        }
        // ... If player2 wins a column, return -10
        if(board[0][i] == player2 && board[1][i] == player2 && board[2][i] == player2){
            return -10;
        }
    }
    
    // Check Diagonals
    // ... If player1 wins a diagonal, return 10
    if((board[0][0] == player1 && board[1][1] == player1 && board[2][2] == player1)|| (board[0][2] == player1 && board[1][1] == player1 && board[2][0] == player1)){
        return 10;
    }
    // ... If player2 wins a diagonal, return -10
    if((board[0][0] == player2 && board[1][1] == player2 && board[2][2] == player2)|| (board[0][2] == player2 && board[1][1] == player2 && board[2][0] == player2)){
        return -10;
    }
    // --- 2. Check Draw (0) ---
    // Loop through the board to count empty_spots
    // ... If empty_spots is 0, return 0
    bool full = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                full = false;
                break; // Optimization: exit inner loop as soon as an empty spot is found
            }
        }
        if (!full) break; // Optimization: exit outer loop too
    }

    if (full) {
        return 0;
    }
    // --- 3. Game is Ongoing (-1) ---
    return -1; 
}

int minimax(char board[3][3], bool is_maximizer) {
    // 1. BASE CASE: If the position is a terminal state (win, loss, or draw), return the score.
    int score = evaluate_board(board);
    if (score != -1) { // -1 means game is not over
        return score;
    }
    // Inside the main minimax function:
    if (is_maximizer) {
        // 1. Initialize the best score (to the lowest possible value)
        int maximizer = -100000;
        // 2. Loop through all 9 cells (i, j)
        //    If the cell is empty ('-'):
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                        // 3. Make the move (board[i][j] = 'X')
                        board[i][j] = 'X';
                        // 4. Call minimax recursively for the other player
                        int current_score = minimax(board, false);
                        // 5. Update the best score found so far (HINT: Use the max() function concept)
                        if (current_score > maximizer){
                            maximizer = current_score;
                        }
                        // 6. Un-do the move (board[i][j] = '-')
                        board[i][j] = '-';
                    }
                }
            }
        // Outside the loops, but inside the if (is_maximizer) block:
        // 7. Return the final best score.
        return maximizer;
            
    }else { // This is the Minimizer's turn (is_maximizer == false)
        // 1. Initialize the worst score (to the highest possible value)
        int minimizer = 100000;
        // 2. Loop through all empty cells (i, j)
        //    If the cell is empty ('-'):
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    // 3. Make the move using the Minimizer's symbol
                    board[i][j] = 'O';
                    // 4. Call minimax recursively for the Maximizer (is_maximizer = true)
                    int current_score = minimax(board, true);
                     // 5. Update the best (lowest) score found so far
                    if (current_score < minimizer){
                        minimizer = current_score;
                    }
                    // 6. Un-do the move
                    board[i][j] = '-';
                }
            }
        }
        // 7. Return the final best (lowest) score.
        return minimizer;
    }
}

void find_best_move(int bestMove[2]){
    int bestscore = 100000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                board[i][j] = 'O';
                int curentScore = minimax(board, true);
                if( curentScore < bestscore){
                    bestscore = curentScore;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
                board[i][j] = '-';
            }
        }
    }
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
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

int ifWon(char currentPlayer){
    for(int i=0;i<3;i++){
        // check rows
        if(board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer){
            printf("Player %c won the game\n",currentPlayer);
            return 1;
        }
        // check coloumns
        if(board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer){
            printf("Player %c won the game\n",currentPlayer);
            return 1;
        }
    }
    // check diagonals
    if((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)|| (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)){
        printf("Player %c won the game\n",currentPlayer);
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
            printf("Current player : %c\n\n", currentPlayer);
        }
        else{
            currentPlayer = player2;
            // 1. Declare the move array:
            int moveArray[2];
            // 2. Call the AI function to find the best move:
            find_best_move(moveArray);
            
            printf("AI is thinking");
            for (int i = 0; i < 3; i++) {
                sleep(1);
                printf(".");
            }
            // 3. Execute the move using the coordinates found:
            play(player2, moveArray[0], moveArray[1]);
        }

        int RowCol[2];
        int valid = 0;
        if(currentPlayer == player1){
            do
            {
                getPosition(RowCol);
                valid = play(currentPlayer,RowCol[0],RowCol[1]);
    
            } while (!valid);
        }
        
        displayBoard();

        if(ifWon(currentPlayer)){
            return 0;
        }
    }
    printf("Draw!!!\n");

    return 0;
}