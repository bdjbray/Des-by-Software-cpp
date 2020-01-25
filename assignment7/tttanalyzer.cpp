// Copyright 2019 Dingjun Bian braybian@bu.edu
// Copyright 2019 Shiyang Hu shiyangh@bu.edu
#include <iostream>
#include <string>
#include <vector>
#include "movedef.h"
using std::cout;
using std::string;
using std::vector;

char tttresult(string board) {
  int len = board.length();
  int countvalid = 0;
  int countx = 0;
  int counto = 0;
  int fullcout = 0;
  if (len != 9) {
    return 'e';
  }
  for (int i = 0; i < len; ++i) {
    if ((board.at(i) == 'x') || (board.at(i) == 'o') || (board.at(i) == '#')) {
      countvalid += 1;
    }
  }
  if (countvalid != 9) {
    return 'e';
  }
  int numx = 0;
  int numo = 0;
  for (int i = 0; i < len; ++i) {
    if (board.at(i) == 'x') {
      numx += 1;
    }
    if (board.at(i) == 'o') {
      numo += 1;
    }
  }
  if ((numo - numx >= 1) || (numx - numo >= 2)) {
    return 'i';
  }
  for (int i = 0; i < 8; i += 3) {
    if ((board.at(i) == 'x') && (board.at(i) == board.at(i + 1)) && (board.at(i + 1) == board.at(i + 2))) {
      countx = 1;
      break;
    }
  }
  for (int i = 0; i < 3; i += 1) {
    if ((board.at(i) == 'x') && (board.at(i) == board.at(i + 3)) && (board.at(i + 3) == board.at(i + 6))) {
      countx = 1;
      break;
    }
  }
  if((board.at(0) == 'x') && (board.at(0) == board.at(4)) && (board.at(4) == board.at(8))) {
    countx = 1;
  }
  if((board.at(2) == 'x') && (board.at(2) == board.at(4)) && (board.at(4) == board.at(6))) {
    countx = 1;
  }
  for (int i = 0; i < 8; i += 3) {
    if ((board.at(i) == 'o') && (board.at(i) == board.at(i + 1)) && (board.at(i + 1) == board.at(i + 2))) {
      counto = 1;
      break;
    }
  }
  for (int i = 0; i < 3; i += 1) {
    if ((board.at(i) == 'o') && (board.at(i) == board.at(i + 3)) && (board.at(i + 3) == board.at(i + 6))) {
      counto = 1;
      break;
    }
  }
  if((board.at(0) == 'o') && (board.at(0) == board.at(4)) && (board.at(4) == board.at(8))) {
    counto = 1;
  }
  if((board.at(2) == 'o') && (board.at(2) == board.at(4)) && (board.at(4) == board.at(6))) {
    counto = 1;
  }
  if ((countx == 1) && (counto == 1)) {
    return 'i';
  } else if (countx == 1) {
    if (numx - numo == 1) {
      return 'x';
    } else {
      return 'i';
    }
  } else if (counto == 1) {
    if (numo == numx) {
      return 'o';
    } else {
      return 'i';
    }
  }
  for (int i = 0; i < len; ++i) {
    if ((board.at(i) == 'x') || (board.at(i) == 'o')) {
      fullcout += 1;
    }
  }
  if (fullcout == 9) {
    return 't';
  }
  return 'c';
}

char tttresult(vector<Move>  board) {
  int len1 = board.size();
  int xwon = 0;
  int owon = 0;
  int validbit;
  if (len1 > 9) {
    return 'i';
  }
  for (int i = 0; i < len1; ++i) {
    if ((board.at(i).player != 'x') && (board.at(i).player != 'o')) {
      return 'i';
    }
    if ((board.at(i).r > 2) || (board.at(i).r < 0)) {
      return 'i';
    }
    if ((board.at(i).c > 2) || (board.at(i).c < 0)) {
      return 'i';
    }
  }
  int diagcountx = 0;
  int antidiagcountx = 0;
  vector<int> rowcountx (3, 0);
  vector<int> colcountx (3, 0);
  int diagcounto = 0;
  int antidiagcounto = 0;
  vector<int> rowcounto (3, 0);
  vector<int> colcounto (3, 0);
  for (int i = 0; i < len1; ++i) {
    if (board.at(i).player == 'x') {
      if ((board.at(i).r) == (board.at(i).c)) {
        diagcountx += 1;
      }
      if ((board.at(i).r + board.at(i).c) == 2) {
        antidiagcountx += 1;
      }
      rowcountx.at(board.at(i).r) += 1;
      colcountx.at(board.at(i).c) += 1;
    }
    if (board.at(i).player == 'o') {
      if ((board.at(i).r) == (board.at(i).c)) {
        diagcounto += 1;
      }
      if ((board.at(i).r + board.at(i).c) == 2) {
        antidiagcounto += 1;
      }
      rowcounto.at(board.at(i).r) += 1;
      colcounto.at(board.at(i).c) += 1;
    }
  }
  if(abs(rowcountx.at(0)) == 3 || abs(rowcountx.at(1)) == 3 || abs(rowcountx.at(2)) == 3 || abs(colcountx.at(0)) == 3 || abs(colcountx.at(1)) == 3 || abs(colcountx.at(2)) == 3 || abs(diagcountx) == 3 || abs(antidiagcountx) == 3) {
    xwon = 1;
  }
  if(abs(rowcounto.at(0)) == 3 || abs(rowcounto.at(1)) == 3 || abs(rowcounto.at(2)) == 3 || abs(colcounto.at(0)) == 3 || abs(colcounto.at(1)) == 3 || abs(colcounto.at(2)) == 3 || abs(diagcounto) == 3 || abs(antidiagcounto) == 3) {
    owon = 1;
  }
  if ((owon == 1) && (xwon == owon)) {
    return 'i';
  } else if (xwon == 1) {
    return 'x';
  } else if (owon == 1) {
    return 'o';
  }
  if (len1 == 9) {
    return 't';
  }
  return 'c';
}

vector<string> get_all_boards() {
  vector<string> boards;
  string s1;
  for(int i = 0; i < 19683; ++i) {
    int c = i;
    s1 = "";
    for (int j = 0; j < 9; ++j) {
      int a = c % 3;
      if (a == 0) {
        s1.push_back('#');
      } else if(a == 1) {
        s1.push_back('x');
      } else if(a == 2) {
        s1.push_back('o');
      }
      c /= 3;
    }
    boards.push_back(s1);
  }
  return boards;
}

void ttt_tally() {
  int totalx = 0;
  int totalo = 0;
  int totalt = 0;
  int totali = 0;
  int totalc = 0;
  vector<string> v;
  char result;
  v = get_all_boards();
  for (int i = 0; i < v.size(); ++i) {
    result = tttresult(v.at(i));
    if (result == 'x') {
      totalx += 1;
    } else if (result == 'o') {
      totalo += 1;
    } else if (result == 't') {
      totalt += 1;
    } else if (result == 'i') {
      totali += 1;
    } else if (result == 'c') {
      totalc += 1;
    }
  }
  cout << "x " << totalx << "\n" << "o " << totalo << "\n" << "t " << totalt << "\n" << "i " << totali << "\n" << "c " << totalc << "\n";
}


// MAIN
int main() {
  int n;
  std::string board;
  Move m;
  std::vector<Move> moves;
  std::vector<std::string> boards;
  std::string asktype;

  while (std::cin >> asktype) {
    if (asktype == "v") {  // test tttresult vector
      moves.clear();
      std::cin >> n;
      for (int i = 0; i < n; i++) {
        std::cin >> m.r >> m.c >> m.player;
        moves.push_back(m);
      }
      std::cout << tttresult(moves) << "\n";
    } else if (asktype == "s") {  // test tttresult string
      std::cin >> board;
      std::cout << tttresult(board) << "\n";
    } else if (asktype == "a") {  // test get_all_boards
      boards = get_all_boards();
      for (auto b : boards) {
        std::cout << b << "\n";
      }
    } else if (asktype == "t") {  // test ttt_tally
      ttt_tally();
    } else {
      return 0;
    }
  }
  return 0;
}