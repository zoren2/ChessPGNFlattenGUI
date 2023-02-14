#pragma once

#include <string>
#include <vector>
#include <regex>
#include <algorithm>

class Moves
{
public:

    Moves();
    ~Moves();

    std::string move_notation;
    std::string white_move;
    std::string black_move;

    // Function to parse PGN string into vector of moves
    static std::string parse_pgn(const std::string& pgn);
    static std::vector<std::string> split(const std::string str, const std::string regex_str);
    static void replaceAll(std::string& source, const std::string& from, const std::string& to);
};

