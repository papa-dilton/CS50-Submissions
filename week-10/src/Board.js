import React, { Component } from "react";
import BoardSquare from "./BoardSquare";

export default class Board extends Component{
    render() {

        return (
            <>
            <div className='board'><table><tbody>
            {
                this.props.boardState.map((row, rowInd) => {
                    return (
                        <tr key={`r${rowInd}`}>
                            {row.map((square, colInd) => {
                                return <BoardSquare fill={square + this.props.extraClasses[rowInd][colInd]} addPiece={this.props.addPiece} posX={colInd} posY={rowInd} key={`${colInd}e${rowInd}`}/>
                            })}
                        </tr>
                    )
                })
            }
            </tbody></table></div>
            </>
        )
    }
}