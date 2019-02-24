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

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>

using namespace glm;
using namespace boost;
using namespace std;

enum CELL_TYPE {
  START = -2,
  BLOCKED = -1,
  EMPTY = 0
};

int load_data(char* filename, vector<vector<CELL_TYPE>>& out_vec)
{
  string data(filename);
  ifstream in(data.c_str());
  if (!in.is_open()) return 1;

  typedef tokenizer<escaped_list_separator<char>> Tokenizer;

  vector<string> vec;
  string line;

  while (getline(in, line))
  {
    Tokenizer tok(line);
    vec.assign(tok.begin(),tok.end());

    vector<CELL_TYPE> line_vec;
    for (auto element: vec) {
      line_vec.push_back(static_cast<CELL_TYPE>(stoi(element)));
    }
    out_vec.push_back(line_vec);
  }

  return 0;
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("Usage: %s CSV_MAP", argv[0]);
    return -1;
  }

  vector<vector<CELL_TYPE>> data_vec;

  if (load_data(argv[1], data_vec))
    return -1;

  return 0;

  // Initialise GLFW
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context
  window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    perror("Failed to initialize GLEW");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  do{
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw nothing, see you in tutorial 2 !


    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
      glfwWindowShouldClose(window) == 0 );

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}

