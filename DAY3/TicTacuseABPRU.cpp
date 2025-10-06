#include<iostream>
using namespace std;

#define COMPUTER 1
#define HUMAN 2 

#define SIZE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// Display the board
void showBoard(char board[][SIZE]){
    cout<<"   "<<board[0][0]<< " | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"----------------"<<endl;
    cout<<"   "<<board[1][0]<< " | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"----------------"<<endl;
    cout<<"   "<<board[2][0]<< " | "<<board[2][1]<<" | "<<board[2][2]<<endl;
}

// Show instructions for positions
void showIntruction(){
    cout<<"Choose any place where you want to place it."<<endl;
    cout<<"    1 | 2 | 3  " <<endl;
    cout<<"   ------------" <<endl;
    cout<<"    4 | 5 | 6  " <<endl;
    cout<<"   ------------" <<endl;
    cout<<"    7 | 8 | 9  " <<endl;
}

// Initialize the board
void Initialize(char board[][SIZE]){
    for(int i=0; i< SIZE; i++){
        for(int j=0; j< SIZE; j++){
            board[i][j] = ' ';
        }
    }
}

// Declare winner
void declareWinner( int whoseturn){
    if( whoseturn == COMPUTER){
        cout<<"Computer wins!"<<endl;
    }
    else{
        cout<<"Human wins!"<<endl;
    }
}

// Check row victory
bool rowCrossed(char board[][SIZE]){
    for(int i=0 ; i<SIZE ; i++){
        if( board[i][0] == board[i][1] && board[i][1]== board[i][2] && board[i][0] != ' '){
            return true;
        }
    }
    return false;
}

// Check column victory
bool columnCrossed(char board[][SIZE]){
    for(int i=0; i< SIZE; i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' '){
            return true;
        }
    }
    return false;
}

// Check diagonal victory
bool DiagonalCrossed(char board[][SIZE]){
    if( board[0][0]== board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' '){
        return true;
    }
    if( board[0][2]== board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '){
        return true;
    }
    return false;
}

// Check if the game is over
bool gameOver(char board[][SIZE]){
    return (rowCrossed(board) || columnCrossed(board) || DiagonalCrossed(board));
}

// Minimax with Alpha-Beta pruning
int minmax(char board[][SIZE], int depth, bool isAI, int alpha, int beta){
    if(gameOver(board)){
        if(isAI)
            return -1;
        else
            return +1;
    }
    if(depth == 9)
        return 0;
    
    if(isAI){
        int bestscore = -999;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                if(board[i][j] == ' '){
                    board[i][j] = COMPUTERMOVE;
                    int score = minmax(board, depth+1, false, alpha, beta);
                    board[i][j] = ' ';
                    bestscore = max(bestscore, score);
                    alpha = max(alpha, bestscore);
                    if(beta <= alpha)
                        return bestscore;
                }
            }
        }
        return bestscore;
    } else {
        int bestscore = 999;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                if(board[i][j] == ' '){
                    board[i][j] = HUMANMOVE;
                    int score = minmax(board, depth+1, true, alpha, beta);
                    board[i][j] = ' ';
                    bestscore = min(bestscore, score);
                    beta = min(beta, bestscore);
                    if(beta <= alpha)
                        return bestscore;
                }
            }
        }
        return bestscore;
    }
}

// Function to calculate best move
int bestMove(char board[][SIZE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minmax(board, moveIndex+1, false, -999, 999);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*SIZE + y;
}

// Main game loop
void play_tic_tac_toe(int whoseturn){
    char board[SIZE][SIZE];
    int moveIndex = 0, x =0 , y=0;
    
    Initialize(board);
    showIntruction();

    while( gameOver(board) == false && moveIndex != SIZE*SIZE ){
        int n;
        if(whoseturn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIZE;
            y = n % SIZE;
            board[x][y] = COMPUTERMOVE;
            cout<<"Computer has put "<< COMPUTERMOVE<<" at "<<n+1<<endl;
            showBoard(board);
            moveIndex++;
            whoseturn = HUMAN;
        }
        else if(whoseturn == HUMAN)
        {
            cout<<"You can insert in any of the following position "<<endl;
            for(int i =0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    if(board[i][j] == ' ' ){
                        cout<<i*3 + j + 1<<endl;
                    }
                }
            }
            cout<<"Enter the position: "<<endl;
            cin>>n;
            n = n-1;
            x = n / SIZE;
            y = n % SIZE;

            if(n>=0 && n<9 && board[x][y] == ' ')
            {
                board[x][y] = HUMANMOVE;
                cout<<"Human has put "<<HUMANMOVE<< " at "<< n+1<<endl;
                showBoard(board);
                moveIndex++;
                whoseturn  = COMPUTER;
            }
            else{
                cout<<"Invalid or filled position! Try again."<<endl;
            }
        }
    }

    if(gameOver(board) == false && moveIndex == SIZE*SIZE){
        cout<<"It's a draw!"<<endl;
    }
    else{
        if(whoseturn == COMPUTER){
            whoseturn = HUMAN;
        } else {
            whoseturn = COMPUTER;
        }
        declareWinner(whoseturn); 
    }
}

// Main function
int main(){
    cout<<"      Tic Tac Toe"<<endl;
    cout<<" ---------------------"<<endl;
    char playing = 'y';
    do {
        char choice;
        cout<<"Do you want to play first (y/n) ?"<<endl;
        cin>> choice;

        if(choice =='n'){
            play_tic_tac_toe(COMPUTER);
        }
        else if(choice =='y'){
            play_tic_tac_toe(HUMAN);
        }
        else{
            cout<<"Enter a valid choice."<<endl;
        }

        cout<<"Do you want to quit ? (y/n)"<<endl;
        cin>>playing;
    }while(playing == 'n');
    return 0;
}