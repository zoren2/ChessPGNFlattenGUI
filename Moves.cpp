#include "Moves.h"

Moves::Moves()
{
}

Moves::~Moves()
{
}

// Return the string of separate games - perhaps alter original string instead
// wxString conversion to string

/*
 * Algorithm:
 * 
 * If '(' is encountered, it means a new game needs to be populated.
 * If ')' is encountered, pop off contents until '(' is 
 * If ".." is encountered, skip to the next item. It indicates null move from entering a new variation
 * If EOF (Denoted by '*', "1-0", "0-1", or "1/2-1/2") then generate final string
 */
std::string Moves::parse_pgn(const std::string& pgn)
{
    std::regex removeMoveNumber("\\d+\\.");
    std::string returnString;
    returnString = std::regex_replace(pgn, removeMoveNumber, "");
    replaceAll(returnString, ")", " )");
    std::vector<std::string> moveList = split(returnString, " ");

    // Refactor - move into another function, cleans up movelist array if it has empty elements
    for (int i = 0; i < moveList.size(); ++i) {
        if (moveList.at(i) == "") {
            //remove element if empty string
            moveList.erase(moveList.begin() + i);
            --i;
        }
    }

    // Split PGN string into moves by finding each '.' character
    int start = 0;
    for (int i = 0; i < pgn.size(); i++) {
        if (pgn[i] == '.') {
            std::string move = pgn.substr(start, i - start + 1);
            start = i + 1;

            // Split move string into separate white and black moves
            int split = move.find(" ");
            std::string white_move = move.substr(0, split - 1);
            std::string black_move = move.substr(split + 1);

            // Add move to vector of moves
            Moves m;
            m.move_notation = move;
            m.white_move = white_move;
            m.black_move = black_move;
            //moves.push_back(m);
        }
    }
    return returnString;
}

std::vector<std::string> Moves::split(const std::string str, const std::string regex_str)
{
    std::regex regexz(regex_str);
    return { std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
            std::sregex_token_iterator() };
}

void Moves::replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}