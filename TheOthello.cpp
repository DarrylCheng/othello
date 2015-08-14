/**********|**********|**********|
Program: TheOthello.cpp
Course: Degree: Computer science
Year: 2015/16 Trimester 1
Name: Darryl Cheng Lin Wei
ID: 1142700585
Email: darrylclw@gmail.com
Phone: 012-737-0538
**********|**********|**********/

#include <iostream> //cout/cin
#include <string> //String
#include <stdlib.h> //system("cls")
#include <iomanip> //setw
#include <sstream> //istringstream
#include <fstream>
#include <cctype> //isalpha()
using namespace std;

#define cls (system("cls")) //Clear screen
#define arrow (cout << "==> ") 
#define SymbolO(x,y) board[x][y]='O' //Input symbol O on the board
#define SymbolX(x,y) board[x][y]='X' //Input symbol X on the board
#define banner cout << line << "\n|" << setw(30) << right << "Othello: The Game"  << setw(20) << "|\n" << line << endl; //Game banner

void menu();
void game();
void ingame_commands();
void validateMove(int,int);
void helpPage(); 
void displayStatus(); //Display score and current player
void convertIndex(char&, int&);

bool player = true; //True for player X, false for player Y. Default first player will be X.
string line(50, '-');
string selections = "1. New Game\n2. Load a game\n3. Help\n4. Quit\n\n";
string gameboard(" |---+---+---+---+---+---+---+---|\n");
string menu_commands, game_commands;
bool done = false;
char board[8][8]; //Initialize (Multidimensional Array) Serves as the game board on screen.
int totalscore=0; //If totalscore is 64 which is all the possible input spaces available, means the game has ended.

int main() //Main function
{
	menu();
	return 0;
}

void menu() //Start up screen 
{
	cls; 
	banner;
	cout << "Choose the following selections\nType the number or the whole text\n\n";
	cout << selections;
	arrow;
	getline(cin, menu_commands);
	for(int i=0; i< menu_commands.length(); i++) {
		menu_commands[i] = toupper(menu_commands[i]); 
		//convert user input into capital letters, so program only have to check for capitalized version of each command.
	}
	if (menu_commands == "1" || menu_commands == "NEW GAME"){	
		SymbolX(4,3), SymbolO(4,4), SymbolO(3,3), SymbolX(3,4); //Initialize board
		done = false;
		game();
	}
	else if (menu_commands == "2" || menu_commands == "LOAD A GAME"){
		ifstream read;
		read.open("a.txt");
		for(int X=0;X<8;X++){
			for(int Y=0;Y<8;Y++){

				read.get(board[X][Y]);
			}
		}
		read >> player;
		read.close();
		game();
	}
	else if (menu_commands == "3" || menu_commands == "HELP"){
		helpPage(); //Display help page
	}
	else if (menu_commands == "4" || menu_commands == "QUIT"){
		cout << "Good bye!"; 
		return;
		//Back to main()
	}
	else {
		//If invalid input, back to menu.
		cout << "\a"; //Beep sound indicates invalid input
		menu();
	}
}

void game(){ //Draws the game board
	cls; 
	banner;
	int num=8; //Vertical numbers beside the game board
	for (int i=0;i<=7;i++) { //Draws the game board using for loop
	
		cout << gameboard; //A string of text declared at line 36
		cout << num-- << "|";
		for(int j=0;j<=7;j++)
		{
			cout << " " << board[i][j] << " |";
		}
		cout << endl;
	}
	cout << gameboard; //A string of text declared at line 36
	cout << "   a   b   c   d   e   f   g   h"; //Horizontal alphabets below the game board
	displayStatus(); //Display score and player turn
	//totalscore's value is from displayStatus()

	if(!done){
		ingame_commands();
		return;
	} else {
		totalscore = 0; //Resets the game (Refer in displayStatus())
		player = true; //Re initialize player back to true.
		menu(); //Back to menu
	}
}

void ingame_commands(){ //GET user input in game
	cout << endl;
	arrow;
	if (getline(cin, game_commands)){
		for(int i=0; i< game_commands.length(); i++) {
			game_commands[i] = toupper(game_commands[i]); 
			//convert user input into capital letters, so program only have to check for capitalized version of each command.
		}
		if (game_commands == "MENU"){
			for (int i=0;i<=7;i++) //For loop used to reset/re-initialize all array back to 0
			{
				for(int j=0;j<=7;j++){
					board[i][j] = ' ';
				}
			}
			player = true; //Re initialize player back to true.
			menu(); 
		}
		else if (game_commands == "NEXT PLAYER"){
			if (player == true){ //Flag variable? Switching between players are determined with true and false
				player = false; //False for player Y.
			} else {
				player = true; //True for player X.
			}
			game();
		} 
		else if (game_commands == "SAVE"){
			ofstream savegame;
			savegame.open("a.txt");
			for(int X=0;X<8;X++){
				for(int Y=0;Y<8;Y++){
					savegame << board[X][Y];
				}
			}
			savegame << player;
			savegame.close();
			game();
		} else {
			istringstream seperate(game_commands); //Seperate input into char and int 
			char alpha;
			int num;
			seperate >> alpha >> num;
			convertIndex(alpha,num);
			if (!(alpha == 10 || num == 10) && !(board[num][alpha]=='X' || board[num][alpha]=='O')){  //If returned number 10, means one of the inputs are false.
				validateMove(alpha, num);
				game();
			} else {
				cout << "\a"; //Beep sound indicates invalid input
				game();
			}
}  //game() function are called to re-draw the game board with the necessary changes by user input	
	}	
}

void validateMove(int right, int left){
	int largest = right;
	if (player == true){ //X
		SymbolX(left, right);
		player = false;									
	} 
	else{ //O
		SymbolO(left, right);
		player = true;
	}
	return;
}
void displayStatus() //Display player score and turn.
{
	int scoreX=0,scoreO=0;
	for(int a=0;a<8;a++) {
		for(int b=0;b<8;b++) {
			if (board[a][b] == 'O') //Calculates how many array are equal to 1 (Which is Symbol O)
			{
				scoreO++;
			}
			else if (board[a][b] == 'X')//Calculates how many array are equal to 2 (Which is Symbol X)
			{
				scoreX++;
			} 
		}
	}
	totalscore = scoreO + scoreX;
	if (totalscore == 64){
		done = true;
	}
	cout << "\nScore:\t\tO = " << scoreO << "\tX = " << scoreX << endl;
	if (!done)
	{
		if (player == true) //If player is TRUE, then it is player X. Else player O.
		{
			cout << "Current player: X";
		} else
			cout << "Current player: O";
	}	
	else 
	{
		if (scoreO < scoreX){
			cout << "Winner is player X!\n";
		} else if (scoreO == scoreX){
			cout << "It is a draw!\n";
		} else{
			cout << "Winner is player O!\n";
		}
		system("pause");
		for (int i=0;i<=7;i++) //For loop used to reset/re-initialize all array
		{
			for(int j=0;j<=7;j++){
				board[i][j] = ' ';
			}
		}
	}

}

void helpPage() //Game instructions
{
	cls;
	banner;
	cout  << "In game instructions:\nTo input into the game board, type in the format of (A-H, 1-8) for example \n"
		<< "==> f 4\n\nSpaces that already contain a X or O cannot be inputted again,\nonce the game board is fully filled,"
		<< " the game will display the winner and \nreturn to the game menu.\n";
	cout << "\nOther available commands in-game are:\n==> menu (Back to menu and resets the game)\n==> next player (Forfeit your turn)\n";
	cout << "A *beep* sound will be made for every invalid input.\n\n";
	system("pause"); //Pause 
	menu(); //Back to menu()
}

void convertIndex(char& alpha, int& num) //Convert them into array readable numbers, since user input (F,5) are (5,3) in terms of array positions.
{
	if (alpha>= 65 && alpha<=72){ //ASCII
		alpha -= 65;
	} else {
		alpha = 10; //Return as error
	}

	static int numbers[8] = {7,6,5,4,3,2,1,0};
	if (num>0 && num<9)
	{
		num =  numbers[num-1];
	} else {
		num = 10; //Return as error
	}
}
