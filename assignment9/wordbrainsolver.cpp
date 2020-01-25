// Copyright 2019 Dingjun Bian braybian@bu.edu
// Copyright 2019 Shiyang Hu shiyangh@bu.edu
// Copyright 2019 Charles Thao cthao19@bu.edu
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;
const int ALPHABETS = 26;

typedef std::vector <vector <char> > Word;

struct trienode {
  char me;
  struct trienode *child[ALPHABETS];
  struct trienode *parent;
  bool endword = false;
  string word = "";
};

struct game {
  Word board;
  int dimension = 0;
  void clear_board(int d);
  void show(int n);
};

int solve_control(game *gam, vector <string> game_list,
                  trienode *trie,
                  vector <int> lengths,
                  map <int, char> sol,
                  vector <std::string> *words,
                  set <std::string> *solset);
trienode * root;
void game::clear_board(int d) {
  dimension = d;
  board.clear();
  board.resize(dimension, vector <char> (d, 0));
}

int load_dictionary(string fn, trienode *trie) {
  ifstream infile(fn);
  int count;
  string s;
  while (infile >> s) {
    if (s.length() > ALPHABETS)
      continue;
    count++;
    if (trie->child[s.length()] == NULL) {
      trie->child[s.length()] = new trienode;
      trie->child[s.length()]->parent = trie;
      trie->child[s.length()]->me = '0' + s.length();
    }
    trienode * trielow = trie->child[s.length()];
    for (auto c : s) {
      if (trielow->child[c - 'a'] == NULL) {
        trielow->child[c - 'a'] = new trienode;
        trielow->child[c - 'a']->parent = trielow;
        trielow->child[c - 'a']->me = c;
      }
      trielow = trielow->child[c - 'a'];
    }
    trielow->endword = true;
    trielow->word = s;
  }
  return count;
}

bool load_game(const int& game_length,
               const vector<std::vector <char> >& game_words,
               const vector <string>& game_list,
               vector <int> *lengths, game *gam) {
  gam->clear_board(game_length);
  for (int j = 0; j < gam->dimension; j++) {
    for (int i = 0; i < game_words.size(); i++) {
      gam->board[j][i] = game_words[game_words.size() - 1 - i][j];
    }
  }
  for (auto &i : game_list) {
    lengths->push_back(i.length());
  }
  if (lengths->size() == 0 || gam->dimension == 0)
    return false;
  return true;
}

int solve_game(int elemx, int elemy,
               vector <string> game_list,
               game *gam,
               vector <int> lengths,
               trienode *trie,
               map <int, char> *sol,
               vector <string> *words,
               set <string> *solset
              ) {
  if (!trie) return false;
  map <int, char> tsol;
  tsol.insert(sol->begin(), sol->end());
  (tsol)[elemx + elemy * gam->dimension] = trie->me;
  for (const auto &p : (*sol))
    if (trie->endword) {
      vector <int> tlengths = lengths;
      tlengths.erase(tlengths.begin());
      vector <std::string> twords = *words;
      twords.push_back(trie->word);
      for (const auto &p : (twords))
        if (solve_control(gam, game_list, root, tlengths,
                          tsol, &twords, solset)) {
          *words = twords;
          *sol = tsol;
          return true;
        } else {
          return false;
        }
    }
  int maxx, maxy, minx, miny;
  if (elemx + 1 < gam-> dimension) {
    maxx = elemx + 1;
  } else {
    maxx = gam->dimension - 1;
  }
  if (elemy + 1 < gam-> dimension) {
    maxy = elemy + 1;
  } else {
    maxy = gam->dimension - 1;
  }
  if (elemx - 1 > 0) {
    minx = elemx - 1;
  } else {
    minx = 0;
  }
  if (elemy - 1 > 0) {
    miny = elemy - 1;
  } else {
    miny = 0;
  }
  for (int x = minx; x <= maxx; x++) {
    for (int y = miny; y <= maxy; y++) {
      if (tsol.count(x + y * gam->dimension))
        continue;
      char c;
      try {
        c = gam->board.at(x).at(y);
      } catch(std::out_of_range) {
        continue;
      }
      if (trie->child[c - 'a']) {
        if (solve_game(x, y, game_list, gam, lengths,
                       trie->child[gam->board.at(x).at(y) - 'a'], &
                       tsol, words, solset)) {
          sol->insert(tsol.begin(), tsol.end());
          return true;
        }
      }
    }
  }
  return false;
}

int solve_control(game *gam, vector <string> game_list,
                  trienode *trie,
                  vector <int> lengths,
                  map <int, char> sol,
                  vector <string> *words,
                  set <string> *solset) {
  if (lengths.size() == 0) {
    string sols = "";
    for (const auto &p : *words)
      sols += p + " ";
    solset->insert(sols);
    return false;
  }
  game tgam = *gam;
  for (map <int, char>::reverse_iterator it = sol.rbegin();
       it != sol.rend(); ++it) {
    tgam.board[it->first % tgam.dimension].erase(
      tgam.board[it->first % tgam.dimension].begin()
      + it->first / tgam.dimension);
  }
  for (int x = 0; x < tgam.board.size(); x++) {
    for (int y = 0; y < tgam.board.at(x).size(); y++) {
      map <int, char> tsol;
      vector <std::string> twords = *words;
      string temp, hint;
      if (twords.size() != 0) {
        for (int i = 0; i < twords.size(); i++) {
          temp = twords[i];
          hint = game_list[i];
          int count = 0;
          for (int j = 0; j < temp.size(); j++) {
            if (hint[j] != '*') {
              if (temp[j] == hint[j])
                count++;
            } else {
              count++;
            }
          }
          if (count != temp.size()) {
            return false;
          }
        }
      }
      if (trie->child[lengths.front()]) {
        if (solve_game( x, y, game_list, &tgam, lengths,
                        trie->child[lengths.front()]->child[tgam.
                            board.at(x).at(y) - 'a'],
                        &tsol, &twords, solset)) {
          *words = twords;
          return true;
        }
      }
    }
  }
  return false;
}

vector <string> divide_string(const std::string& s,
                              const std::string& c) {
  vector <std::string> v;
  string::size_type pos1, pos2;
  pos1 = 0;
  pos2 = s.find(c);
  while (std::string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2 - pos1));
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if (pos1 != s.length())
    v.push_back(s.substr(pos1));
  return v;
}


int main(int argc, char const *argv[]) {
  trienode trie = trienode();
  trienode trie2 = trienode();
  load_dictionary(argv[1], &trie);
  load_dictionary(argv[2], &trie2);
  while (true) {
    game gam = game();
    Word game_words;
    string games;
    string line = "";
    while (cin) {
      if (cin.eof()) exit(0);
      getline(std::cin, line);
      if (line == "") exit(0);
      if (line.find("*") == std::string::npos) {
        vector<char> data(line.begin(), line.end());
        game_words.push_back(data);
      } else {
        games = line;
        break;
      }
    }
    int game_length = game_words[0].size();
    vector <string> game_list = divide_string(games, " ");
    root = &trie;

    vector <int> lengths;
    if (!load_game(game_length, game_words, game_list, &lengths, &gam))
      return false;
    map <int, char> sol;
    set<string> solset;
    vector<string> words;
    solve_control(&gam, game_list, &trie, lengths, sol, &words, &solset);
    if (solset.size() == 0) {
      root = &trie2;
      solve_control(&gam, game_list,
                    &trie2, lengths, sol, &words, &solset);
    }
    for (const auto &p : solset)
      cout << p << std::endl;
    cout << "." << std::endl;
  }
}



