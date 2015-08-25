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
void flipping(int,int,bool&);
void displayStatus(); //Display score and current player
void convertIndex(char&, int&, bool&);
void stars();
bool player = true,done=false,star=false,canproceed; //True for player X, false for player Y. Default first player will be X.
string line(50, '-'); //Used on banner
char board[8][8]; //Initialize (Multidimensional Array) Serves as the game board on screen.
int totalscore=0; //If totalscore is 64 which is all the possible input spaces available, means the game has ended.

class SPower{
public:
	bool super1,super2,super3;
	bool count1,count2,count3;
	void init(){ //Initialize
		count1 = false, count2 = false,count3 = false;
		super1 = false,super2 = false,super3 = false;
	}
	void S1(){ //Super power 1
		if (!count1){
			super1 = true;
			count1=true; //ONE TIME ONLY
		} else{
			cout << "\a";
		}
	}
	void S2(){ //Super power 2
		if (!count2){
			super2 = true;
			count2=true; //ONE TIME ONLY
		} else{
			cout << "\a";
		}
	}
	void S3(){ //Super power 3
		if (!count3){
			super3 = true;
			count3=true; //ONE TIME ONLY
		} else{
			cout << "\a";
		}	
	}
	void superthree(){ 
		if(super3){
			srand(totalscore);
			int ran = rand()%8; //0-7
			for(int i=0;i<8;i++){ //Clear a random row
				board[ran][i] = ' ';
			}
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
}X,O; //X and O class

int main() //Main function
{
	menu();
	return 0;
}

void menu() //Start up screen 
{
	X.init();
	O.init();
	//Initialize X and O in class
	static string selections = "1. New Game\n2. Load a game\n3. Help\n4. Quit\n\n";
	string menu_commands;
	bool menu=true,super1=false,super2=false,super3=false;
	for (int i=0;i<=7;i++){ //For loop used to reset/re-initialize all array
		for(int j=0;j<=7;j++){
			board[i][j] = ' ';
		}
	}
	while(menu){
		cls; 
		banner;
		cout << "Choose the following selections\nType the number or the whole text to proceed\n"
			 << "Please read \"Help\" before playing!\n\n";
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
			for(int Z=0;Z<8;Z++){
				for(int Y=0;Y<8;Y++){
					read.get(board[Z][Y]); //Load game board save game
				}
			}
			char xx[7];
			read >> xx;
			player=xx[0]-48;
			//Load current player
			X.count1=xx[1]-48;
			X.count2=xx[2]-48;
			X.count3=xx[3]-48;
			O.count1=xx[4]-48;
			O.count2=xx[5]-48;
			O.count3=xx[6]-48;
			//Load super power usage history
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
			return;
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
	stars();
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
	bool invalid;
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
			for(int Z=0;Z<8;Z++){
				for(int Y=0;Y<8;Y++){
					savegame << board[Z][Y];
				}
			}
			savegame << player;
			savegame << X.count1 << X.count2 << X.count3 << O.count1 << O.count2 << O.count3;
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
			invalid=false;
			convertIndex(alpha,num,invalid);
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

void displayStatus() //Display player score and player turn.
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
	if (totalscore == 64 || !canproceed){ 
		//1.If game is completely filled, game ends.
		//2.In the event where game is not possible to continue, game ends.
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
	cout  << "In game instructions:\nTo input into the game board, type in the format of (A-H, 1-8).\n" 
		  << "For example ==> f 4\n";
	cout  << "\nOther available commands in-game are:\n"
		  << "==> menu (Back to menu and resets the game)\n"
		  << "==> next player (Forfeit your turn)\n"
		  << "==> save (Save the game and load it later)\n"
		  << "==> super1 (Place your move ANYWHERE)\n"
		  << "==> super2 (Two consecutive turns)\n"
		  << "==> super3 (Clear a random row)\n\n";
	cout  << "Spaces that already contain a X or O cannot be inputted again, once the \ngame board is fully filled,"
		  << " or no possible inputs are available, the game \nwill display the winner and return to the game menu.\n\n";
	cout  << "A star '*' will be shown on the screen, to note the players where to input \ntheir markers.\n"
		  << "A *beep* sound will be made for every invalid input.\n\n";
	system("pause"); //Pause 
}

void convertIndex(char& alpha, int& num, bool& invalid) 
//Convert into array readable numbers, since user input (F,5) are (5,3) in terms of array positions.
{
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

void validateMove(int right, int left){ //Checks if move is valid
	bool checkpiece = (board[left][right]=='X' || board[left][right]=='O');
	bool ori = checkpiece,validmove=false;
	if (X.super1||O.super1){
		checkpiece = true; //Place any where on board, hence ignoring "checkpiece".
	} 
	if (!checkpiece){
		flipping(right, left, validmove);
	} else if (X.super1||O.super1){ //Place any where on board, hence ignoring "checkpiece".
		flipping(right, left, validmove);
		if(X.super1 || O.super1){ 
			if(player){
				SymbolX(left, right);
				player = false;									
			} else{ //O
				SymbolO(left, right);
				player = true;
			}
		} 
	} else {
		cout << "\a";
	}

	if(validmove && !checkpiece){
		if(X.super2 || O.super2){ //Two consecutive inputs
			X.super2 = false;
			O.super2 = false;
			if(player){
				SymbolX(left, right);
			} else{ //O
				SymbolO(left, right);
			} 
		} else {
			if (player){ //X
				SymbolX(left, right);
				player = false;									
			} 
			else{ //O
				SymbolO(left, right);
				player = true;
			}
		}
	} else {
		if (X.super1 || O.super1){
			X.super1 = false;
			O.super1 = false;
		} else {
			cout << "\a";
		}
	}
}

void flipping(const int RIGHT, const int LEFT, bool& validmove){ //Flipping on markers
	bool phase1=false,phase2=false;
	const int LEFTINCRE[9] = {-1,-1,-1,0,0,0,1,1,1};
	const int RIGHTINCRE[9] = {-1,0,1,-1,0,1,-1,0,1};
	int leftvalue[9] = {-1,-1,-1,0,0,0,1,1,1};
	int rightvalue[9] = {-1,0,1,-1,0,1,-1,0,1};
	char sym;
	
	if (player)
		sym='X';
	else 
		sym='O';

	for(int i=0;i<9;i++){
		phase1=false; phase2=false;
		//Phase 1 start, check if input neighbours are opposite. (EG. If input is X and its neighbour on the right is O, then proceed.)
		if (player){
			if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='O'){
				phase1=true;
			}
		} else {
			if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='X'){
				phase1=true;
			}
		}
		//Phase 2 start, checks for the same marker across opponents marker. (EG. XOO'X' <---). 
		//Ends if a same marker is not found or if the board is empty
		if(phase1){
			while(LEFT+leftvalue[i]>=0 && LEFT+leftvalue[i]<8 && RIGHT+rightvalue[i]>=0 && RIGHT+rightvalue[i]<8){
				leftvalue[i]+=LEFTINCRE[i];
				rightvalue[i]+=RIGHTINCRE[i];
				if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]==' ' || board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='*'){
					break;
				}
				if (board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]==sym){
					phase2=true;
					break;
				}
			}
		}
		//phase2 end
		//phase 3 start, replaces all the marker (in its respective direction).
		if(phase1 && phase2 && !star){
			validmove=true;
			while(!(rightvalue[i]==RIGHTINCRE[i]) || !(leftvalue[i]==LEFTINCRE[i])){
				rightvalue[i] -= RIGHTINCRE[i];
				leftvalue[i] -= LEFTINCRE[i];
				if(player){
					SymbolX(LEFT+leftvalue[i],RIGHT+rightvalue[i]);
				} else {
					SymbolO(LEFT+leftvalue[i],RIGHT+rightvalue[i]);
				}
			}
		} else if (phase1 && phase2 && star){
			validmove=true;
		}
		//phase 3 end
	}
}
void stars(){
	bool validshowstar;
	canproceed=false; //In the event where player doesn't have any valid moves anymore.
	star=true;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			validshowstar=false;
			if (!(board[i][j]== 'X' || board[i][j]== 'O')){ //Only checks for pieces with no markers
				flipping(j,i,validshowstar); //Check for valid input
				if(validshowstar){ //If move will be valid, place a star on that position
					board[i][j]='*';
					canproceed=true;
				} else {
					board[i][j]=' '; //If not valid, place a space to cover the previously placed star.
				}
			}
		}
	}
	star=false;
	return;
}