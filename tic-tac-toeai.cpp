#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
private:
    vector<char> board;

    const int winPatterns[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

public:
    TicTacToe() {
        resetBoard();
    }

    void resetBoard() {
        board={'1','2','3','4','5','6','7','8','9'};
    }

    void displayBoard() {
        cout << "\n";
        cout << " " << board[0] << " | " <<board[1] << " | "<<board[2] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[3] << " | "<< board[4] << " | " << board[5] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[6]<< " | " << board[7] << " | " <<board[8] << "\n";
        cout << "\n";
    }

    bool isMovesLeft() {
        for (char cell : board) {
            if (cell != 'X' && cell != 'O')
                return true;
        }
        return false;
    }

    bool checkWin(char player) {
        for (auto &pattern : winPatterns) {
            if (board[pattern[0]]==player &&
                board[pattern[1]]==player &&
                board[pattern[2]]==player)
                return true;
        }
        return false;
    }

    int evaluate() {
        if (checkWin('O'))
            return 10;

        if (checkWin('X'))
            return -10;

        return 0;
    }

    // Minimax with Alpha-Beta Pruning
    int minimax(bool isMax, int depth, int alpha, int beta) {

        int score=evaluate();

        if (score==10)
            return score - depth;

        if (score== -10)
            return score + depth;

        if (!isMovesLeft())
            return 0;

        if (isMax) {

            int best = -1000;

            for (int i = 0; i < 9; i++) {

                if (board[i] != 'X' && board[i] != 'O') {

                    char temp = board[i];
                    board[i] = 'O';

                    best = max(best,
                               minimax(false, depth + 1,
                                       alpha, beta));

                    board[i] = temp;

                    alpha = max(alpha, best);

                    if (beta <= alpha)
                        break; // Prune
                }
            }

            return best;
        }
        else {

            int best = 1000;

            for (int i = 0; i < 9; i++) {

                if (board[i]!= 'X' && board[i] != 'O') {

                    char temp=board[i];
                    board[i] = 'X';

                    best=min(best,
                               minimax(true, depth + 1,
                                       alpha, beta));

                    board[i] = temp;

                    beta = min(beta, best);

                    if (beta <= alpha)
                        break; // Prune
                }
            }

            return best;
        }
    }

    int findBestMove() {

        int bestValue= -1000;
        int bestMove= -1;

        for (int i = 0; i < 9; i++) {

            if (board[i] != 'X' && board[i] != 'O') {

                char temp=board[i];
                board[i] = 'O';

                int moveValue=
                    minimax(false, 0, -1000, 1000);

                board[i] = temp;

                if (moveValue > bestValue) {
                    bestValue = moveValue;
                    bestMove = i;
                }
            }
        }

        return bestMove;
    }

    bool makeHumanMove(int pos) {

        if (pos < 1 || pos > 9)
            return false;

        if (board[pos - 1]== 'X' ||
            board[pos - 1]== 'O')
            return false;

        board[pos - 1] = 'X';
        return true;
    }

    void makeAIMove() {

        int bestMove = findBestMove();

        if (bestMove != -1)
            board[bestMove] = 'O';
    }

    void playGame() {

        cout << "\n=== TIC TAC TOE AI ===\n";
        cout << "You = X\n";
        cout << "AI  = O\n";

        char choice;

        cout << "Do you want to play first? (y/n): ";
        cin >> choice;

        bool humanTurn =
            (choice == 'y' || choice == 'Y');

        while (true) {

            displayBoard();

            if (humanTurn) {

                int move;

                cout << "Enter position (1-9): ";

                while (!(cin >> move) ||
                       !makeHumanMove(move)) {

                    cout << "Invalid move. Try again: ";

                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );
                }

                if (checkWin('X')) {

                    displayBoard();
                    cout << "You win!\n";
                    break;
                }
            }
            else {

                cout << "AI is thinking...\n";

                makeAIMove();

                if (checkWin('O')) {

                    displayBoard();
                    cout << "AI wins!\n";
                    break;
                }
            }

            if (!isMovesLeft()) {

                displayBoard();
                cout<< "It's a draw!\n";
                break;
            }

            humanTurn= !humanTurn;
        }
    }
};

int main() {

    char again;

    do {

        TicTacToe game;
        game.playGame();

        cout<< "\nPlay again? (y/n): ";
        cin>>again;

    } while (again== 'y' ||again== 'Y');

    cout<< "\nThanks for playing!\n";

    return 0;
}