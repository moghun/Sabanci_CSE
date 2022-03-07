//Muhammed Orhun Gale - 26754

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


char** board;       //Pointer to share board
int board_size;     //Board size variable that will be taken from the user

char turn;          //Indicates who has the turn
int WinX = 0;       //Logical variable that indicates whether X win or not
int WinO = 0;       //Logical variable that indicates whether O win or not

int isGameCont = 1; //Logical variable that indicates whether the game has been concluded or not

pthread_mutex_t mutex;  //Lock to control threads

//Checks if the given player (X or O) win the game by a full row
//Returns logical indicator
int checkRows(char player)
{
    for (int i = 0; i < board_size; i++)
    {
        int winningCondition = 1;
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] != player)
            {
                winningCondition = 0;
            }
        }
        if (winningCondition == 1)
        {
            return 1;
        }
    }
    return 0;
}

//Checks if the given player (X or O) win the game by a full column
//Returns logical indicator
int checkCols(char player)
{
    for (int i = 0; i < board_size; i++)
    {
        int winningCondition = 1;
        for (int j = 0; j < board_size; j++)
        {
            if (board[j][i] != player)
            {
                winningCondition = 0;
            }

        }
        if (winningCondition == 1)
        {
            return 1;
        }
    }
    return 0;
}

//Checks if the given player (X or O) win the game by a full main diagonal
//Returns logical indicator
int diagUL2DR(char player)
{
    int winningCondition = 1;
    for (int i = 0; i < board_size; i++)
    {
        if (board[i][i] != player) //From upper left to lower right
        {
            winningCondition = 0;
        }

    }
    return winningCondition;
}

//Checks if the given player (X or O) win the game by a full anti main diagonal
//Returns logical indicator
int diagDR2UL(char player)
{
    int winningCondition = 1;
    for (int i = 0; i < board_size; i++)
    {
        if (board[(board_size - i) - 1][i] != player) //From lower left to upper right
        {
            winningCondition = 0;
        }

    }
    return winningCondition;
}

//In given player's turn, finds a random empty location to insert player's sign
//Checks if the player won or not after it places its sign
int play(char player) 
{
    int x;
    int y;
    
    //Find empty location
    int locationFound = 0;

    while (locationFound == 0)
    {
        x = rand() % board_size;
        y = rand() % board_size;
        if (board[x][y] == ' ')
        {
            board[x][y] = player;
            locationFound = 1;
            printf("Player %c played on: (%d,%d)\n", player, x, y);
        }
    }

    //Check if the player won or not via scanning all possible scenerios
    int check = checkRows(player);

    if (check == 1)
    {
        isGameCont = 0;
        return 1;
    }

    check = checkCols(player);

    if (check == 1)
    {
        isGameCont = 0;
        return 1;
    }


    check = diagUL2DR(player);

    if (check == 1)
    {
        isGameCont = 0;
        return 1;
    }

    check = diagDR2UL(player);

    if (check == 1)
    {
        isGameCont = 0;
        return 1;
    }

    //If the board is full after the player placed its sign, end the game
    int isFull = 1;

    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            if (board[i][j] == ' ')
                isFull = 0;
        }
    }

    if (isFull == 1)
    {
        isGameCont = 0;
    }

    return 0;

}

//Makes X Player's moves
void* XPlayer(void* ptr)
{
    //Until the game concludes
    int flag = 1;
    while (flag == 1)
    {
        pthread_mutex_lock(&mutex);         //Lock the table to make your move if:


        if (isGameCont == 0)                //Game is not finished yet
        {
            pthread_mutex_unlock(&mutex);   //Otherwise unlock the mutex
            pthread_exit(NULL);             //Since the game finished, exit the thread
        }

        else if (turn != 'X')               //If it is not your turn
        {
            pthread_mutex_unlock(&mutex);

        }


        else {                                   //If it is your turn and game still on process
            WinX = play('X');                    //Make your move and see if you win or not

            if (isGameCont == 0 || WinX == 1)   //If you win or the game is concluded
            {
                isGameCont = 0;
                turn = 'O';                     //Say that your turn is over by giving the turn

                pthread_mutex_unlock(&mutex);   //Unlock the mutex
                pthread_exit(NULL);             //Since the game finished, exit the thread
                flag = 0;
            }

            else {                              //Pass the turn
                turn = 'O';
                pthread_mutex_unlock(&mutex);   //Unlock the mutex
            }
        }
    }
	return NULL;
}

//Makes O Player's moves
void* OPlayer(void* ptr)
{
    //Until the game concludes
    int flag = 1;
    while (flag == 1)
    {
        pthread_mutex_lock(&mutex);         //Lock the table to make your move if:


        if (isGameCont == 0)                //Game is not finished yet
        {
            pthread_mutex_unlock(&mutex);   //Otherwise unlock the mutex
            pthread_exit(NULL);             //Since the game finished, exit the thread
        }

        else if (turn != 'O')               //If it is not your turn
        {
            pthread_mutex_unlock(&mutex);

        }


        else {                                   //If it is your turn and game still on process
            WinO = play('O');                    //Make your move and see if you win or not

            if (isGameCont == 0 || WinX == 1)   //If you win or the game is concluded
            {
                isGameCont = 0;
                turn = 'X';                     //Say that your turn is over by giving the turn

                pthread_mutex_unlock(&mutex);   //Unlock the mutex
                pthread_exit(NULL);             //Since the game finished, exit the thread
                flag = 0;
            }

            else {                              //Pass the turn
                turn = 'X';
                pthread_mutex_unlock(&mutex);   //Unlock the mutex
            }
        }
    }
	return NULL;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));              //Start the srand

    board_size = atoi(argv[1]);     //Take the board_size from the user
    board = (char**)malloc(sizeof(char*) * board_size); //Allocate the memory for the shared board

    //Construct the board for with space char entries that indicates "empty" spots
    for (int i = 0; i < board_size; i++)
    {
        board[i] = (char*)malloc(board_size); //Allocate memory for each char
        for (int j = 0; j < board_size; j++)
        {
            board[i][j] = ' ';
        }
    }
    printf("Board Size : %dx%d\n", board_size, board_size);

    //Create threads
    pthread_t p1;
    pthread_t p2;

    turn = 'X'; //Start the game by giving the first turn to X Player

    //Pass player functions
    int rc1 = pthread_create(&p1, NULL, XPlayer, NULL);
    //Check if the thread-1 sucsessfully returned or not
    assert(rc1 == 0);
    


    int rc2 = pthread_create(&p2, NULL, OPlayer, NULL);
    //Check if the thread-2 sucsessfully returned or not
    assert(rc2 == 0);

    //Join after each thread ends
    (void)pthread_join(p1, NULL);
    (void)pthread_join(p2, NULL);


    //Print the game result
    printf("\nGame end\n");

    //If X won
    if (WinX == 1)
    {
        printf("Winner is X\n");
    }
    //If O won
    else if (WinO == 1)
    {
        printf("Winner is O\n");
    }

    //If it is a tie
    else
    {
        printf("It is a tie\n");
    }

    //Print the board
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            printf("[%c]", board[i][j]);
        }
        printf("\n");
    }
    
    int ex = pthread_mutex_destroy(&mutex); //Destroy mutex
    
    //Return peacefully
    return 0;
}
