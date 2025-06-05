# include <iostream>
# include <bits/stdc++.h>
using namespace std;

//------------------- Jump
class Jump{
    
  public:
      int start;
      int end;
      
      Jump(): start(-1), end(-1){}; // def constructor
      Jump(int s , int e): start(s), end(e){};
};

//------------------- Cell
class Cell{
    int val;
  
  public:
      Jump jump;
      // Cell(): val(0){} // u can create default constructor to init the values // ALways defualt default constructor, so u dontdw about values not passing
      Cell(int v): val(v), jump(){};   // init jump aslo
      
      int getValue(){
          return val;
      }
};

//------------------- Dice
class Dice {                    // just like struct
    int face;
    
    public:                     // ensure 
        Dice(int f): face(f){};    // init list (): (), (){} // colon
        
        int getDiceVal(){
            return rand()%face + 1;
        }    
};                              // semi colon

//------------------- Player
class Player {
    
    string name;
    
    public:
        int position;
        Player (string n, int pos): position(pos), name(n) {};
        
        int getPlayerPosition(){return position;}               // use getter
        string getPlayerName(){return name;}
};

//------------------- Board
class Board {
  int size;
  vector<vector<Cell>> cellArr; 
  
  public:  
      Board (int s): size(s){};
      
      void initializeBoard(){
          cellArr.resize(size, vector<Cell>(size, Cell(-1) ));         //VIMP 2D resize // createing ceel type w/o defualt constructor, so create def one || initi cell
          
          for(int i = 0 ; i < size; i++){
              for(int j = 0 ; j < size ; j++){
                  //cout<<i<<" "<<j<<endl;
                  cellArr[i][j] = Cell(10*i + j);
              }
          }
     }
  
      Cell& getCell(int i, int j){
          return cellArr[i][j];                     //VIMP :  return the actual reference, with Cell it will be a copy and u are changing the copy not the real cell 
      }  
};

//------------------- Game 
class Game{
  Dice dice;         // cant init in class (like dice(6)), initi in object construction
  Board board;
  queue<Player> playersQ;
  
  public:
      Game(): dice(6), board(10){};   // init members here
      // add snakes(3) and ladders(5) and add players to queue
      void initializeGame(){
          board.initializeBoard();
          
          int snakes = 3, ladders = 5;
          
          while(snakes){
              int s, e;
              
              s = rand() % 100; // vals in range[0, 99], so row is num/10 and col is num %10
              e = rand() % 100;
              
              if(s > e){
                  board.getCell(s/10, s%10).jump.start = s;                 // 
                  board.getCell(s/10, s%10).jump.end = e;
                  cout<< "placed one snake, start, end"<<s <<" : "<< e<<endl;
                  snakes--;
              }
          }
          while (ladders){
              int s, e;
              
              s = rand() % 100; // vals in range[0, 99], so row is num/10 and col is num %10
              e = rand() % 100;
              
              if(s < e){
                  
                  board.getCell(s/10, s%10).jump.start = s;                 // chnaging actual cell with the help of values
                  board.getCell(s/10, s%10).jump.end = e;
                  cout<< "placed one ladder , start, end"<<s <<" : "<< e<<endl;
                  ladders--;
              }
          }
          
          playersQ.push(Player("Somesh", 0));
          playersQ.push(Player("Ashima", 0));
          playersQ.push(Player("Vidur", 0));
      }
  
      void play(){
        bool winner = false;
          
        while(!winner){
          // get player turn 
          auto& currPlayer = playersQ.front(); playersQ.pop(); 
          auto currPlayerPos = currPlayer.getPlayerPosition();
          
          // roll dice and check final pos after dice roll
          int diceVal = dice.getDiceVal();
          int finalPos = currPlayerPos + diceVal;
          
          // check pos >= 99 winner
          if(finalPos > 99){
             winner = true;
              cout<< "player : "<< currPlayer.getPlayerName()<<" WINS ===============  :) "<<endl;
              return;
          }
          
          auto& currCell = board.getCell(finalPos/10, finalPos%10);         // U can use ref instead of creating new Object (currCell). >> Fast and work <<auto&>>
          
          // check for snakes and ladders at this pos
          if(currCell.jump.start != -1){
              if(currCell.jump.start > currCell.jump.end)
                  cout<< "climbed ladder"<< endl;
              else
                  cout<<"bitten by snake"<<endl;
                  
              finalPos = finalPos + currCell.jump.end - currCell.jump.start;
          }
          
          currPlayer.position = finalPos;
          playersQ.push(currPlayer);
          
        }
      }
  
};

//------------------- MAIN
int main(){
    
    srand(time(NULL));      // use diff seed // should be called once at the start of the main

    Player player1 ("Somesh", 0);
    
    //Board board(10); board.intializeBoard();   // u can pass args to constr or init func, its oki in both cases
    
    Game game;
    game.initializeGame();
    game.play();
    
    return 0;
}