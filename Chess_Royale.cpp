#include<iostream>
using namespace std;

class GamePiece
{
    private:
    virtual bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) = 0;
    char myPieceColor;
     
public:
    GamePiece(char pieceColor) : myPieceColor(pieceColor) {}
    ~GamePiece() {}
    virtual char getPiece() = 0;
    char getColor() {
        return myPieceColor;
    }
   
    bool isLegalMove(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        GamePiece* Dest = gameBoard[destRow][destCol];
        if ((Dest == 0) || (myPieceColor != Dest->getColor())) {
            return areSquaresLegal(srcRow, srcCol, destRow, destCol, gameBoard);
        }
        return false;
    }

};

class Pawn : public GamePiece
{
public:
    Pawn(char pieceColor) : GamePiece(pieceColor) {}
    ~Pawn() {}
private:
    virtual char getPiece() {
        return 'P';
    }
  
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        GamePiece* Dest = gameBoard[destRow][destCol];
        if (Dest == 0) {
            // Destination square is unoccupied
            if (srcCol == destCol) {
                if (getColor() == 'W') {
                    if (destRow == srcRow + 1) {
                        return true;
                    }
                    else if(srcRow==1&&destRow==srcRow+2&&gameBoard[srcRow+1][srcCol]==0){
                        return true;
                    }
                } else {
                    if (destRow == srcRow - 1) {
                        return true;
                    }
                    else if(srcRow==6&&destRow==srcRow-2&&gameBoard[srcRow-1][srcCol]==0){
                        return true;
                    }
                }
            }
        } else {
            // Destination square is occupied and holds piece of opposite color
            if ((srcCol == destCol + 1) || (srcCol == destCol - 1)) {
                if (getColor() == 'W') {
                    if (destRow == srcRow + 1) {
                        return true;
                    }
                } else {
                    if (destRow == srcRow - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Knight : public GamePiece
{
public:
    Knight(char pieceColor) : GamePiece(pieceColor) {}
    ~Knight() {}
private:
    virtual char getPiece() {
        return 'N';
    }
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((srcCol == destCol + 1) || (srcCol == destCol - 1)) {
            if ((srcRow == destRow + 2) || (srcRow == destRow - 2)) {
                return true;
            }
        }
        if ((srcCol == destCol + 2) || (srcCol == destCol - 2)) {
            if ((srcRow == destRow + 1) || (srcRow == destRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class Bishop: public GamePiece
{
public:
    Bishop(char pieceColor) : GamePiece(pieceColor) {}
    ~Bishop() {}
private:
    virtual char getPiece() {
        return 'B';
    }
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        if (abs(destCol - srcCol) == abs(destRow - srcRow)) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            int checkRow;
            int checkCol;
            for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset;
                checkRow !=  destRow;
                checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
            {
                if (gameBoard[checkRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Rook : public GamePiece
{
public:
    Rook(char pieceColor) : GamePiece(pieceColor) {}
    ~Rook() {}
private:
    virtual char getPiece() {
        return 'R';
    }
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        if (srcRow == destRow) {
            // Make sure that all invervening squares are empty
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            for (int checkCol = srcCol + colOffset; checkCol !=  destCol; checkCol = checkCol + colOffset) {
                if (gameBoard[srcRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (destCol == srcCol) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            for (int checkRow = srcRow + rowOffset; checkRow !=  destRow; checkRow = checkRow + rowOffset) {
                if (gameBoard[checkRow][srcCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Queen : public GamePiece
{
public:
    Queen(char pieceColor) : GamePiece(pieceColor) {}
    ~Queen() {}
private:
    virtual char getPiece() {
        return 'Q';
    }
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        if (srcRow == destRow) {
            // Make sure that all invervening squares are empty
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            for (int checkCol = srcCol + colOffset; checkCol !=  destCol; checkCol = checkCol + colOffset) {
                if (gameBoard[srcRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (destCol == srcCol) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            for (int checkRow = srcRow + rowOffset; checkRow !=  destRow; checkRow = checkRow + rowOffset) {
                if (gameBoard[checkRow][srcCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((destCol - srcCol == destRow - srcRow) || (destCol - srcCol == srcRow - destRow)) {
            // Make sure that all invervening squares are empty
            int rowOffset = (destRow - srcRow > 0) ? 1 : -1;
            int colOffset = (destCol - srcCol > 0) ? 1 : -1;
            int checkRow;
            int checkCol;
            for (checkRow = srcRow + rowOffset, checkCol = srcCol + colOffset;
                checkRow !=  destRow;
                checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
            {
                if (gameBoard[checkRow][checkCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class King : public GamePiece
{
public:
    King(char pieceColor) : GamePiece(pieceColor) {}
    ~King() {}
private:
    virtual char getPiece() {
        return 'K';
    }
    bool areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol, GamePiece* gameBoard[8][8]) {
        int rowDelta = abs(destRow - srcRow);
        int colDelta = abs(destCol - srcCol);
        if ((rowDelta <= 1) && (colDelta <= 1))
        {
            return true;
        }
        return false;
    }
};

class Board{
    public:
    GamePiece *gameBoard[8][8];
    Board(){
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
               gameBoard[row][col]=0; 
        }
    }  

    // Allocating Black pieces
    for(int col=0;col<8;col++){
    gameBoard[6][col]=new Pawn('B');
    }

    gameBoard[7][0]=new Rook('B');
    gameBoard[7][1]=new Knight('B');
    gameBoard[7][2]=new Bishop('B');
    gameBoard[7][3]=new King('B');
    gameBoard[7][4]=new Queen('B');
    gameBoard[7][5]=new Bishop('B');
    gameBoard[7][6]=new Knight('B');
    gameBoard[7][7]=new Rook('B');

    // Allocating White pieces
    for(int col=0;col<8;col++){
    gameBoard[1][col]=new Pawn('W');
    }
    gameBoard[0][0]=new Rook('W');
    gameBoard[0][1]=new Knight('W');
    gameBoard[0][2]=new Bishop('W');
    gameBoard[0][3]=new King('W');
    gameBoard[0][4]=new Queen('W');
    gameBoard[0][5]=new Bishop('W');
    gameBoard[0][6]=new Knight('W');
    gameBoard[0][7]=new Rook('W');
    } 

    ~Board(){
    for(int row=0;row<8;row++){
       for(int col=0;col<8;col++){
       delete gameBoard[row][col];
       gameBoard[row][col]=0; 
          }
      }    
  }

void print(){
    cout<<endl;
cout<<"                                                 ";
    cout<<" ________________________________"<<endl;
    const int keyRow=3;
    const int keyCol=4;

    for(int row=0;row<8*keyRow;row++){
        int squareRow=row/keyRow;

        //Print Side Border Alphabetically.
        if(row%3==1){
        cout<<"                                              ";
        cout<<"-"<<(char)('a'+7-squareRow)<<"-|";
        }
        else{
        cout<<"                                              ";
        cout<<"---|";
        }
      
        //Printing the ChessBoard.
        for(int col=0;col<8*keyCol;col++){
        int squareCol=col/keyCol;
        if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2) && gameBoard[7-squareRow][squareCol] != 0) {
                    if((col % 4) == 1){
                        cout << gameBoard[7-squareRow][squareCol]->getColor();
                    }else{
                        cout << gameBoard[7-squareRow][squareCol]->getPiece();
                    }
                }else{
                    if((squareRow + squareCol) % 2 == 1){
                        cout << '#';
                    }else{
                        cout << ' ';
                    }
                }
        }
           cout<<"|";
           cout<<endl;
    }

    cout<<"                                                 ";
    cout<<"|________________________________|"<<endl;

    //Printing Bottom border Alphabetically.
    for (int row= 0; row < keyRow; row++){
            if (row% 3 == 1){
                cout<<"                                                 ";
                cout<< "--";
                for (int col = 0; col < 8*keyCol; col++) {
                    int squareCol = col/keyCol;
                    if((col % 4) == 1){
                        cout << (squareCol + 1);
                    }else{
                        cout <<'-';
                    }
                }
                cout << endl;
            }else{
                cout<<"                                                 ";
                for (int col = 1; col < 9*keyCol-1; col++) {
                    cout<<'-';
                }
                cout << endl;
            }
        }
}

bool isInCheck(char pieceColor){
        int kingRow;
        int kingCol;
        //Finding King's row and column.
        for (int Row = 0;Row < 8;Row++) {
            for (int Col = 0; Col < 8; Col++) {
                if (gameBoard[Row][Col] != 0) {
                    if (gameBoard[Row][Col]->getColor() == pieceColor) {
                        if (gameBoard[Row][Col]->getPiece() == 'K') {
                            kingRow = Row;
                            kingCol = Col;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int Row = 0; Row < 8; ++Row) {
            for (int Col = 0; Col < 8; ++Col) {
                if (gameBoard[Row][Col] != 0) {
                    if (gameBoard[Row][Col]->getColor() != pieceColor) {
                        if (gameBoard[Row][Col]->isLegalMove(Row, Col, kingRow, kingCol, gameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
}
bool canMove(char pieceColor){
for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
         if(gameBoard[row][col]!=0){
            //If it is a piece of the current player see, if it has a legal move.
            if(gameBoard[row][col]->getColor()==pieceColor){
              for(int moveRow=0;moveRow<8;moveRow++){
                for(int moveCol=0;moveCol<8;moveCol++){
                 if(gameBoard[row][col]->isLegalMove(row,col,moveRow,moveCol,gameBoard)){
                    //Make move and check if King is in check.
                    GamePiece *temp=gameBoard[moveRow][moveCol];
                    gameBoard[moveRow][moveCol]=gameBoard[row][col];
                    gameBoard[row][col]=0;
                    bool bcanMove=isInCheck(pieceColor);
                    //Undo the move
                    gameBoard[row][col]= gameBoard[moveRow][moveCol];
                     gameBoard[moveRow][moveCol]=temp;
                     if(bcanMove==false){
                        return true;
                     }
                 }
                }
              }
            }
         }
    }
}
return false;
}
};

class ChessBoard{
    private:
    Board myGameBoard;
    char myPlayerTurn;
public:
    ChessBoard() : myPlayerTurn('W') {}
    ~ChessBoard() {}

    void start() {
        do {
            getNextMove(myGameBoard.gameBoard);
            alternateTurn();
        } while (!isGameOver());
        myGameBoard.print();
    }

    void getNextMove(GamePiece* gameBoard[8][8]) {
   
        bool bValidMove = false;
        do {
            myGameBoard.print();
            cout << myPlayerTurn << "'s Move :- "<<endl;

            cout<<"Do you want to know possible moves of any piece ? (y/n) : ";
            char ask;
            cin>>ask;
              while(ask=='y'){
                 cout<<"Enter the location of piece whose possible moves you want to know :- "<<endl;
                 int askedRow,askedCol;
                 cout<<"Row : ";
                    char tempRow;
                    cin>>tempRow;
                    askedRow=tempRow-'a';
                    cout<<"Column : ";
                    cin>>askedCol;

                    // Find Possibilities
                   possibilities(askedRow,askedCol,myPlayerTurn,gameBoard);

                   cout<<"Do you want to know possible moves of any other piece ? (y/n) : ";
                   cin>>ask;
              }

            // Get input and convert to coordinates
            cout<<"                            ------------------- ENTER YOUR MOVE -------------------"<<endl;

            cout<<"FROM :- ";
            char sRow;
            cout<<"iROW : ";
            cin >> sRow;
            int startRow=sRow-'a';
            int startCol;
            cout<<"        iCOL : ";
            cin>>startCol;
            startCol--;
            cout << "TO   :- ";
            char eRow;
            int endCol;
            cout<<"fROW : ";
            cin >> eRow;
            int endRow=eRow-'a';
            cout<<"        fCOL : ";
            cin>>endCol;
            endCol--;
        
            // Check that the indices are in range
            // and that the source and destination are different
            if ((startRow >= 0 && startRow <= 7) &&
                (startCol >= 0 && startCol <= 7) &&
                (endRow >= 0 && endRow <= 7) &&
                (endCol >= 0 && endCol <= 7)) {
                // Additional checks in here
                GamePiece* currPiece = gameBoard[startRow][startCol];
                // Check that the piece is the correct color
                if ((currPiece != 0) && (currPiece->getColor() == myPlayerTurn)) {
                    // Check that the destination is a valid destination
                    if (currPiece->isLegalMove(startRow, startCol, endRow, endCol, gameBoard)) {
                        // Make the move
                        GamePiece* Temp               = gameBoard[endRow][endCol];
                        gameBoard[endRow][endCol]     = gameBoard[startRow][startCol];
                        gameBoard[startRow][startCol] = 0;

                        // Make sure that the current player is not in check
                        if (!myGameBoard.isInCheck(myPlayerTurn)) {
                           
                            if(gameBoard[endRow][endCol]->getColor()=='W'&&endRow==7&&gameBoard[endRow][endCol]->getPiece()=='P'){
                                gameBoard[endRow][endCol]=0;
                                cout<<"Congrats now convert your pawn"<<endl;
                                cout<<"Type Q for Queen"<<endl;
                                  cout<<"Type R for Rook"<<endl;
                                    cout<<"Type B for Bishop"<<endl;
                                      cout<<"Type N for Knight"<<endl;
                                      cout<<"if you type anything beyond them then you will get Rook"<<endl;
                                      char newPiece;
                                      cin>>newPiece;
                                      if(newPiece=='Q'){
                                      gameBoard[endRow][endCol]=new Queen('W');}
                                      else if(newPiece=='N'){
                                      gameBoard[endRow][endCol]=new Knight('W');}
                                      else if(newPiece=='B'){
                                      gameBoard[endRow][endCol]=new Bishop('W');}
                                      else{
                                      gameBoard[endRow][endCol]=new Rook('W');}
                            }
                            if(gameBoard[endRow][endCol]->getColor()=='B'&&endRow==0&&gameBoard[endRow][endCol]->getPiece()=='P'){
                                gameBoard[endRow][endCol]=0;
                                cout<<"Congrats now convert your pawn"<<endl;
                                cout<<"Type Q for Queen"<<endl;
                                  cout<<"Type R for Rook"<<endl;
                                    cout<<"Type B for Bishop"<<endl;
                                      cout<<"Type N for Knight"<<endl;
                                      cout<<"if you type anything beyond them then you will get Rook"<<endl;
                                      char newPiece;
                                      cin>>newPiece;
                                      if(newPiece=='Q'){
                                      gameBoard[endRow][endCol]=new Queen('B');}
                                      else if(newPiece=='N'){
                                      gameBoard[endRow][endCol]=new Knight('B');}
                                      else if(newPiece=='B'){
                                      gameBoard[endRow][endCol]=new Bishop('B');}
                                      else{
                                      gameBoard[endRow][endCol]=new Rook('B');}
                            }
                             delete Temp;
                            bValidMove = true;
                        } else { // Undo the last move
                            gameBoard[startRow][startCol] = gameBoard[endRow][endCol];
                            gameBoard[endRow][endCol]     = Temp;
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "                                                           * INVALID MOVE! *" << endl;
            }
        } while (!bValidMove);
    }
    void possibilities(int row,int col,char myPlayerTurn,GamePiece* gameBoard[8][8]){
        int flag=0;
        col--; 
        GamePiece *location=gameBoard[row][col];
        if(row>=8||row<0||col<0||col>=8||gameBoard[row][col]==0||location->getColor()!=myPlayerTurn){
            cout<<"Invalid Demand"<<endl;
            return;
        }  
             for(int tempRow=0;tempRow<8;tempRow++){
                for(int tempCol=0;tempCol<8;tempCol++){
                if(location->isLegalMove(row,col,tempRow,tempCol,gameBoard)==true){
                      GamePiece* Temp               = gameBoard[tempRow][tempCol];
                        gameBoard[tempRow][tempCol]     = gameBoard[row][col];
                        gameBoard[row][col] = 0;
                        if(myGameBoard.isInCheck(myPlayerTurn)==false){
                          cout<<char(tempRow+'a')<<" "<<(tempCol+1)<<" / ";
                          flag=1;
                        }
                        gameBoard[row][col] = gameBoard[tempRow][tempCol];
                            gameBoard[tempRow][tempCol]     = Temp;
                   
                }
            }
        }
        if(!flag) cout<<"No possible moves, try another piece!"<<endl;
      cout<<endl;
    }
    void alternateTurn() {
        myPlayerTurn = (myPlayerTurn == 'W') ? 'B' : 'W';
    }

    bool isGameOver() {
        // Check that the current player can move
        // If not, we have a stalemate or checkmate
        bool bCanMove=false;
        bCanMove = myGameBoard.canMove(myPlayerTurn);
        if (!bCanMove) {
            if (myGameBoard.isInCheck(myPlayerTurn)) {
                alternateTurn();
                cout << "Checkmate, " << myPlayerTurn << "WINS!" <<endl;
            } else {
                cout << "Stalemate, " <<"Game ends on a TIE."<<endl;
            }
        }
        return !bCanMove;
    }

};
int main(){
     cout<<endl<<"                                                       ************************"<<endl;
     cout<<"                                                       ***** CHESS ROYALE *****";
     cout<<endl<<"                                                       ************************"<<endl;
            cout<<"Symbols used :-"<<endl;
            cout<<"1). # = white space"<<endl;
            cout<<"2). Blank space = black space"<<endl;
            cout<<"3). WP = White pawn   & BP = Black pawn"<<endl;
            cout<<"4). WN = White Knight & BN = Black Knight"<<endl;
            cout<<"5). WB = White Bishop & BB = Black Bishop"<<endl;
            cout<<"6). WR = White Rook   & BR = Black Rook"<<endl;
            cout<<"7). WQ = White Queen  & BQ = Black Queen"<<endl;
            cout<<"8). WK = White King   & BK = Black King"<<endl<<endl;
            cout<<"Rule : Move by selecting initial row & column to final desired row & column"<<endl;
ChessBoard myGame;
myGame.start();
}
