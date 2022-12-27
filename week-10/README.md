# ReactReversi
#### Video Demo: https://youtu.be/F1t4f9MBbqE
#### Description:
This is a small project in which I made my own React.js app without a tutorial or outside help! It neither looks the best nor follows best practices, but I'm still proud of the amount of effort I put in and functionality I got out.

The game of Reversi (or Othello) is simple, each player alternates for a turn. Black goes first. You must place one of your pieces so that it 'captures' an opponents piece. You may capture a piece by sandwitching it between two of your pieces. This version will handle all possible moves for you. If you have no legal moves, your turn is skipped. The game ends when neither player has a legal move or the board is filled.

#### /src/index.js
Uses React.js to push forward App.js into the DOM and HTML

#### /src/App.js
The main functional component of the app. App.js has multiple functions whose descriptions are listed below;

##### addPiece()
This function is called to add anohter piece to the board, representing a player making a move. `BoardSquare` components will trigger this function when they are clicked.

###### changeCol()
This function simply changes data in the `data.board` object to reflect the new color. I made a function to do this because `data.board` holds values at `[y][x]` and I wanted to be able to write in proper ordered pair form of `(x, y)` as well as be more verbose in my code.

###### checkCapture()
This function checks to see what captures would be made if a piece on the board chaged to a different color. It returns an object containing the x and y values of the origional spot as well as a `captures` array of the ordered pairs which would be captured. If no pieces would be captured, `checkCaptures(x, y, col).captures` is an empty array. This function is used both when a new piece is placed and to render all possible moves.

###### displayNextMoves()
This function adds classes to all `BoardSquare` components which are legal moves for the current player. CSS then uses these classes to shade in those squares.

###### makeBoard()
Initializes an 8x8 matrix to hold board values. If all spots are initialized wiht an 'e' forempty squares, the function will also add corresponding starting values for the game.

###### endGame()
Ends the game, stops React from rendering, and displays the winner.

#### /src/Board.js
Creates an HTML table for each element to be placed into. Mainly just a rendering component that passes classes and information into `BoardSquare` components

#### /src/BoardSquare.js
The component holding all buttons for possible piece placements. The main purpose of this element is to hold classes and trigger events.

#### /src/styles.css
A Cascading Style Sheet file to make the page look (slightly) less abhorent.

#### /node_modules
All files related to installed packages via npm and neccesary for React to function.

#### package.json and package-lock.json
Metadata and library managemnt constructed by npm.