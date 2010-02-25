/* 
 * File:   main.cpp
 * Author: tiago
 *
 * Created on February 25, 2010, 5:10 PM
 */

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

int m, n, w, h, x0, y0, xf, yf;
int dist = 0;

bool isFinalSquare(vector< pair<int, int> > Squares) {
    for (vector< pair<int, int> >::const_iterator it = Squares.begin();
            it < Squares.end(); ++it) {

        if ((*it).first == xf && (*it).second == yf)
            return true;
    }
    return false;
}

bool isPossible(const pair<int, int>& coord) {
    return (coord.first > 0 && coord.second > 0
            && coord.first <= w && coord.second <= h);
}

vector< pair<int, int> > getNewSquares(pair<int, int> Square) {
    vector< pair<int, int> > coords;

    coords.push_back(make_pair(Square.first + m, Square.second + n));
    coords.push_back(make_pair(Square.first + m, Square.second - n));
    coords.push_back(make_pair(Square.first - m, Square.second + n));
    coords.push_back(make_pair(Square.first - m, Square.second - n));
    coords.push_back(make_pair(Square.first + n, Square.second + m));
    coords.push_back(make_pair(Square.first + n, Square.second - m));
    coords.push_back(make_pair(Square.first - n, Square.second + m));
    coords.push_back(make_pair(Square.first - n, Square.second - m));

    for (vector< pair<int, int> >::iterator it = coords.begin();
            it != coords.end(); it++) {

        if (!isPossible(*it)) {
            coords.erase(it);
            it--;
        }
    }

    return coords;
}

vector < pair<int, int> > mainloop(vector < pair<int, int> > Squares,
        set< pair<int, int> > & visitedSquares) {

    vector< pair<int, int> >newSquares;

    for (vector < pair<int, int > >::const_iterator it = Squares.begin();
            it < Squares.end(); ++it) {

        vector < pair<int, int> > temp;

        if (visitedSquares.insert((*it)).second)
            temp = getNewSquares(*it);


        for (vector < pair<int, int > >::const_iterator iter = temp.begin();
                iter < temp.end(); ++iter) {

            newSquares.push_back(*iter);
        }
    }

    if (newSquares.size() == 0) {
        dist = -1;
        return newSquares;
    }

    if (isFinalSquare(newSquares)) {
        dist++;
        return newSquares;
    } else {
        dist++;
        mainloop(newSquares, visitedSquares);
    }



}

int main(void) {

    string line;
    stringstream iss;

    do {
        getline(cin, line);
        if (line == "")
            break;
        iss << line;
        iss >> m >> n >> w >> h >> x0 >> y0 >> xf >> yf;

        set< pair<int, int> > visitedSquares;

        vector< pair<int, int> > firstSquare;
        firstSquare.push_back(make_pair(x0, y0));

        mainloop(firstSquare, visitedSquares);
        if (dist == -1) {
            cout << "impossible\n";
        } else {
            cout << dist << endl;
        }

        dist = 0;
        visitedSquares.clear();
        iss.clear();
    }    while (true);

    return 0;
}

