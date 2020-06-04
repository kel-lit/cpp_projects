#include <iostream> 
#include <vector>
#include "clear_console.h"

class Slot{
    //Using a class here for each slot is unnecessary and uses more memory than needed, but I just wanted to practice this.
    bool empty = true;
    char display;
    int position;

    public:

        Slot(int position){
            this->position = position;
        }

        void insert_piece(char piece){
            empty = false;
            display = piece; 
        }

        char get_piece(){

            if (empty){
                return ' ';
            }
            else {
                return display;
            }
        }
};

class Board{

    int pieces = 0;
    int size_x = 7;
    int size_y = 6;
    int board_size = size_x * size_y;
    std::vector<Slot> board;

    public:
        Board(){
            //Initialse board
            for (int i=0; i < board_size; i++){
                board.push_back(Slot(i));
            }
        }

        void size(){
            std::cout << board.size();
        }

        void draw_board(){

            std::cout << ' ';
            for (int i; i < size_x; i++){
                std::cout << i+1 << ' ';
            }

            std::cout << std::endl << '|';

            for (int j; j <= board.size(); j++){
                std::cout << board[j].get_piece() << '|';
                if (j % size_x == 0 && j != board.size()){
                    std::cout << std::endl << '|';
                }
            }
            std::cout << std::endl;
        }

        int check_y(int position){
            //We want to check that there is space vertically for the piece.
            int cursor = board_size - ((size_x - 1) - position);
            while (cursor > 0){
                if (board[cursor].get_piece() == ' '){
                    return cursor; 
                }
                cursor -= size_x; //Move up on the y-axis
            }
            return -1;
        }

        bool check_line(int direction, int position, char type, int offset){
            // Direction 0-7 (n, ne, e, se, s, sw, w, nw)

            int n = -(size_x * offset);
            int e = -offset;
            int s = size_x * offset;
            int w = offset;

            int ne = -((size_x * offset) - offset);
            int se = (size_x * offset) + offset;
            int sw = (size_x * offset) - offset;
            int nw = -((size_x * offset) + offset);

            int directions[8] = {n, e, s, w, ne, se, sw, nw}; //n, e, s, w, ne, se, sw, nw

            char directional_offset_piece = board[position + directions[direction]].get_piece();

            if (directional_offset_piece == type){
                if (offset == 1){
                    return true;
                }
                else {
                    return check_line(direction, position, type, --offset);
                }
            }
            return false;
        }

        bool check_for_win(int position, char type){
            
            bool won;
            
            if (pieces < 7){
                return false;
            }

            for (int i; i < 8; i++){
                won = check_line(i, position, type, 3);
                if (won){
                    return true;
                }
            }
            return false;
        }

        int place_marker(char piece, int position){
            
            position--; //User-supplied position starts at 1. 

            if(position > size_x){
                return false;               
            }
            else{
                int lowest_free_y = check_y(position);
                if (lowest_free_y > 0){
                    pieces++;
                    board[lowest_free_y].insert_piece(piece); 
                }
                return lowest_free_y;
            }
        }
};

class Menu {

    public:

        void main_menu(){
            std::cout << "Connect 4" << std::endl;
            std::cout << "1. 2 Players" << std::endl;
            std::cout << "2. Player vs AI" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "Option: ";
        }

        void draw_menu(){

            std::cout << "Insert token at position (0 to exit game): "<< std::endl;
        }


};

int main(){

    char player1 = 'X';
    char player2 = 'O';
    int current_player = 1;
    bool game_finished = false;

    Board b;
    Menu m;
    
    m.main_menu();
    int option;
    std::cin >> option;

    if (option != 1 && option != 2 && option != 3){
        std::cout << "Invalid option" << std::endl;
        return 1;
    }

    int marker_position;
    int piece_placed = 0;
    bool started = false;

    while (!game_finished){

        if (piece_placed < 0) {
            std::cout << "Illegal move" << std::endl;
        }
        else if(piece_placed >= 0 && started){
            current_player = current_player == 2 ? 1 : 2; //Switches the current player
        }
        
        clear_console();
        b.draw_board(); 
        m.draw_menu();

        started = true;
        std::cout << "It's Player" << current_player << "'s turn" << std::endl;

        std::cin >> marker_position;

        if (marker_position == 0){
            std::cout << "Exiting game" << std::endl;
            return 0;
        }

        char current_piece = current_player == 2 ? player1 : player2;
        piece_placed = b.place_marker(current_piece, marker_position); //Returns the position of the piece, or -1 if no space in the column
        
        std::cin.clear(); // Reset stdin to avoid 
        std::cin.ignore(100000, '\n');

        game_finished = b.check_for_win(piece_placed, current_piece);

        if (game_finished){
            clear_console();
            b.draw_board();
            std::cout << "Player" << current_player << " Wins!" << std::endl;
            return 0;
        }

    }
    return 0;
}