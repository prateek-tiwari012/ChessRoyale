# <p align="center">CHESS ROYALE</p> 




## Introduction:
<p 
Chess Royale is an object-oriented C++ based 2-PLAYER chess game that aims to provide an immersive and enjoyable chess-playing experience. The game is designed using object-oriented programming principles to create a modular and extensible structure. 
</p>
<p
         We implement the most popular 2-player game of Chess keeping in mind the object oriented practices of the  C++ .The Base class i.e GamePiece Class has 2 pure virtual functions i.e these functions has to be over-ridden who even extends the base class or else the extending class also becomes the abstract class. getPiece() & areSquaresLegal are 2 virtual functions in the base class . Gamepiece is an abstract class as it has pure virtual functions.
</p>
<p 
         In addition to its C++ implementation and terminal accessibility, Chess Royale stands out with its elegant OOP design, delivering a seamless and intuitive user interface for players to immerse themselves in the strategic depth and tactical challenges of the game. With its refined mechanics and engaging gameplay, Chess Royale is poised to captivate chess enthusiasts and provide countless hours of enjoyment in the digital realm.
</p>

<p align ="center">
<img src="/images/ChessGame.jpg"/ alt="chess-game">
</p> 

## UML DIAGRAM OF THE CLASSES :

<p align ="center">
<img src="/images/UML.jpeg"/ alt="Flowchart to show classes">
</p> 

<p>
The Gamepiece class as two pure virtual functions : getPiece() and areSquaresLegal(). The function getPiece() is overridden by each piece class to return the char that signifies each piece type: 'P' = pawn, 'N' = knight, 'R' = rook, 'B' = bishop, 'Q' = queen, and 'K' = king. The function areSquaresLegal() is overridden to test the source and destination locations versus the movement rules for the particular piece.
</p> 
<p>
               The board is numbered on the left from a to h alphabetically and bottom from 1 to 8 numerically (as shown below) so that locations can be specified with the initial row and column of the piece to move and  a valid final row and column. Valid location is checked by the code , if invalid location is entered then user is prompted to enter once again. Along with this we provide the player with the expected moves of any piece the player wants to know and then the player is asked for the move he want to enter.
</p> 

<p align ="center">
<img src="/images/CHESS_ROYALE.jpg"/ alt="chess board on IDE terminal">
</p> 
<p align ="center">
<img src="/images/CHESS_TERMINAL.jpg"/ alt="chess board on IDE terminal">
</p> 

<p>
The gameBoard is an 8 by 8 array of pointers to piece objects. This is where the polymorphism comes in. Any square can hold any piece or none at all. If we want to know whether a piece can make a certain move, we just pass in the move to the isLegalMove() function in the piece class. Then correct function is called for any of the pieces: pawn, knight, bishop, rook, queen, and king. However, all we know when the function is called is that it is a piece.
</p>

**CONCEPTS OF OOPS USED:**

* **Inheritance** 
* **Polymorphism**
* **Encapsulation** 
* **Abstraction** 
* **Data Hiding** 
* **Polymorphism**
* **Constructor in derived class (specialization)**
* **Virtual base class**
* **Abstract class**
* **Pure virtual function**
* **Visibility modes in Inheritance**

**Installation :**
<p>
Install my-project with any C++ compiler
</p>

**# NOTE : This project is coded in C++ on Vs Code. The user will need any C++ compiler to run this code.**
