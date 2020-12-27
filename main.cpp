#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <chrono>

using std::cout;
using std::vector;
using std::stack;
using std::pair;
using std::make_pair;
using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::left;
using std::right;


using twoDimVector = vector<vector<int>>;
using twoDimStack = vector<vector<stack<int>>>;
using hrClock = std::chrono::high_resolution_clock;


void initializeBoard(twoDimVector& board,twoDimStack& checked, int n) {
    board.clear();
    checked.clear();

    vector<int> vectorOfZeros;
    vector<stack<int>> vectorOfStacks;
    stack<int> zeroStack;
    zeroStack.push(0);
    for (int i = 0; i < n; i++) {
        vectorOfZeros.push_back(0);
        vectorOfStacks.push_back(zeroStack);
    }
    for (int j = 0; j < n; j++) {
        board.push_back(vectorOfZeros);
        checked.push_back(vectorOfStacks);
    }
}


pair<int,int> findBestQueen(twoDimVector& board,twoDimStack& checked, int n, int k) {
    int count;
    int maxCount = 0;
    pair<int, int> coordBest;
    coordBest = make_pair(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count = 0;
            if (board[i][j] <=0 && checked[i][j].top() != k) {
                if(board[i][j] == 0) count = 1;
                for (int l = 1; l < n; l++) {
                    if (j + l < n && board[i][j + l] == 0) count = count + 1;
                    if (j - l >= 0 && board[i][j - l] == 0) count = count + 1;
                    if (i + l < n && board[i + l][j] == 0) count = count + 1;
                    if (i - l >= 0 && board[i - l][j] == 0) count = count + 1;
                    if (i + l < n && j + l < n && board[i + l][j + l] == 0) count = count + 1;
                    if (i - l >= 0 && j - l >= 0 && board[i - l][j - l] == 0) count = count + 1;
                    if (i - l >= 0 && j + l < n && board[i - l][j + l] == 0) count = count + 1;
                    if (i + l < n && j - l >= 0 && board[i + l][j - l] == 0) count = count + 1;
                }
                if (count > maxCount) {
                    maxCount = count;
                    coordBest = make_pair(i, j);
                }
            }
        }
    }
    return coordBest;
}


pair<int, int> findBestBishop(twoDimVector& board, twoDimStack& checked, int n, int k) {
    int count;
    int maxCount = 0;
    pair<int, int> coordBest;
    coordBest = make_pair(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count = 0;
            if (board[i][j] <= 0  && checked[i][j].top() != k) {
                if(board[i][j] == 0) count = 1;
                for (int l = 1; l < n; l++) {
                    if (i + l < n && j + l < n && board[i + l][j + l] == 0) count = count + 1;
                    if (i - l >= 0 && j - l >= 0 && board[i - l][j - l] == 0) count = count + 1;
                    if (i - l >= 0 && j + l < n && board[i - l][j + l] == 0) count = count + 1;
                    if (i + l < n && j - l >= 0 && board[i + l][j - l] == 0) count = count + 1;
                }
                if (count > maxCount) {
                    maxCount = count;
                    coordBest = make_pair(i, j);
                }
            }
        }
    }
    return coordBest;
}


pair<int, int> findBestKnight(twoDimVector& board, twoDimStack& checked, int n, int k) {
    int count;
    int maxCount = 0;
    pair<int, int> coordBest;
    coordBest = make_pair(-1, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            count = 0;
            if (board[i][j] <= 0 && checked[i][j].top() != k) {
                    if(board[i][j] == 0) count =  1;
                    if (i + 1 < n && j + 2 < n && board[i + 1][j + 2] == 0) count = count + 1;
                    if (i + 2 < n && j + 1 < n && board[i + 2][j + 1] == 0) count = count + 1;
                    if (i + 1 < n && j - 2 >= 0 && board[i + 1][j - 2] == 0) count = count + 1;
                    if (i + 2 < n && j - 1 >= 0 && board[i + 2][j - 1] == 0) count = count + 1;
                    if (i - 1 >= 0 && j - 2 >= 0 && board[i - 1][j - 2] == 0) count = count + 1;
                    if (i - 2 >= 0 && j - 1 >= 0 && board[i - 2][j - 1] == 0) count = count + 1;
                    if (i - 1 >= 0 && j + 2 < n && board[i - 1][j + 2] == 0) count = count + 1;
                    if (i - 2 >= 0 && j + 1 < n && board[i - 2][j + 1] == 0) count = count + 1;
            }
            if (count > maxCount) {
                maxCount = count;
                coordBest = make_pair(i, j);
            }
        }
    }
    return coordBest;
 }



pair<int,int> findBest(twoDimVector& board, twoDimStack& checked, int n, int k, pair<int,int>(*tipas)(twoDimVector&, twoDimStack&, int, int)) {
    return tipas(board, checked, n, k);
}


void place(twoDimVector& board, int n, int i, int j, int val, void(*tipas)(twoDimVector&, int, int, int, int)) {
    tipas(board, n, i, j, val);
}


void placeQueen(twoDimVector& board,int n, int i, int j,int val) {
    for (int l = 1; l < n; l++) {
        if (j + l < n && board[i][j + l] == 0) board[i][j + l] = -val;
        if (j - l >= 0 && board[i][j - l] == 0) board[i][j - l] = -val;
        if (i + l < n && board[i + l][j] == 0) board[i + l][j] = -val;
        if (i - l >= 0 && board[i - l][j] == 0)board[i - l][j] = -val;
        if (i + l < n && j + l < n && board[i + l][j + l] == 0) board[i + l][j + l] = -val;
        if (i - l >= 0 && j - l >= 0 && board[i - l][j - l ] == 0) board[i - l][j - l] = -val;
        if (i - l >= 0 && j + l < n && board[i - l][j + l] == 0) board[i - l][j + l] = -val;
        if (i + l < n && j - l >= 0 && board[i + l][j - l] == 0) board[i + l][j - l] = -val;
    }
}


void placeBishop(twoDimVector& board, int n, int i, int j, int val) {
    for (int l = 1; l < n; l++) {
        if (i + l < n && j + l < n && board[i + l][j + l] == 0) board[i + l][j + l] = -val;
        if (i - l >= 0 && j - l >= 0 && board[i - l][j - l] == 0) board[i - l][j - l] = -val;
        if (i - l >= 0 && j + l < n && board[i - l][j + l] == 0) board[i - l][j + l] = -val;
        if (i + l < n && j - l >= 0 && board[i + l][j - l] == 0) board[i + l][j - l] = -val;
    }
}



void placeKnight(twoDimVector& board, int n, int i, int j, int val) {
    if (i + 1 < n && j + 2 < n && board[i + 1][j + 2] == 0)  board[i + 1][j + 2] = -val;
    if (i + 2 < n && j + 1 < n && board[i + 2][j + 1] == 0) board[i + 2][j + 1] = -val;
    if (i + 1 < n && j - 2 >= 0 && board[i + 1][j - 2] == 0) board[i + 1][j - 2] = -val;
    if (i + 2 < n && j - 1 >= 0 && board[i + 2][j - 1] == 0) board[i + 2][j - 1] = -val;
    if (i - 1 >= 0 && j - 2 >= 0 && board[i - 1][j - 2] == 0) board[i - 1][j - 2] = -val;
    if (i - 2 >= 0 && j - 1 >= 0 && board[i - 2][j - 1] == 0) board[i - 2][j - 1] = -val;
    if (i - 1 >= 0 && j + 2 < n && board[i - 1][j + 2] == 0) board[i - 1][j + 2] = -val;
    if (i - 2 >= 0 && j + 1 < n && board[i - 2][j + 1] == 0) board[i - 2][j + 1] = -val;

}


int countZeros(twoDimVector& board) {
    int count = 0;
    for (auto& line: board) {
        for (int& square : line) {
            if (square == 0) count = count + 1;
        }
    }
    return count;
}





void removeFromStack(twoDimStack& checked, int k) {
    for (auto& line : checked) {
        for (auto& square : line) {
            if (square.top() == k) square.pop();
        }
    }
}


void removeFromVector(twoDimVector& board, int k) {
    for (auto& line : board) {
        for (int& square : line) {
            if (abs(square) == k) square = 0;
        }
    }
}


void dominatingSet(twoDimVector& board, twoDimStack& checked, int n, pair<int, int>(*findType)(twoDimVector&, twoDimStack&, int, int), void(*placeType)(twoDimVector&, int, int, int, int)) {
    int k = 1;
    int k_best = INT_MAX;
    twoDimVector ats;
    pair<int, int> coordBest;
    while (k > 0) {
        while (k < k_best) {
            coordBest = findBest(board,checked,n,k,findType);
            if (coordBest.first == -1) {
                break;
            }
            checked[coordBest.first][coordBest.second].push(k);
            board[coordBest.first][coordBest.second] = k;
            place(board,n,coordBest.first,coordBest.second,k,placeType);        
            if (countZeros(board) == 0) {
                k_best = k;
                ats = board;
                break;
            }
            if (k == k_best - 1) {
                break;
            }
            k = k + 1;
        }
        removeFromVector(board, k);
        removeFromStack(checked, k);
        k = k - 1;
        removeFromVector(board,k);
    }
    cout << "\n";
    cout << "Minimalus figuru skaicius: " << k_best << "\n\n";
    cout << "Gautas issidestymas lentoje: \n";
    for (auto& line : ats) {
        for (int& square : line) {
            cout << setw(3) << square << " ";
        }
        cout << "\n";
    }
    cout << "Teigiamas skaicius reiskia n-tosios figuros padejimo langeli\n";
    cout << "Neigiami skaicius reiskia kad tam langeliui pirmoji grasino n-toji figura\n";
 }



void greedyDominatingSet(twoDimVector& board, twoDimStack& checked, int n, pair<int, int>(*findType)(twoDimVector&, twoDimStack&, int, int), void(*placeType)(twoDimVector&, int, int, int, int)) {
    pair<int, int> coordBest;
    int k = 1;
    while (true) {
        coordBest = findBest(board, checked, n, k, findType);
        board[coordBest.first][coordBest.second] = k;
        place(board, n, coordBest.first, coordBest.second, k, placeType);
        if (countZeros(board) == 0) {
            break;
        }
        k = k + 1;
    }
    cout << "\n";
    cout << "Godziu algoritmu rastas figuru skaicius: " << k << "\n\n";
    cout << "Gautas issidestymas lentoje: \n";
    for (auto& line : board) {
        for (int& square : line) {
            cout <<setw(3) << square << " ";
        }
        cout << "\n";
    }
    cout << "Teigiamas skaicius reiskia n-tosios figuros padejimo langeli\n";
    cout << "Neigiami skaicius reiskia kad tam langeliui pirmoji grasino n-toji figura\n";
}



void start(twoDimVector& board, twoDimStack& checked, int n, void(*algorithm)(twoDimVector&, twoDimStack&, int, pair<int, int>(*)(twoDimVector&, twoDimStack&, int, int), void(*)(twoDimVector&, int, int, int, int))) {
    std::chrono::time_point<hrClock> start;
    std::chrono::time_point<hrClock> end;
    int m;
    cout << "\n Pasirinkite figura: \n";
    cout << "1. Valdove \n";
    cout << "2. Rikis \n";
    cout << "3. Zirgas \n";
    cin >> m;
    start = hrClock::now();
    switch (m) {
    case 1:
        algorithm(board, checked, n, findBestQueen, placeQueen);
        end = hrClock::now();
        cout << "\nAlgoritmas uztruko: " << std::chrono::duration<double>(end - start).count() << " s \n";
        break;
    case 2:
        algorithm(board, checked, n, findBestBishop, placeBishop);
        end = hrClock::now();
        cout << "\nAlgoritmas uztruko: " << std::chrono::duration<double>(end - start).count() << " s \n";
        break;
    case 3:
        algorithm(board, checked, n, findBestKnight, placeKnight);
        end = hrClock::now();
        cout << "\nAlgoritmas uztruko: " << std::chrono::duration<double>(end - start).count() << " s \n";
        break;
    default:
        cout << "Tokio pasirinkimo nera! \n";
        cin.clear();
        break;
    }
}


int main()
{
    int n;
    int m;
    twoDimVector board;
    twoDimStack checked;


    cout << setfill('-') << setw(55) << "-" << setfill(' ') << "\n";
    cout << "|" << setw(55) << "|\n";
    cout << "|" << setw(50) << left << " Sachmatu Lentos Dominavimo Skaicius" << right << "   |\n";
    cout << "|" << setw(55) << "|\n";
    cout << "|" << setw(55) << " Dovydas Martinkus Duomenu Mokslas 2gr. |\n";
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << "\n\n";


    while (true) {
        board.clear();
        checked.clear();
        cout << "Iveskite sachmatu lentos ilgi (ploti) n: \n";
        cin >> n;
        if (n <= 0) {
            n = 1;
            cout << "Bloga ivestis, laikau kad lentos dydis lygus 1 \n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        cout << "\n";
        initializeBoard(board, checked, n);
        cout << "Koki algoritma naudoti: \n";
        cout << "1. Paieska su grizimu \n";
        cout << "2. Godus algoritmas \n";
        cin >> m;
        switch (m) {
        case(1):
            start(board, checked, n, dominatingSet);
            break;
        case(2):
            start(board, checked, n, greedyDominatingSet);
            break;
        default:
            cout << "Tokio pasirinkimo nera! \n";
            cin.clear();
            break;
        }
        cout << "Paspauskite Enter jeigu norite pradeti is naujo \n";
        cin.ignore(256, '\n');
        cin.get();
    }
    return 0;
}

