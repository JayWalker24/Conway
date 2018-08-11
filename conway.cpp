#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class Board;

class Board{
    private:
        vector<vector<char>> CBoard;
        int Rows;
        int Cols;
    public:
        Board(int numCols, int numRows){
            Rows = numRows;
            Cols = numCols;
        }

        Board(){}

        void initialize(){
            for(int x = 0;x<Rows;x++){
                vector<char> row;
                for(int y = 0;y<Cols;y++){
                    row.push_back('.');
                }
                CBoard.push_back(row);
            }
        }

        void displayBoard(){
            for(vector<char> row:CBoard){
                for(char character:row){
                    cout<<character<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }

        void createState(){
            //generate a random number of cells
            //for thsoe random number of cells generate x and y cordinates
            //assign the cells to those cordinates
            //generate random number between 0 and x * y
            int numCells = rand()%(Rows*Cols)+1;
            for(int cells = 0; cells<numCells;cells++){
                int xLoc = rand()%Rows;
                int yLoc = rand()%Cols;
                CBoard[xLoc][yLoc] = 'O';
            }

        }

        void addBorders(){
            Cols+=2;
            vector<char> topBor;
            vector<char> botBor;
            for(int x = 0; x<Rows;x++){
                topBor.push_back('*');
                botBor.push_back('*');
            }
            CBoard.push_back(topBor);
            CBoard.insert(CBoard.begin(),botBor);

            for(int y = 0; y<Cols;y++){
                CBoard[y].push_back('*');
                CBoard[y].insert(CBoard[y].begin(),'*');
            }

        }

        int countNeighbors(int xLoc, int yLoc){
            int NCount = 0;
            for (int x = -1; x<=1;x++){
                for (int y = -1; y<= 1; y++){
                    if(CBoard[x+xLoc][y+yLoc]=='O'){
                        NCount++;
                    }
                }
            }
            return NCount;
        }

        Board newState(){
            Board nextState(Cols-2,Rows);
            //creates a new board that's the same size and has borders
            nextState.initialize();
            nextState.addBorders();

            //run the COnway logic on each cell
            //copy the new values to the next board
            //repeat process with the new board
            for(int x = 1; x<Rows-1;x++){
                //cout<<"  ";
                for(int y = 1; y<Cols-1;y++){
                    //go through each cell and run the count neighbors helper function
                    //nextState.CBoard[x][y] = CBoard[x][y];
                    int num = this->countNeighbors(x,y);
                    if(CBoard[x][y]=='O'){
                        //cout<<num-1<<" ";
                        num--;
                        if(num<2){
                            nextState.CBoard[x][y] = '.';
                        }
                        if(num==2||num==3){
                            nextState.CBoard[x][y] ='O';
                        }
                        if(num>3){
                            nextState.CBoard[x][y] = '.';
                        }
                    }else{
                        if(num==3){
                            nextState.CBoard[x][y] ='O';
                        }
                        //cout<<num<<" ";
                    }
                    
                }
                //cout<<endl;
            }
             nextState.displayBoard();

            return nextState;
        }

};



int main() {
    srand((int)time(0));
    Board Conway(40,40);
    Conway.initialize();
    Conway.createState();  
    Conway.addBorders(); 
    Conway.displayBoard();
    int cycles = 30;
    while(cycles){
        Board newBoard = Conway.newState();
        Conway = newBoard;
        cycles--;
    }
    getchar();
    return 0;

}