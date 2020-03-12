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
#include <string.h>
#include <set>
#include <iostream>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>




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
        throw ServerException("Bad file name");
    } else {
        while (!this->p1_setup_board.eof()) {
            getline(this->p1_setup_board, p1b);
            //cout << p1b << "\n";
            c1++;
        }
        while (!this->p2_setup_board.eof()) {
            getline(this->p2_setup_board, p2b);
            c2++;
        }
        if (c1 != c2 || c1 != board_size || c2 != board_size) {
            //cout << "Error: Player board sizes do not match\n" << "Player 1: " << c1 << "\nPlayer 2: " << c2 << "\nBoard size: " << board_size << "\n";
            throw ServerException("Error board sizes do NOT match -initialize");
        }

        //Set the board size and clear and move position back to beginning
        this->board_size = board_size;
        this->p1_setup_board.clear();
        this->p1_setup_board.seekg(0, ios::beg);
        this->p2_setup_board.clear();
        this->p2_setup_board.seekg(0, ios::beg);
    }
}
Server::~Server() {
}
BitArray2D *Server::scan_setup_board(string setup_board_name){
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    char location;
    string tmp;

    //First check if shots are out of bounds
    if (x >= board_size || y  >= board_size || x < 0 || y < 0) {
        return 0; //Out of bounds
    } else {
        //For each player find shot location
        if (player == 1) {
            for (int row = 0; row <= y; row++) {
                getline(this->p1_setup_board, tmp);
            }
            location = tmp[x];
        } else if (player == 2) {
            for (int row = 0; row <= y; row++) {
                getline(this->p2_setup_board, tmp);
            }
            location = tmp[x];
        } else {
            throw ServerException("Error: Invalid player number -evaluate_shot");
        }
    }
    //Check if location is a miss
    if (location == '_') {
        return -1; //Miss
    } else {
        return 1; //Hit
    }
}


int Server::process_shot(unsigned int player) {
    //File names
    string fInName = "player_" + std::to_string(player) + ".shot.json";
    string fOutName = "player_"+ std::to_string(player) + ".result.json";

    unsigned int x, y;

    ifstream inFile(fInName);
    if (player > MAX_PLAYERS || player <= 0) {
        throw ServerException("Incorrect player number -process_shot");
    } else if (!inFile.good()) {
        return NO_SHOT_FILE;
    } else {
        //Read the archive
        cereal::JSONInputArchive read_archive(inFile); // initialize an archive on the file
        read_archive(x,y); // deserialize the array
        inFile.close(); // close the file
        remove(fInName.c_str());

        int result = evaluate_shot(player, x,y);

        //Write to the result.json
        ofstream outFile(fOutName);
        cereal::JSONOutputArchive write_archive(outFile);
        write_archive(cereal::make_nvp("result", result)); // serialize the data giving it a name
        outFile << "\n}";
        outFile.close(); // close the file
        return SHOT_FILE_PROCESSED;
    }
}