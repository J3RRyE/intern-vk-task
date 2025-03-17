#pragma once

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Input {
  std::vector<std::set<std::size_t>> adjacency_list;
  std::size_t start_vertex;

 private:
  void fill_from_stream(std::istream& input) {
    std::size_t vertices_amount, edges_amount;
    input >> vertices_amount >> edges_amount;

    adjacency_list.resize(vertices_amount);

    for (; edges_amount--;) {
      std::size_t vertex_out, vertex_in;
      input >> vertex_out >> vertex_in;

      adjacency_list[vertex_out].emplace(vertex_in);
      adjacency_list[vertex_in].emplace(vertex_out);
    }
    input >> start_vertex;
  }

  void fill_from_file(const std::string& path_to_input_file) {
    std::ifstream input(path_to_input_file);
    if (!input.is_open()) {
      std::cerr << "File not found: " << path_to_input_file << std::endl;
      throw std::runtime_error("File not found");
    }

    fill_from_stream(input);
    input.close();
  }

 public:
  Input() = delete;
  Input(const std::string& path) {
    if (path == "cin") {
      fill_from_stream(std::cin);
    } else {
      fill_from_file(path);
    }
  }
  ~Input() = default;
};

class Graph {
 private:
  // For fast access, store adjacency list as: Vertex_id -> set<Vertex>
  std::vector<std::set<std::size_t>> adjacency_list_;

 public:
  Graph() = default;

  Graph(Input& input) : adjacency_list_(std::move(input.adjacency_list)) {}

  ~Graph() = default;

  auto BFS(const std::size_t& start_vertex) const -> std::vector<ssize_t> {
    std::vector<ssize_t> distance(adjacency_list_.size(), -1);

    std::queue<std::size_t> queue;
    queue.push(start_vertex);
    distance[start_vertex] = 0;

    while (!queue.empty()) {
      std::size_t current_vertex = queue.front();
      queue.pop();

      for (const auto& neighbour : adjacency_list_[current_vertex]) {
        if (distance[neighbour] == -1) {
          distance[neighbour] = distance[current_vertex] + 1;
          queue.push(neighbour);
        }
      }
    }

    return distance;
  }
};
