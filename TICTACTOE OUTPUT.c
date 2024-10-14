#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for input validation functions
#include <string.h> // for string manipulation

char arr[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int moveHistory[9];
int moveCount = 0;
char player1Marker, player2Marker; // Global variables for markers

void showBoard();
int checkForWin();
void resetBoard();
void showMoveHistory(char *player1, char *player2);
void displayRules(); // Function to display rules of the game
void chooseMarkers(); // Function to allow players to choose markers

// Driver Function
int main()
{
    char player1[50], player2[50];
    char choice;
    int player = 1, gameOver, position;
    char mark;

    displayRules(); // Display the rules before starting the game
    chooseMarkers(); // Allow players to choose markers

    // Prompt for Player 1 name
    printf("Enter Player 1 Name: ");
    scanf("%s",player1);
    player1[strcspn(player1, "\n")] = '\0'; // Remove newline character

    // Prompt for Player 2 name
    printf("Enter Player 2 Name: ");
    scanf("%s",player2);
    player2[strcspn(player2, "\n")] = '\0'; // Remove newline character

    do
    {
        resetBoard();
        moveCount = 0;
        player = 1; // Player 1 starts first
        gameOver = -1;

        do
        {
            showBoard();
            player = (player % 2) ? 1 : 2;

            printf("%s's turn (choose a number from 1-9): ", (player == 1) ? player1 : player2);

            if (scanf("%d", &position) != 1 || position < 1 || position > 9 || arr[position] != '0' + position)
            {
                printf("Invalid move! Please try again.\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }

            mark = (player == 1) ? player1Marker : player2Marker; // Use chosen markers
            arr[position] = mark;
            moveHistory[moveCount++] = position;

            gameOver = checkForWin();
            player++;

        } while (gameOver == -1);

        showBoard();

        if (gameOver == 1)
        {
            printf("Congratulations, %s wins!\n", (player == 2) ? player1 : player2);
        }
        else
        {
            printf("It's a draw!\n");
        }

        showMoveHistory(player1, player2);

        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clear input buffer

    } while (toupper(choice) == 'Y');

    return 0;
}

// Function to print the Tic-Tac-Toe board
void showBoard()
{
    system("cls || clear");
    printf("\tTIC TAC TOE\n\n");
    printf("       |       |      \n");
    printf("   %c   |   %c   |   %c   \n", arr[1], arr[2], arr[3]);
    printf("-------|-------|-------\n");
    printf("   %c   |   %c   |   %c   \n", arr[4], arr[5], arr[6]);
    printf("-------|-------|-------\n");
    printf("   %c   |   %c   |   %c   \n", arr[7], arr[8], arr[9]);
    printf("       |       |      \n\n");
}

// Function to check for a win
int checkForWin()
{
    if (arr[1] == arr[2] && arr[2] == arr[3])
        return 1;
    else if (arr[4] == arr[5] && arr[5] == arr[6])
        return 1;
    else if (arr[7] == arr[8] && arr[8] == arr[9])
        return 1;
    else if (arr[1] == arr[4] && arr[4] == arr[7])
        return 1;
    else if (arr[2] == arr[5] && arr[5] == arr[8])
        return 1;
    else if (arr[3] == arr[6] && arr[6] == arr[9])
        return 1;
    else if (arr[1] == arr[5] && arr[5] == arr[9])
        return 1;
    else if (arr[3] == arr[5] && arr[5] == arr[7])
        return 1;
    else if (arr[1] != '1' && arr[2] != '2' && arr[3] != '3' &&
             arr[4] != '4' && arr[5] != '5' && arr[6] != '6' &&
             arr[7] != '7' && arr[8] != '8' && arr[9] != '9')
        return 0;
    else
        return -1;
}

// Function to reset the board for a new game
void resetBoard()
{
    for (int i = 1; i <= 9; i++)
    {
        arr[i] = '0' + i;
    }
}

// Function to display the history of moves made during the game
void showMoveHistory(char *player1, char *player2)
{
    printf("\nMove History:\n");
    for (int i = 0; i < moveCount; i++)
    {
        printf("Move %d: Player %s placed on %d\n", i + 1, (i % 2 == 0) ? player1 : player2, moveHistory[i]);
    }
}

// Function to display the rules of the game
void displayRules()
{
    printf("Welcome to the Tic-Tac-Toe Game!\n");
    printf("Here are the rules:\n");
    printf("1. The game is played on a grid of 3x3 squares.\n");
    printf("2. You are Player 1 or Player 2.\n");
    printf("3. Player 1 uses 'X', and Player 2 uses 'O'.\n");
    printf("4. The goal is to get three of your marks (X or O) in a row, column, or diagonal.\n");
    printf("5. To place your mark, choose a number corresponding to the square's position on the board (1-9).\n");
    printf("6. The first player to get three in a row wins!\n");
    printf("7. If all squares are filled and no player has three in a row, the game ends in a draw.\n\n");
    printf("Press any key to start the game...\n");
    getchar(); // Wait for the player to press a key before starting
}

// Function to allow players to choose their markers
void chooseMarkers()
{
    char markerChoice;
    
    do {
        printf("Choose marker for Player 1 (X or O): ");
        scanf(" %c", &markerChoice);
        markerChoice = toupper(markerChoice); // Convert to uppercase

        if (markerChoice == 'X') {
            player1Marker = 'X';
            player2Marker = 'O';
        } else if (markerChoice == 'O') {
            player1Marker = 'O';
            player2Marker = 'X';
        } else {
            printf("Invalid choice. Please choose either 'X' or 'O'.\n");
        }
    } while (markerChoice != 'X' && markerChoice != 'O');
}
