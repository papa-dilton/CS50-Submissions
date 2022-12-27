import React, { Component } from "react";


export default class BoardSquare extends Component {
    render() {

        return (
            <td><button className={this.props.fill} onClick={() => {this.props.addPiece(this.props.posX, this.props.posY)}}>   </button></td>
        )
    }
}