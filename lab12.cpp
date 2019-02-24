// Include standard headers
#include <cstdio>
#include <cstdlib>

#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

#include <boost/tokenizer.hpp>

using namespace boost;
using namespace std;

enum CELL_TYPE {
  START = -2,
  BLOCKED = -3,
  EMPTY = 0
};

vector<vector<int>> vec;
static int num_steps = 0;

int load_data(char* filename)
{
  string data(filename);
  ifstream in(data.c_str());
  if (!in.is_open()) return 1;

  typedef tokenizer<escaped_list_separator<char>> Tokenizer;

  vector<string> vec_tmp;
  string line;

  while (getline(in, line))
  {
    Tokenizer tok(line);
    vec_tmp.assign(tok.begin(),tok.end());

    vector<int> line_vec;
    for (auto element: vec_tmp) {
      line_vec.push_back(stoi(element));
    }
    vec.push_back(line_vec);
  }

  return 0;
}

void find_start_point(int& startX, int& startY)
{
  for(int i = 0; i < vec.size(); i++) {
    for(int j = 0; j < vec[i].size(); j++) {
      if (vec[i][j] == START) {
        startX = j;
        startY = i;
        return;
      }
    }
  }
}

void draw_array()
{
  for(int i = 0; i < vec.size(); i++) {
    for(int j = 0; j < vec[i].size(); j++)
      printf("%3d", vec[i][j]);
    printf("\n");
  }
  printf("\n");
}

void mark_point(int x, int y, int counter)
{
  if ((y >= 0) && (y < vec.size()) && (x >= 0) && (x < vec[y].size()) && (vec[y][x] == EMPTY))
    vec[y][x] = counter;
}

void mark_nearest(int startX, int startY, int counter)
{
  num_steps++;
  printf("Step: %d\n", num_steps);

  mark_point(startX + 1, startY, counter);
  mark_point(startX, startY - 1, counter);
  mark_point(startX, startY + 1, counter);
  mark_point(startX - 1, startY, counter);

  draw_array();

  int newX, newY;

  newY = startY;
  newX = startX + 1;
  if ((newY >= 0) && (newY < vec.size()) &&
      (newX >= 0) && (newX < vec[newY].size()) && (vec[newY][newX] == counter))
    mark_nearest(newX, newY, counter + 1);

  newY = startY - 1;
  newX = startX;
  if ((newY >= 0) && (newY < vec.size()) &&
      (newX >= 0) && (newX < vec[newY].size()) && (vec[newY][newX] == counter))
    mark_nearest(newX, newY, counter + 1);

  newY = startY + 1;
  newX = startX;
  if ((newY >= 0) && (newY < vec.size()) &&
      (newX >= 0) && (newX < vec[newY].size()) && (vec[newY][newX] == counter))
    mark_nearest(newX, newY, counter + 1);

  newY = startY;
  newX = startX - 1;
  if ((newY >= 0) && (newY < vec.size()) &&
      (newX >= 0) && (newX < vec[newY].size()) && (vec[newY][newX] == counter))
    mark_nearest(newX, newY, counter + 1);

  return;
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("Usage: %s CSV_MAP", argv[0]);
    return -1;
  }

  if (load_data(argv[1]))
    return -1;

  printf("Step: %d\n", num_steps);
  draw_array();

  int startX, startY;
  find_start_point(startX, startY);
  //printf("X: %d. Y: %d\n", startX, startY);

  //vec[startY][startX] = 0;
  int counter = 0;
  mark_nearest(startX, startY, counter + 1);

  return 0;
}

