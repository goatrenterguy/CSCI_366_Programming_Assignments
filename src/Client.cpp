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
#include "Client.hpp"
#include <iostream>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <string>

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    vector<vector<char> > board(board_size, vector<char>(board_size, 0));
    string fname = "player_"+ std::to_string(player)+".action_board.json";
    this->board_size = board_size;
    this->player = player;
    initialized = true;
    ofstream file(fname);
    cereal::JSONOutputArchive write_archive(file);
    write_archive(cereal::make_nvp("board", board)); // serialize the data giving it a name
    file << "\n}";
    file.close(); // close the file

}


void Client::fire(unsigned int x, unsigned int y) {
    string fname = "player_"+ std::to_string(player)+".shot.json";
    remove(fname.c_str());
    ofstream shot_file(fname);
    cereal::JSONOutputArchive write_archive(shot_file);
    write_archive(cereal::make_nvp("x", x),cereal::make_nvp("y", y)); // serialize the data giving it a name
    shot_file << "\n}";
    shot_file.close();
}


bool Client::result_available() {
    string fname = "player_"+ std::to_string(player)+".result.json";
    ifstream file(fname);
    if (file) {
        file.close();
        return 1;
    } else {
        file.close();
        return 0;
    }
}


int Client::get_result() {
    int result = 0;
    string fname = "player_"+ std::to_string(player)+".result.json";
    ifstream result_file(fname);
    cereal::JSONInputArchive read_archive(result_file);
    read_archive(result);
    remove(fname.c_str());
    if (result > 1 || result < -1) {
        result_file.close();
        throw ClientException("Bad Result");
    } else {
        result_file.close();
        return result;
    }
}

void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    vector<vector<int> > ab(board_size, vector<int>(board_size));
    string fileName = "player_"+ std::to_string(player)+ ".action_board.json";
    ifstream abInFile(fileName);
    cereal::JSONInputArchive read_archive(abInFile);
    read_archive(ab);
    abInFile.close();
    remove(fileName.c_str());
    ab[x][y] = result;
    ofstream abOutfile(fileName);
    cereal::JSONOutputArchive write_archive(abOutfile);
    write_archive(cereal::make_nvp("board", ab)); // serialize the data giving it a name
    abOutfile << "\n}";
    abOutfile.close(); // close the file

}


string Client::render_action_board(){
    string fname = "player_"+ std::to_string(player)+".action_board.json";
    vector<vector<char> > board(board_size, vector<char>(board_size));
    string boardString;
    ifstream f(fname);
    cereal::JSONInputArchive read_archive(f);
    read_archive(board);
    f.close();
    std::stringstream ss;
    ss << f.rdbuf();
    boardString = ss.str();
    return boardString;
}