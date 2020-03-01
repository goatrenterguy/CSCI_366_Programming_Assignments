//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    std::streampos fSize = 0;
    fSize = file->tellg();
    file->seekg(0, std::ios::end);
    fSize = (file->tellg() - fSize);
    file->close();
    return fSize;

}


void Server::initialize(unsigned int board_size, string p1_setup_board,
                        string p2_setup_board) {
    int c1, c2;
    c1 = -1, c2 = -1;
    this->p1_setup_board.open(p1_setup_board);
    this->p2_setup_board.open(p2_setup_board);
    string p1b, p2b;
    if (!this->p1_setup_board || !this->p2_setup_board) {
        throw "Bad file name";
    } else {}
    while (!this->p1_setup_board.eof()) {
        getline(this->p1_setup_board, p1b);
        c1++;
    }
    while (!this->p2_setup_board.eof()) {
        getline(this->p2_setup_board, p2b);
        c2++;
    }
    if (c1 != c2 || c1 != board_size || c2 != board_size) {
        //cout << "Error: Player board sizes do not match\n" << "Player 1: " << c1 << "\nPlayer 2: " << c2 << "\nBoard size: " << board_size << "\n";
        throw "Error board sizes do NOT match";
    }
    this->board_size = board_size;
}

Server::~Server() {
}


BitArray2D *Server::scan_setup_board(string setup_board_name){
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    char board[board_size][board_size];
    if (x > board_size || y > board_size){
        throw "Error: Shot is out of bounds";
    }
    if (player > MAX_PLAYERS || player < 0) {
        throw "Error: Invalid player number";
    }
    //TODO: Add hit detection

}


int Server::process_shot(unsigned int player) {
   return NO_SHOT_FILE;
}