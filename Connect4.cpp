#include <bits/stdc++.h>
using namespace std;
int play, turn, userIn, maximum;
bool win;
void multi();
void single();
vector<vector<string>> board(6, vector<string>(7," "));
vector<vector<string>> cleared(6,vector<string>(7," "));
map<int,int> colspace;

int main() {
    cout << "\tWelcome to Connect Four!\nEnter 1 for singleplayer\nEnter 2 for multiplayer\nEnter 3 to exit\nInput : ";
    cin>>play;
    cout<<"\n";

    while (!(play == 1 || play == 2 || play == 3)) {
        cout<<"Invalid Input\n\n";
        cout<<"Enter 1 for singleplayer\nEnter 2 for multiplayer\nEnter 3 to exit\nInput : ";
        cin>>play;
        cout<<"\n";
    }

    board = cleared;
    win = false;
    switch (play) {
        case 1:
            turn = 1;
            single();
            break;
        case 2:
            turn = (rand() % 2) + 1;    
            multi();
            break;
        case 3:
            return 0;
    } 

    return 0;
}

void replay() {
    cout<<"\n\nWould you like to play another game?\nEnter 1 to play another game\nEnter 2 to exit\nInput: ";
    cin>>play; cout<<"\n";
    while (!(play == 1 || play == 2)) {
        cout<<"Invalid Input\n\n";
        cout<<"Enter 1 to play another game\nEnter 2 to exit\nInput: ";
        cin>>play;
        cout<<"\n";
    }
    switch (play) {
        case 1:
            main();
        case 2:
            return;
    }
}

void getInput() {
    string temp;
    while (true) {
        cout << "Enter a Column : "; cin>>temp; cout<<"\n"; 
        //Input Checking
        try {
            userIn = stoi(temp);
        } catch (invalid_argument&) {
            cout << "Please Enter a digit\n";
            continue;
        }
        if (userIn <= 0 || userIn >= 8) {
            cout << "Please Enter numbers 1-7\n";
        } else if (colspace[userIn] <= 0) {
            cout << "This column is full\n";
        } else {
            break;
        }
        //
    }
}

bool checkboard(int row, int col, string x, vector<vector<string>>& currentboard) {
    //Check Vertical
    int i = row - 1, j = row + 1, h = 1;
    while (i >= 0 && currentboard[i][col] == x) {
        h++;
        i--;
    } while (j < currentboard.size() && currentboard[j][col] == x) {
        h++;
        j++;
    }
    if (h >= 4) {

        return true;
    }

    //Check Horizontal
    i = col - 1, j = col + 1, h = 1;
    while (i >= 0 && currentboard[row][i] == x) {
        h++;
        i--;
    } while (j < currentboard[0].size() && currentboard[row][j] == x) {
        h++;
        j++;
    }
    if (h >= 4) {
        return true;
    }

    //Check Diagonal UpLeft-DownRight
    i = row - 1, j = row + 1, h = 1;
    int i2 = col - 1, j2 = col + 1;
    while (i >= 0 && i2 >= 0 && currentboard[i][i2] == x) {
        h++;
        i--;
        i2--;
    } while (j < currentboard.size() && j2 < currentboard[0].size() && currentboard[j][j2] == x) {
        h++;
        j++;
        j2++;
    }
    if (h >= 4) {
        return true;
    }

    //Check Diagonal DownLeft-UpRight
    i = row + 1, i2 = col - 1, j = row - 1, j2 = col + 1, h = 1;
    while (i < currentboard.size() && i2 >= 0 && currentboard[i][i2] == x) {
        h++;
        i++;
        i2--;
    } while (j >= 0 && j2 < currentboard[0].size() && currentboard[j][j2] == x) {
        h++;
        j--;
        j2++;
    }
    if (h >= 4) {
        return true;
    }

    return false;
}

int evaluateBoard(vector<string>& current) {

    int ans = 0, opp = 0, ai = 0; 
    for (auto a : current) {
        if (a == "O") {
            ai++;
        } else if (a == "X") {
            opp++;
        }
    }

    if (ai == 3 && opp == 0) {
        ans+=5;
    } else if (ai == 2 && opp == 0) {
        ans+=3;
    } else if (ai == 1 && opp == 0) {
        ans+=1;
    } else if (ai == 2 && opp == 1) {
        ans+=2;
    } else if (ai == 1 && opp == 2) {
        ans-=2;
    } else if (ai == 0 && opp == 2) {
        ans-=3;
    } else if (ai == 0 && opp == 3) {
        ans-=5;
    } else if (ai == 0 && opp == 1) {
        ans-=1;
    }

    return ans;
}

int score(vector<vector<string>>& current) {
    int ans = 0;
    //Count Center
    for (int i = 0; i < 6; i++) {
        if (current[i][3] == "O") ans += 5;
    }
    //

    vector<string> temp;
    //Horizontal for each row 
    //Eg. Row one, taking 1-4,2-5,3-6,4-7 and adding scores so row two and so forth, yea;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            temp = { current[i][j], current[i][j+1], current[i][j+2], current[i][j+3] };
            ans += evaluateBoard(temp);
        }
    }
    //

    //Vertical same thing
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            temp = {current[j][i], current[j+1][i],current[j+2][i],current[j+3][i]};
            ans += evaluateBoard(temp);
        }
    }
    //

    //Diagonal
    for (int i = 0; i < 3; i++) { //i = rows
        for (int j = 0; j < 4; j++) { // j = cols
            temp = { current[i][j], current[i+1][j+1], current[i+2][j+2], current[i+3][j+3] };
            ans += evaluateBoard(temp);
        }
    }   
    //

    //Neg.Diagonal
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 7; j++) {
            temp = { current[i][j], current[i+1][j-1], current[i+2][j-2], current[i+3][j-3]};
            ans += evaluateBoard(temp);
        }
    }
    //

    return ans; 
}

pair<int,int> minimax(vector<vector<string>>& currentboard, int depth, bool Ai, int steps, map<int,int>& currentmap) {
    if (depth == 0) {
        return {0, score(currentboard)};
    }
    if (steps >= 42) {
        return {0,0};
    }
    int temp, col;
    if (Ai) {
        temp = INT_MIN;
        for (int i = 0; i < 7; i++) {
            if (currentmap[i+1] - 1 < 0) continue;

            currentboard[currentmap[i+1] - 1][i] = "O";
            currentmap[i+1]--;

            if (checkboard(currentmap[i+1], i, "O" , currentboard)) {
                temp = INT_MAX;
                currentmap[i+1]++;
                currentboard[currentmap[i+1] - 1][i] = " ";
                col = i;
                break;
            }
    
            if (temp < minimax(currentboard, depth - 1, !Ai, steps+1, currentmap).second) {
                temp = minimax(currentboard, depth - 1, !Ai, steps+1, currentmap).second;
                col = i;
            }

            currentmap[i+1]++;
            currentboard[currentmap[i+1] - 1][i] = " ";
        }

        return {col, temp};
    } else {
        temp = INT_MAX;
        for (int i = 0; i < 7; i++) {
            if (currentmap[i+1] - 1 < 0) continue;

            currentboard[currentmap[i+1] - 1][i] = "X";
            currentmap[i+1]--;

            if (checkboard(currentmap[i+1] , i, "X" , currentboard)) {
                temp = INT_MIN;
                currentmap[i+1]++;
                currentboard[currentmap[i+1] - 1][i] = " ";
                col = i;
                break;
            }

            if (temp > minimax(currentboard, depth - 1, !Ai, steps+1, currentmap).second) {
                temp = minimax(currentboard, depth - 1, !Ai, steps+1, currentmap).second;
                col = i;
            }

            currentmap[i+1]++;
            currentboard[currentmap[i+1] - 1][i] = " ";
        }

        return {col,temp};
    }
}

void printboard() {
    cout << "\n    1    2    3    4    5    6    7   \n";
    int x = 0;
    for (auto a : board) {
        x++;
        for (auto b : a) {
            cout << " || " << b;
        } 
        if (x > 5) {
            cout << " ||\n";
            break;
        }
        cout << " ||\n ||   ||   ||   ||   ||   ||   ||   ||\n"; 
    } cout << " =====================================\n";
}

void single() {
    colspace = {{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6}};
    int maximum = 0;
    string temp;

    while (true) {
        printboard();

        if (turn == 1) {
            cout<<"Your Turn\n";
            getInput();
        } else {
            userIn = minimax(board, 5, true, maximum, colspace).first + 1;
        }

        maximum++; 
        board[colspace[userIn] - 1][userIn - 1] = turn == 1 ? "X" : "O";
        //Win
        if (checkboard(colspace[userIn] - 1 , userIn - 1, (turn == 1 ? "X" : "O"), board)) break;
        //
        if (maximum == 42) break;

        colspace[userIn]--;
        turn = turn == 1 ? 2 : 1;
    } 

    printboard();
    if (maximum == 42) {
        cout << "Draw!!";
    } else {
        if (turn == 1) {
            cout << "You Win!";
        } else {
            cout << "You lost";
        }
    }
    replay();
}

void multi() {
    colspace = {{1,6},{2,6},{3,6},{4,6},{5,6},{6,6},{7,6}};
    maximum = 0;
    while (true) {
        printboard();
        cout<<"Player "<<turn<<"'s Turn\n";
        getInput();  

        maximum++; 
        board[colspace[userIn] - 1][userIn - 1] = turn == 1 ? "X" : "O";
        //Win
        win = checkboard( colspace[userIn] - 1 , userIn - 1, (turn == 1 ? "X" : "O"), board);
        if (win) break;
        //
        if (maximum == 42) break;

        colspace[userIn]--;
        turn = turn == 1 ? 2 : 1;
    } 

    printboard();
    if (maximum == 42) {
        cout << "Draw!!";
    } else {
        cout << "Winner : Player "<<turn<<" !!!";
    }
    replay();
}