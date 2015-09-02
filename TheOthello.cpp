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
#include <fstream> //Save and load file
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
void flipping(int,int,bool&);
void calcStatus(int&, int&);
void convertIndex(char&, int&, bool&);
void stars();//Stars on board to show valid inputs
bool player = true,done=false,star=false,passed=false,description,saved=false,canproceed,wronginput=false; 
//Player - True for player X, false for player Y. Default first player will be X.
//canproceed - If no more valid move, return false and done=true.
string line(50, '-'); //Used on banner
char board[8][8]; //Initialize (Multidimensional Array) Serves as the game board on screen.
int totalscore=0; //If totalscore is 64 which is all the possible input spaces available, means the game has ended.

class SPower{
public:
	bool super1,super2,super3;
	bool count1,count2,count3,error1,error2,error3,rands;
	void init(){ //Initialize
		count1 = false, count2 = false,count3 = false;
		error1=false,error2=false,error3=false;
		super1 = false,super2 = false,super3 = false;
	}
	void S1(){ //Super power 1
		if (!count1){
			super1 = true;
			count1=true; //ONE TIME ONLY
		} else{
			error1 = true;
			cout << "\a";
		}
	}
	void S2(){ //Super power 2
		if (!count2){
			super2 = true;
			count2=true; //ONE TIME ONLY
		} else{
			error2 = true;
			cout << "\a";
		}
	}
	void S3(){ //Super power 3
		if (!count3){
			super3 = true;
			count3=true; //ONE TIME ONLY
		} else{
			error3 = true;
			cout << "\a";
		}	
	}
	void supertwo(){
		if(super2){
			srand(time(NULL));
			int ran = rand()%8;
			for(int i=0;i<8;i++){ //Clear a random row
				if(ran+i <= 7)
					if(player)
						board[ran+i][i] = 'X';
					else
						board[ran+i][i] = 'O';
			}
			switchplayer();
		}
	}
	void superthree(){ 
		if(super3){
			srand(time(NULL));
			int ran = rand()%8; //0-7
			for(int i=0;i<8;i++){ //Clear a random row
				board[ran][i] = ' ';
			}
			switchplayer();
		}
	}
	void powerdescription(){
		if(super1){
			if(description){
				cout << "\tSuper power 1!";
				description=false;
			}else{
				cout << "\tYou can place ANYWHERE you like!";
				description=true;
			}
		} else if (super2){
			if(description){
				cout << "\tSuper power 2!";
				description=false;
			}else{
				cout << "\tRandom diagonal line generated!";
				super2=false;
				description=true;
			}
		} else if (super3) {
			if(description){
				cout << "\tSuper power 3!";
				description=false;
			}else{
				cout << "\tCleared a random row :P";
				description=true;
				super3 = false;
			}
		}	
	}
	private:
		void switchplayer(){
				if(player)
					player = false;
				else
					player = true;
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
	bool menu=true;
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
			player=true;//Re initialize player back to true.
			menu = false;
			game();
		}
		else if (menu_commands == "2" || menu_commands == "LOAD A GAME"){
			ifstream read;
			read.open("a.txt");
			if(!read.is_open()){
				cout << "==> Save game not found!\n==> ";
				system("pause");
				continue;
			}
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

void calcStatus(int& scoreX, int& scoreO) //Display player score and player turn.
{
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
		//If game is completely filled, game ends.
		done = true;
	}
}

void game(){ //Draws the game board
	char disp,disp2;
	bool showstat=false;
	int counter=0; //If BOTH players have no turns anymore.
	redraw:
	int scoreX=0,scoreO=0;
	calcStatus(scoreX, scoreO);
	description=true;
	cls; 
	banner;
	stars();
	static string gameboard(" |---+---+---+---+---+---+---+---|\n");
	int num=8; //Vertical numbers beside the game board
	for (int i=0;i<=7;i++) { //Draws the game board using for loop
		cout << gameboard; //A string of text declared at line 36
		cout << num-- << "|";
		for(int j=0;j<=7;j++){
			cout << " " << board[i][j] << " |";
		}
		if (done){
			if(num==5){
				if (scoreO < scoreX){
					cout << "\tWinner is player X!";
				} else if (scoreO == scoreX){
					cout << "\tIt is a draw!";
				} else{
					cout << "\tWinner is player O!";
				}
			} else if (num==4){
				cout << "\tCongratulations!";
			}
		} else if (wronginput){
			if(num==5){
				cout << "\t\aInvalid input!";
			} else if (num==4){
				cout << "\tValid places are marked with *";
				wronginput=false;
			}
		} else if (passed){
			if(num==5){
				cout << "\tPassed to next player!";
			} else if (num==4){
				passed=false;
			}
		} else if (X.super1 || X.super2 || X.super3 || O.super1 || O.super2 || O.super3){
			if(num==5){
				X.powerdescription(),O.powerdescription();
			} else if (num==4){
				X.powerdescription(),O.powerdescription();
			}
		} else if (X.error1 || O.error1 || X.error2 || O.error2 || X.error3 || O.error3){
			if(num==5){
				cout << "\tOops, each super power";
			} else if (num==4){
				cout << "\tcan only be used once!";
				X.error1 = false,X.error2 = false,X.error3 = false;
				O.error1 = false,O.error2 = false,O.error3 = false;
			}
		} else if (saved) {
			if(num==5){
				cout << "\tGame saved!" << disp;
			} else if (num==4){
				saved=false;
			}
		} else if (showstat){	
			if(num==5){
				cout << "\t\aNo more valid moves for player " << disp;
			} else if (num==4){
				cout << "\tturn passed to player " << disp2 << "!";
				showstat=false;
			}
		} else {
			if(num == 5){
				cout << "\tPlaces marked with * are";
			} else if (num==4){
				cout << "\tpossible valid inputs.";
			} 
			if (num==1){
				cout << "\tType help for list of commands";
			}
		}
		cout << endl;
	}
	cout << gameboard; //A string of text declared at line 36
	cout << "   a   b   c   d   e   f   g   h"; //Horizontal alphabets below the game board
	cout << "\nScore:\t\tO = " << scoreO << "\tX = " << scoreX << endl;
	if (!done){
		if (player){ //If player is TRUE, then it is player X. Else player O.
			cout << "Current player: X";
		} else
			cout << "Current player: O";
	}	
	if (totalscore !=64  && !canproceed && counter!=2){ 
		//In the event where game is not possible to continue (with board not fully filled), automatically passes to next player.
		if(player){
				disp = 'X', disp2 = 'O';
				player=false;
			}
			else {
				disp = 'O', disp2 = 'X';
				player=true;
		}	
		showstat = true;
		counter++; 
		if(counter==2) //If BOTH players have no turns left, game ends.
			done=true;
		goto redraw; //After passing turn to next player, redraws the map with the stars.
	}
	if(!done){
		ingame_commands();
	} else {
		player = true; //Re initialize player back to true.
		done = false;
		totalscore=0;	//totalscore's value is from displayStatus()
		system("pause");	
		menu();
	}
}
void ingame_commands(){ //GET user input in game
	bool invalid;
	string game_commands;
	cout << endl;
	arrow;
	if (getline(cin, game_commands)){
		for(int i=0; i< game_commands.length(); i++) {
			game_commands[i] = toupper(game_commands[i]); 
			//convert user input into capital letters, so program only have to check for capitalized version of each command.
		}
		if (game_commands == "MENU"){
			menu(); 
		}
		else if (game_commands == "NEXT PLAYER"){
			if (player){ //Flag variable? Switching between players are determined with true and false
				player = false; //False for player Y.
			} else {
				player = true; //True for player X.
			}
			passed=true;
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
			savegame << " \n\n\nThis is intended as a READ-ONLY file, DO NOT EDIT.";
			savegame.close();
			saved=true;
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
				X.supertwo();
			} else {
				O.S2();
				O.supertwo();
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
		} else if (game_commands == "HELP"){
			helpPage();
			game();
		}else {
			istringstream seperate(game_commands); //Seperate input into char and int 
			char alpha;
			int num;
			seperate >> alpha >> num;
			invalid=false;
			convertIndex(alpha,num,invalid);
			if (!invalid){ 
				validateMove(alpha, num);
			} else {
				wronginput=true;
			}
			game();
			//game() function are called to re-draw the game board with the necessary changes by user input	
		}
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
		  << "==> super1 (Place your move ANYWHERE, creates a big X.)\n"
		  << "==> super2 (Generates a diagonal line starting at a random row.)\n"
		  << "==> super3 (Clear a random row)\n\n";
	cout  << "-Spaces that already contain a X or O cannot be inputted again, once the \n game board is fully filled,"
		  << " the game will display the winner and \n return to the game menu.\n"
		  << "-Super powers can only be used once!\n";
	cout  << "-A star '*' will be shown on the screen, to note the players where to input \n their markers.\n"
		  << "-If neither players have any moves left, the game will end.\n"
		  << "-A *beep* sound will be made for every invalid input.\n\n";
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
	} 
	else if (X.super1||O.super1){ //Place any where on board, hence ignoring "checkpiece".
		static int leftz[5] = {0,-1,-1,1,1};
		static int rightz[5] = {0,-1,1,1,-1};
		for(int fivetimes=0;fivetimes<5;fivetimes++){
			if(right+rightz[fivetimes]>=0 && right+rightz[fivetimes]<8 && left+leftz[fivetimes]>=0 && left+leftz[fivetimes]<8){
				flipping(right+rightz[fivetimes], left+leftz[fivetimes], validmove);
				if(player){
					SymbolX(left+leftz[fivetimes],right+rightz[fivetimes]);								
				} else{ //O
					SymbolO(left+leftz[fivetimes],right+rightz[fivetimes]);
				}
			}
		}
		if(player)
			player=false;
		else
			player=true;
	} 
	else {
		wronginput=true;
	}

	if(validmove && !checkpiece){
		if (player){ //X
			SymbolX(left, right);
			player = false;									
		} 
		else{ //O
			SymbolO(left, right);
			player = true;
		}
	} else {
		if (X.super1 || O.super1){
			X.super1 = false;
			O.super1 = false;
		} else {
			wronginput=true;
		}
	}
}

void flipping(const int RIGHT, const int LEFT, bool& validmove){ //Flipping on markers
	bool phase1=false,phase2=false;
	const int LEFTINCRE[8] = {-1,-1,-1,0,0,1,1,1};
	const int RIGHTINCRE[8] = {-1,0,1,-1,1,-1,0,1};
	int leftvalue[8] = {-1,-1,-1,0,0,1,1,1};
	int rightvalue[8] = {-1,0,1,-1,1,-1,0,1};
	char sym;
	if (player)
		sym='X';
	else 
		sym='O';
	for(int i=0;i<8;i++){
		phase1=false; phase2=false;
		//Phase 1 start, check if input neighbours are opposite. (EG. If input is X and its neighbour is O, then proceed.)
		if(LEFT+leftvalue[i]>=0 && LEFT+leftvalue[i]<8 && RIGHT+rightvalue[i]>=0 && RIGHT+rightvalue[i]<8){
			if (player){
				if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='O'){
					phase1=true;
				}
			} else {
				if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='X'){
					phase1=true;
				}
			}
		}
		//Phase 2 start, checks for the same marker across opponents marker. (EG. XOO'X' <---). 
		//False if a same marker is not found or if the board is empty
		if(phase1){
			while(LEFT+leftvalue[i]>=0 && LEFT+leftvalue[i]<8 && RIGHT+rightvalue[i]>=0 && RIGHT+rightvalue[i]<8){
				if(board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]==' ' || board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]=='*'){
					break;
				}
				if (board[LEFT+leftvalue[i]][RIGHT+rightvalue[i]]==sym){
					phase2=true;
					break;
				}
				leftvalue[i]+=LEFTINCRE[i];
				rightvalue[i]+=RIGHTINCRE[i];
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