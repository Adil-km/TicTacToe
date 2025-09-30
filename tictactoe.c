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

void menu();
void playTicTacToe();
void displayBoard();
int input(int from, int to);
int play(char symbol, int row, int col);
int ifWon(char currentPlayer);
void getPosition(int pos[]);

//Minimax Functions
int evaluate_board(char board[3][3]);
int minimax(char board[3][3], bool is_maximizer);
void find_best_move(int bestMove[2]);

/**
 * @brief Reads and validates user input for a range, and handles 'm' (menu) or 'q' (quit) commands.
 * @param from The minimum valid integer value (inclusive).
 * @param to The maximum valid integer value (inclusive).
 * @return The valid integer input, or -1 for the 'm' (menu) command.
 */
int input(int from, int to) {
    int a;
    int input_char;
    while(1) {
        // Read a single character
        input_char = getchar();
        // --- Input Buffer Clearing ---
        if (input_char != '\n' && input_char != EOF) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if (input_char == 'q') {
            printf("Program quiting...\n");
            exit(0); 
        }
        else if (input_char == 'm') {
            return -1;
        }
        // Convert character ('1', '2', '3') to integer (1, 2, 3)
        a = input_char - '0';
        if (a >= from && a <= to) {
            return a;
        } else {
            printf("Invalid input. (Must be '%d - %d', 'm', or 'q').\n", from, to);
            continue;
        }
    }
}

/**
 * @brief Displays the current state of the Tic-Tac-Toe board.
 */
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

/**
 * @brief Attempts to place a symbol on the board at a given location.
 * @param symbol The player's symbol ('X' or 'O').
 * @param row The 0-indexed row.
 * @param col The 0-indexed column.
 * @return 1 if the move was valid and played, 0 if the position was already marked.
 */
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

/**
 * @brief Checks if the current player has won the game.
 * @param currentPlayer The symbol to check ('X' or 'O').
 * @return 1 if the player won, 0 otherwise.
 */
int ifWon(char currentPlayer){
    for(int i=0;i<3;i++){
        // check rows
        if(board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer){
            printf("Player %c won the game\n",currentPlayer);
            return 1;
        }
        // check columns
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

/**
 * @brief Prompts the user for a row and column position (1-3) and converts it to 0-indexed.
 * @param pos An array of size 2 to store the 0-indexed row and column.
 */
void getPosition(int pos[]) {
    int r, c;

    printf("\nChoose row position (1, 2, or 3), 'm' for Menu, or 'q' to quit: ");
    r = input(1,3);
    if(r == -1){
        menu();
    }    
    pos[0] = r-1;
    
    printf("\nChoose column position (1, 2, or 3), 'm' for Menu, or 'q' to quit: ");
    c = input(1,3);
    if(c == -1){
        menu();
    }    
    pos[1] = c-1;
}    

/**
 * @brief Evaluates the current board state for the Minimax algorithm.
 * @param board The 3x3 game board.
 * @return 10 for Maximizer ('X') win, -10 for Minimizer ('O') win, 0 for draw, -1 for ongoing game.
 */
int evaluate_board(char board[3][3]) {
    char player1 = 'X'; // Maximizer
    char player2 = 'O'; // Minimizer

    // --- 1. Check Win/Loss (+10 or -10) ---
    for (int i = 0; i < 3; i++) {
        // Check Rows
        if(board[i][0] == player1 && board[i][1] == player1 && board[i][2] == player1){
            return 10;
        }
        if(board[i][0] == player2 && board[i][1] == player2 && board[i][2] == player2){
            return -10;
        }
        // Check Columns
        if(board[0][i] == player1 && board[1][i] == player1 && board[2][i] == player1){
            return 10;
        }
        if(board[0][i] == player2 && board[1][i] == player2 && board[2][i] == player2){
            return -10;
        }
    }
    
    // Check Diagonals
    if((board[0][0] == player1 && board[1][1] == player1 && board[2][2] == player1)|| (board[0][2] == player1 && board[1][1] == player1 && board[2][0] == player1)){
        return 10;
    }
    if((board[0][0] == player2 && board[1][1] == player2 && board[2][2] == player2)|| (board[0][2] == player2 && board[1][1] == player2 && board[2][0] == player2)){
        return -10;
    }

    // --- 2. Check Draw (0) ---
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

/**
 * @brief The recursive Minimax algorithm to find the optimal score for the current player.
 * @param board The 3x3 game board.
 * @param is_maximizer True if it's the Maximizer's ('X') turn, false if Minimizer's ('O').
 * @return The optimal score the current player can achieve from this state.
 */
int minimax(char board[3][3], bool is_maximizer) {
    // 1. BASE CASE: If the position is a terminal state (win, loss, or draw), return the score.
    int score = evaluate_board(board);
    if (score != -1) { // -1 means game is not over
        return score;
    }
    
    if (is_maximizer) {
        // Maximizer's turn ('X') - aims for a high score.
        int maximizer = -100000;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    // 3. Make the move
                    board[i][j] = 'X';
                    // 4. Call minimax recursively for the other player
                    int current_score = minimax(board, false);
                    // 5. Update the best score found so far
                    if (current_score > maximizer){
                        maximizer = current_score;
                    }
                    // 6. Un-do the move (backtrack)
                    board[i][j] = '-';
                }
            }
        }
        // 7. Return the final best score.
        return maximizer;
            
    } else { 
        // Minimizer's turn ('O') - aims for a low score.
        int minimizer = 100000;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    // 3. Make the move using the Minimizer's symbol
                    board[i][j] = 'O';
                    // 4. Call minimax recursively for the Maximizer
                    int current_score = minimax(board, true);
                    // 5. Update the best (lowest) score found so far
                    if (current_score < minimizer){
                        minimizer = current_score;
                    }
                    // 6. Un-do the move (backtrack)
                    board[i][j] = '-';
                }
            }
        }
        // 7. Return the final best (lowest) score.
        return minimizer;
    }
}

/**
 * @brief Determines the best move for the AI ('O') using the Minimax algorithm.
 * @param bestMove An array of size 2 to store the best 0-indexed row and column.
 */
void find_best_move(int bestMove[2]){
    // AI is the Minimizer ('O'), so we want the move that results in the lowest score.
    int bestscore = 100000; 

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                // Try this move
                board[i][j] = 'O';
                // Find the score for this move by letting the Maximizer ('X') play next
                int curentScore = minimax(board, true);
                // Check if this move is better (lower score) than the current best
                if( curentScore < bestscore){
                    bestscore = curentScore;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
                // Undo the move (backtrack)
                board[i][j] = '-';
            }
        }
    }
}

/**
 * @brief Handles the main Tic-Tac-Toe game loop.
 */
void playTicTacToe(){
    system(CLEAR);
    char player1 = 'X', player2 = 'O'; // Player 1 is 'X', AI is 'O'
    char currentPlayer;
    // Reset board and count for a new game
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            board[i][j] = '-';
        }
    }
    playCount = 0;

    displayBoard();
    while(playCount!=9){
        int valid = 0;
        // Determine the current player
        if(playCount%2 == 0){
            // Player 1's ('X') turn (Human)
            currentPlayer = player1;
            int RowCol[2];
            
            printf("Current player : %c\n\n", currentPlayer);
            do {
                getPosition(RowCol);
                valid = play(currentPlayer, RowCol[0], RowCol[1]);
            } while (!valid);
        } else {
            // Player 2's ('O') turn (AI)
            currentPlayer = player2;
            int moveArray[2];

            printf("AI is thinking");
            for (int i = 0; i < 2; i++) {
                sleep(1);
                printf(".");
            }
            // Find and execute AI's best move
            find_best_move(moveArray);
            play(player2, moveArray[0], moveArray[1]);
        }

        displayBoard();

        if(ifWon(currentPlayer)){
            // Game ended with a win
            system(CLEAR);
            return;
        }
    }
    // If loop finishes without a win
    printf("Draw!!!\n");
}

/**
 * @brief Displays the main menu and handles user choices.
 */
void menu(){
    system(CLEAR);
    printf("-------Menus-------\n");
    printf("(1) play Tic Tac Toe\n");
    printf("(2) Quit game\n");
    while(1){
        printf("Enter your choice: ");
        int choice = input(1,2);
        if (choice == 1) {
            playTicTacToe();
        }else if (choice == 2) {
            printf("Program quiting...\n");
            exit(0); 
        } 
    }
}

int main(){
    menu();
    return 0;
}