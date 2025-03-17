#include <iostream>

#include "graph.hpp"

int main(int argc, char* argv[]) {
  Input input(argc > 1 ? argv[1] : /*base path*/ "./tests/graph.txt");
  Graph graph(input);
  std::size_t start_vertex = input.start_vertex;

  auto answ = graph.BFS(start_vertex);

  for (const auto& dist : answ) {
    std::cout << dist << std::endl;
  }
}
