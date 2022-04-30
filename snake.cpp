#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <vector> 
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////
#define wall 219            //ascii code for character wall
#define happyface 2			//ascii code for character snake
#define wfx 0               //wall first place x
#define wfy 0				//wall first place y
#define wlx 41				//wall last place x
#define wly 21            	//wall last place y
#define maxfood 59          //the number of food that shold be eaten for winning
#define body_character '0'	//snake's body character

////////////////////////////////////////////////////////////////////////////////////////////

void gotoxy (int x, int y) {							//usefull functions
static HANDLE h = NULL;
if (!h) {
h = GetStdHandle(STD_OUTPUT_HANDLE);
}
COORD c = {x, y};
SetConsoleCursorPosition(h, c);
}

void sleep (int mili) {									//usefull functions
Sleep(mili);
}

void clearScreen () {									//usefull functions
system("cls");
}

void showConsoleCursor (bool showFlag) {              //usefull functions
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO cursorInfo;
GetConsoleCursorInfo(out, &cursorInfo);
cursorInfo.bVisible = showFlag;
SetConsoleCursorInfo(out, &cursorInfo);
}
/////////////////////////////////////////////////////////////////////////////////////////////// 
class Unit {																						//class Unit
	protected:
		int cfx = 1;				//cursor first place x
		int cfy = 1;				//cursor first place y
		char food_character = '#';  //character of food
		int xfood;					//place of food x
		int yfood;					//place of food y
		vector <int> px;			//x place for length of snake's body
		vector <int> py;			//y place for length of snake's body
		char sb[60];				//how many snake body made 
		int ef;						//number of eaten food
		int testfood;				//test for that the food cout on snake's body or not
		
		
		void printWalls();
		void increaseSnakeLenght();
};
///////////////////////////////////////////////////////////////////////////////////////////////
void Unit::printWalls(){
	for(int i = wfx ; i <= wlx ; i = i + 1){
		gotoxy(i,0);
		cout << (char)wall;
		}
	for(int i = wfy ; i <= wly ; i = i + 1){
		gotoxy(0,i);
		cout << (char)wall;
		}
	for(int i = wfy ; i <= wly ; i = i + 1){
		gotoxy(wlx,i);
		cout << (char)wall;
		}
	for(int i = wfx ; i <= wlx ; i = i + 1){
		gotoxy(i,wly);
		cout << (char)wall;
		}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Unit::increaseSnakeLenght(){
	if(px.size() <= maxfood){
		px.push_back(cfx);
		py.push_back(cfy);
	}
	else{
		for(int i = 0;i < maxfood;i = i + 1){
			px[i] = px[i + 1];
			py[i] = py[i + 1];
		}
		px[maxfood] = cfx;
		py[maxfood] = cfy;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
class Snake : protected Unit{																		//class Snake
	private:
		void movePlayer(int ch2);
		int validPress(int a,int b);
		void newFood();
		void showOrHideFood();
		void snake_speed(int a);
		int win_check(int a);
		int eating_own_body_test();
	public:	
		void execute();
};
///////////////////////////////////////////////////////////////////////////////////////////////////
void Snake::movePlayer(int ch2){
			if(ch2 == 80){
						gotoxy(cfx,cfy);
						cout<<" ";
						cfy = cfy + 1;
						gotoxy(cfx,cfy);
						cout<<(char)2;
						
			}else if(ch2 == 72){
						gotoxy(cfx,cfy);
						cout<<" ";
						cfy = cfy - 1;
						gotoxy(cfx,cfy);
						cout<<(char)2;
	
			}else if(ch2 == 75){
						gotoxy(cfx,cfy);
						cout<<" ";
						cfx = cfx - 1;
						gotoxy(cfx,cfy);
						cout<<(char)2;
						
			}else if(ch2 == 77){
							gotoxy(cfx,cfy);
							cout<<" ";
							cfx = cfx + 1;
							gotoxy(cfx,cfy);
							cout<<(char)2;
			}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int Snake::validPress(int a,int b){
	switch(a){
		
		case 80:
			if(b == 75 || b == 77){
				a = b;
			}else{
				a = 80;
			}
			return a;
			break;
		
		case 72:
			if(b == 75 || b == 77){
				a = b;
			}else{
				a = 72;
			}
			return a;
			break;
		
		case 75:
			if(b == 72 || b == 80){
				a = b;
			}else{
				a = 75;
			}
			return a;
			break;
		
		case 77:
			if(b == 72 || b == 80){
				a = b;
			}else{
				a = 77;
			}
			return a;
			break;		
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Snake::newFood(){
	srand(time(0));
	xfood = (rand() % (wlx - 1)) + 1;
	yfood = (rand() % (wly - 1)) + 1;
	gotoxy(xfood,yfood);
	cout<<food_character;
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Snake::showOrHideFood(){
	if(cfx == xfood && cfy == yfood){
		ef = ef + 1;
		sb[ef-1] = 'o';
		testfood = 1;
		while(testfood != 0){
			newFood();
			int counter = 0;
			if(px.size() >= 1){
				for(int i = 1;i <= px.size();i = i + 1){
				if(xfood == px[px.size()-i] && yfood == py[py.size()-i] && sb[i - 1] == 'o'){
					
					break;
				}else{
					counter = counter + 1;
					if(counter == px.size()){
						testfood = 0;
					}
			
				}
			}
		}
		
	
	}
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Snake::snake_speed(int a){																		//snake's speed
	if(a < 20){
			sleep(200);
		}else if( a >= 20 && a < 40){
			sleep(100);
		}else{
			sleep(50);
		}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Snake::win_check(int a){
	if(a == maxfood){
		clearScreen ();
		gotoxy(0,0);
		cout<<"You win!";
		return 0;
	}else{
		return 1;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
int Snake::eating_own_body_test(){
	int counter = 0;
	if(px.size() >= 1){
				for(int i = 1;i <= px.size();i = i + 1){
				if(cfx == px[px.size()-i] && cfy == py[py.size()-i] && sb[i - 1] == 'o'){
					return 0;
					break;
				}else{
					counter = counter + 1;
					if (counter == px.size()){
						return 1;
					}
				}
			}
			}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Snake::execute(){
	printWalls();
	showConsoleCursor(false);
	newFood();
	int ch2 = 77;
	
	
	while(true){
		for(int i = 0;i < 50;i = i + 1){
			gotoxy(xfood,yfood);
			cout<<' ';
			gotoxy(xfood,yfood);
			cout<<' ';
			gotoxy(xfood,yfood);
			cout<<food_character;
		}
		snake_speed(ef);
		increaseSnakeLenght();
		
			
		if(kbhit()){
			int ch1;
			ch1 = getch();
			if (ch1 == 0xE0){
			int ch3 = getch();
			validPress(ch2,ch3);
			ch2 = validPress(ch2,ch3);
				}
			}
			
			movePlayer(ch2);
			if(ef >= 1){
				for(int i = 1;i <= ef;i = i + 1){
					gotoxy(px[px.size()-i],py[py.size()-i]);
					cout<<body_character;
					gotoxy(px[px.size()-i-1],py[py.size()-i-1]);
					cout<<' ';
				}
			}
			
			eating_own_body_test();
			if(eating_own_body_test() == 0){
				clearScreen ();
				gotoxy(0,0);
				cout<<"You lose!";
				break;
			}
			
			if(cfx == wfx || cfy == wfy || cfx == wlx || cfy == wly){
				clearScreen ();
				gotoxy(0,0);
				cout<<"You lose!";
				break;
			}
			
			showOrHideFood();
			
			win_check(ef);
			if(win_check(ef) == 0){
				break;
			}
			
			}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
	Snake s1;
	s1.execute();
	return 0;
}
