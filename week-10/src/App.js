import React, { useState } from "react";
import Board from "./Board";

function App() {
    var [data, changeData] = useState({ board: makeBoard('e'), activeUser: 'b', lastTurnImpossible: 0, endGameText: ''})

    // Make space for any other modifications to each piece
    var extraClasses = makeBoard('');

    // Update view to show any and all next moves
    let numPossibleMoves = displayNextMoves()


    // Change user or end game if no possible moves
    if (numPossibleMoves === 0 && data.lastTurnImpossible === 1) {
        endGame()
        data.lastTurnImpossible++
    } else if (numPossibleMoves === 0 && data.lastTurnImpossible === 0) {
        data.activeUser = data.activeUser === 'w' ? 'b' : 'w'
        data.lastTurnImpossible = 1
        changeData(data)
    } else if (numPossibleMoves >= 1){
        data.lastTurnImpossible = 0
    }

    // Adds new piece on board
    function addPiece(x, y) {

        // Make sure not overwriting data
        if (data.board[y][x] !== 'e') return;

        // Check to see if it's a valid move
        let captures = checkCapture(x, y, data.activeUser).captures
        if (captures.length === 0) return;


        // Change to add newest piece
        changeCol(x, y, data.activeUser)

        // Color in captured pieces
        for (let piece of captures) {
            changeCol(piece.x, piece.y, data.activeUser)
        }

        // Change player
        let tmpData = JSON.parse(JSON.stringify(data))
        tmpData.activeUser = tmpData.activeUser === 'w' ? 'b' : 'w'
        if (data.endGameText === '') changeData(tmpData)
    }

    // Changes color of given position on board to color
    function changeCol(x, y, col) {
        data.board[y][x] = col;
    }

    // Checks for any captured given pieces, assuming (x, y) is the theoretical piece on the board
    // Returns a list of positions possible and their captured pieces, stored in object form
    function checkCapture(x, y, curColor) {
        let toReturn = {
            x: x,
            y: y,
            captures: []
        }
        let oppColor;
        switch (curColor) {
            case 'w':
                oppColor = 'b'
                break
            case 'b':
                oppColor = 'w'
                break
            default:
                oppColor = undefined
        }

        // Initialize object to hold values
        let nextPiece = {
            x: x,
            y: y,
            color: data.board[y][x],
            update(changeX, changeY) {
                this.x += changeX
                this.y += changeY
                // Validate place on board exists and update color to match
                if (this.y < 0 || this.y > data.board.length-1) {
                    this.color = undefined
                } else {
                    this.color = data.board[this.y][this.x]
                }
            }

        }

        let directions = [{ x: -1, y: 1 }, { x: 0, y: 1 }, { x: 1, y: 1 }, { x: -1, y: 0 }, { x: 1, y: 0 }, { x: -1, y: -1 }, { x: 0, y: -1 }, { x: 1, y: -1 }];

        // Loop through each possible direction and find chains
        directions.forEach((direction) => {

             nextPiece.update(direction.x, direction.y)

            // Follow any chains made in current direction
            while (nextPiece.color === oppColor) {
                nextPiece.update(direction.x, direction.y)
            }

            // Exit current loop if chain doesn't end in current color
            if (nextPiece.color !== curColor) {
                // Move nextPiece 'pointer' back to current piece
                nextPiece.x = x
                nextPiece.y = y
                nextPiece.update(0, 0)
                return
            }

            // Move back after going too far one square
            nextPiece.update(-direction.x, -direction.y)

            // Add pieces to current position
            while (nextPiece.x !== x || nextPiece.y !== y) {
                toReturn.captures.push({
                    x: nextPiece.x,
                    y: nextPiece.y
                })
                nextPiece.update(-direction.x, -direction.y)
            }
        })

        return toReturn;
    }

    function displayNextMoves() {
        let colorClass = data.activeUser === 'b' ? ' possible-move-black' : ' possible-move-white';
        let possibleMoves = 0
        data.board.forEach((row, y) => {
            row.forEach((square, x) => {
                if (checkCapture(x, y, data.activeUser).captures.length > 0 && square === 'e') {
                    extraClasses[y][x] += colorClass;
                    possibleMoves++;
                }
            })
        })
        return possibleMoves
    }

    // Initiaizes board matrix
    function makeBoard(fill) {
        let boardState = Array.from(Array(8), () => new Array(8));
        for (let i = 0; i < boardState.length; i++) {
            for (let j = 0; j < boardState[i].length; j++) {
                // e = empty, w = white, b = black
                boardState[i][j] = fill;
            }
        }
        if (fill === 'e') {
                // Set initial positions if making game board
                boardState[3][3] = 'w'
                boardState[3][4] = 'b'
                boardState[4][4] = 'w'
                boardState[4][3] = 'b'
        }
        return boardState
    }

    function endGame() {
        let counts = { b: 0, w: 0}
        data.board.forEach((row, y) => {
            row.forEach((square, x) => {
                switch (square) {
                    case 'b':
                        counts.b++;
                        break;
                    case 'w':
                        counts.w++;
                        break;
                    default:
                }
            })
        })

        if (counts.w === counts.b) {
            data.endGameText = `It was a tie!`
        } else if (counts.w > counts.b) {
            data.endGameText = `White won!`
        } else {
            data.endGameText = `Black won!`
        }
        data.endGameText += `\nWhite: ${counts.w}\nBlack: ${counts.b}`
        changeData(data)
    }


    return (
        <>
            <Board addPiece={addPiece} boardState={data.board} extraClasses={extraClasses}/>
            <h1>{data.endGameText}</h1>
        </>
    )
}

export default App;