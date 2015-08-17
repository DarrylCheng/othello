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
#include <cstdlib> //system("cls")
#include <iomanip> //setw
#include <sstream> //istringstream
#include <fstream>
#include <ctime>
using namespace std;

#define cls (system("cls")) //Clear screen
#define arrow (cout << "==> ") 
#define SymbolO(x,y) board[x][y]='O' //Input symbol O on the board
#define SymbolX(x,y) board[x][y]='X' //Input symbol X on the board
#define banner cout << line << "\n|" << setw(35) << right << "Super Othello: The Game"  << setw(15) << "|\n" << line << endl; //Game banner

void menu();
void game();
void ingame_commands();
void validateMove(int,int);
void helpPage(); 
void flipping(int,int);
void displayStatus(); //Display score and current player
void convertIndex(char&, int&);

bool player = true, invalid=false,done=false; //True for player X, false for player Y. Default first player will be X.
bool super1,super2,super3;
string line(50, '-');
char board[8][8]; //Initialize (Multidimensional Array) Serves as the game board on screen.
int totalscore=0; //If totalscore is 64 which is all the possible input spaces available, means the game has ended.

class SPower{
public:
	bool super1,super2,super3;
	int count1,count2,count3;
	void init(){
		count1 = 0, count2 = 0,count3 = 0;
		super1 = false,super2 = false,super3 = false;
	}
	void S1(){
		if (count1==0){
			super1 = true;
			count1=1;
		} else{
			cout << "\a";
		}
	}
	void S2(){
		if (count2==0){
			super2 = true;
			count2=1;
		} else{
			cout << "\a";
		}
	}
	void S3(){
		if (count3==0){
			super3 = true;
			count3=1;
		} else{
			cout << "\a";
		}	
	}
	void superthree(){
		if(super3){
			srand(time(NULL));
			int ran = rand()%8; //0-7
			for(int i=0;i<8;i++){
				board[ran][i] = ' ';
			}
		}
		if(player && super3){
			player=false;
		} else if (!player && super3) {
			player=true;
		}
		
	}
	void powerdescription(){
		if(super1){
			cout << "   (Super power 1! You can place ANYWHERE you like!)";
		} else if (super2){
			cout << "   (Super power 2! Two consequtive inputs!)";
		} else if (super3) {
			cout << "   (Super power 3! Cleared a random row :P)";
			super3 = false;
		}	
	}
};

SPower X;
SPower O;

int main() //Main function
{
	menu();
	return 0;
}

void menu() //Start up screen 
{
	static string selections = "1. New Game\n2. Load a game\n3. Help\n4. Quit\n\n";
	string menu_commands;
	X.init();
	O.init();
	bool menu=true,super1=false,super2=false,super3=false;
	for (int i=0;i<=7;i++){ //For loop used to reset/re-initialize all array
		for(int j=0;j<=7;j++){
			board[i][j] = ' ';
		}
	}
	while(menu){
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
			menu = false;
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
			menu = false;
			game();
		}
		else if (menu_commands == "3" || menu_commands == "HELP"){
			helpPage(); //Display help page
		}
		else if (menu_commands == "4" || menu_commands == "QUIT"){
			menu = false;
			cout << "Good bye!"; 
			//Back to main()
		}
		else {
			//If invalid input, back to menu.
			cout << "\a"; //Beep sound indicates invalid input
		}
	}
}

void game(){ //Draws the game board
	static string gameboard(" |---+---+---+---+---+---+---+---|\n");
	cls; 
	banner;
	int num=8; //Vertical numbers beside the game board
	for (int i=0;i<=7;i++) { //Draws the game board using for loop
		cout << gameboard; //A string of text declared at line 36
		cout << num-- << "|";
		for(int j=0;j<=7;j++){
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
	} else {
		player = true; //Re initialize player back to true.
		done = false;
		totalscore=0;		
		menu();
	}
}

void ingame_commands(){ //GET user input in game
	string game_commands;
	X.powerdescription();
	O.powerdescription();
	cout << endl;
	arrow;
	if (getline(cin, game_commands)){
		for(int i=0; i< game_commands.length(); i++) {
			game_commands[i] = toupper(game_commands[i]); 
			//convert user input into capital letters, so program only have to check for capitalized version of each command.
		}
		if (game_commands == "MENU"){
			player = true; //Re initialize player back to true.
			menu(); 
		}
		else if (game_commands == "NEXT PLAYER"){
			if (player){ //Flag variable? Switching between players are determined with true and false
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
		} else if (game_commands == "SUPER1"){
			if(player){
				X.S1();
			} else {
				O.S1();
			}
			game();
		} else if (game_commands == "SUPER2"){
			if(player){
				X.S2();
			} else {
				O.S2();
			}
			game();
		} else if (game_commands == "SUPER3"){
			if(player){
				X.S3();
				X.superthree();
			} else {
				O.S3();
				O.superthree();
			}
			game();
		} else {
			istringstream seperate(game_commands); //Seperate input into char and int 
			char alpha;
			int num;
			seperate >> alpha >> num;
			convertIndex(alpha,num);
			if (!invalid){ 
				validateMove(alpha, num);
			} else {
				cout << "\a"; //Beep sound indicates invalid input
			}
			game();
			//game() function are called to re-draw the game board with the necessary changes by user input	
		}
	}	
}

void validateMove(int right, int left){
	bool checkpiece = (board[left][right]=='X' || board[left][right]=='O');
	bool ori = checkpiece;
	if (X.super1||O.super1||X.super2||O.super2){
		checkpiece = true;
	} 
	if(!checkpiece){
		if (player){ //X
			SymbolX(left, right);
			player = false;									
		} 
		else{ //O
			SymbolO(left, right);
			player = true;
		}
	} else {
		if(X.super1 || O.super1){
			X.super1 = false;
			O.super1 = false;
			if(player){
				SymbolX(left, right);
				player = false;									
			} else{ //O
				SymbolO(left, right);
				player = true;
			}
		} else if(X.super2 || O.super2){
			if(!ori){
				X.super2 = false;
				O.super2 = false;
				if(player){
					SymbolX(left, right);
				} else{ //O
					SymbolO(left, right);
				} 
			} else {
				cout << "\a";
			}
		} else {
			cout << "\a";
		}
	}
	flipping(right, left);
}

void displayStatus() //Display player score and turn.
{
	int scoreX=0,scoreO=0;
	for(int a=0;a<8;a++) {
		for(int b=0;b<8;b++) {
			if (board[a][b] == 'O'){ //Calculates how many array are equal to 1 (Which is Symbol O)
				scoreO++;
			}
			else if (board[a][b] == 'X'){//Calculates how many array are equal to 2 (Which is Symbol X)
				scoreX++;
			} 
		}
	}
	totalscore = scoreO + scoreX;
	if (totalscore == 64){
		done = true;
	}
	cout << "\nScore:\t\tO = " << scoreO << "\tX = " << scoreX << endl;
	if (!done){
		if (player){ //If player is TRUE, then it is player X. Else player O.
			cout << "Current player: X";
		} else
			cout << "Current player: O";
	}	
	else {
		if (scoreO < scoreX){
			cout << "Winner is player X!\n";
		} else if (scoreO == scoreX){
			cout << "It is a draw!\n";
		} else{
			cout << "Winner is player O!\n";
		}
		system("pause");
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
	cout << "==> save (Save the game and load it later)\n==> super1 (Place your move ANYWHERE)\n"
		 << "==> super2 (Two consecutive turns\n==> super3 (Clear a random row)\n";
	cout << "A *beep* sound will be made for every invalid input.\n\n";
	system("pause"); //Pause 
}

void convertIndex(char& alpha, int& num) //Convert them into array readable numbers, since user input (F,5) are (5,3) in terms of array positions.
{
	invalid = false;
	if (alpha>= 65 && alpha<=72){ //ASCII
		alpha -= 65;
	} else {
		invalid=true; //Return as error
	}
	static int numbers[8] = {7,6,5,4,3,2,1,0};
	if (num>0 && num<9)
	{
		num = numbers[num-1];
	} else {
		invalid=true; //Return as error
	}
}

void flipping(const int right, const int left){
	int col = right, location, row = left;
	bool phase1=false,phase2=false;
	//west
	if(board[left][right]=='X'){
		if(board[left][col-1]=='O')
			phase1=true;
	} else if(board[left][right]=='O'){
		if(board[left][col-1]=='X')
			phase1=true;
	}
	if(phase1){
		while(col>0){
			if(board[left][right]=='X'){
				if(board[left][col-1]=='X'){
					phase2 = true;
					location=col-1;
					break;
				}
			} else if (board[left][right]=='O'){
				if(board[left][col-1]=='O'){
					phase2=true;
					location=col-1;
					break;
				}
			}
			col--;
		}
	}
	if(phase1 && phase2){
		while(location<=right){
			if(board[left][right]=='X'){
				SymbolX(left,location);
			} else if (board[left][right]=='O'){
				SymbolO(left, location);
			}
			location++;
		}
	}
	//east
	phase1=false,phase2=false;
	col = right,row = left;
	if(board[left][right]=='X'){
		if(board[left][col+1]=='O')
			phase1=true;
	} else if(board[left][right]=='O'){
		if(board[left][col+1]=='X')
			phase1=true;
	}
	if(phase1){
		while(col<7){
			if(board[left][right]=='X'){
				if(board[left][col+1]=='X'){
					phase2 = true;
					location=col+1;
					break;
				}
			} else if (board[left][right]=='O'){
				if(board[left][col+1]=='O'){
					phase2=true;
					location=col+1;
					break;
				}
			}
			col++;
		}
	}
	if(phase1 && phase2){
		while(location>=right){
			if(board[left][right]=='X'){
				SymbolX(left,location);
			} else if (board[left][right]=='O'){
				SymbolO(left, location);
			}
			location--;
		}
	}
	//NORTH
	phase1=false,phase2=false;
	col = right,row = left;
	if(board[left][right]=='X'){
		if(board[row-1][right]=='O')
			phase1=true;
	} else if(board[left][right]=='O'){
		if(board[row-1][right]=='X')
			phase1=true;
	}
	if(phase1){
		while(row>0){
			if(board[left][right]=='X'){
				if(board[row-1][right]=='X'){
					phase2 = true;
					location=row-1;
					break;
				}
			} else if (board[left][right]=='O'){
				if(board[row-1][right]=='O'){
					phase2=true;
					location=row-1;
					break;
				}
			}
			row--;
		}
	}
	if(phase1 && phase2){
		while(location<=left){
			if(board[left][right]=='X'){
				SymbolX(location,right);
			} else if (board[left][right]=='O'){
				SymbolO(location, right);
			}
			location++;
		}
	}
	//SOUTH
	phase1=false,phase2=false;
	col = right,row = left;
	if(board[left][right]=='X'){
		if(board[row+1][right]=='O')
			phase1=true;
	} else if(board[left][right]=='O'){
		if(board[row+1][right]=='X')
			phase1=true;
	}
	if(phase1){
		while(row<7){
			if(board[left][right]=='X'){
				if(board[row+1][right]=='X'){
					phase2 = true;
					location=row+1;
					break;
				}
			} else if (board[left][right]=='O'){
				if(board[row+1][right]=='O'){
					phase2=true;
					location=row+1;
					break;
				}
			}
			row++;
		}
	}
	if(phase1 && phase2){
		while(location>=left){
			if(board[left][right]=='X'){
				SymbolX(location,right);
			} else if (board[left][right]=='O'){
				SymbolO(location, right);
			}
			location--;
		}
	}
}