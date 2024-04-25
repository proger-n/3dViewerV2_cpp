#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <sstream>

#include "facade.h"

namespace s21 {

Parser::Parser(std::vector<double> *vertices,
               std::vector<unsigned int> *indices)
    : vertices_(vertices), indices_(indices) {}

void Parser::SetFileName(const std::string &file_name) {
  vertices_->clear();
  indices_->clear();
  file_name_ = file_name;
}

double Parser::GetMaxVertex() const noexcept { return max_vertex_; }

void Parser::ParseObj() {
  std::ifstream file;
  file.open(file_name_);
  if (!file.is_open()) {
    throw std::out_of_range("Could not open input file!");
  }
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      ParseVertices(line.substr(2));
    } else if (line[0] == 'f' && line[1] == ' ') {
      ParseIndices(line.substr(2));
    }
  }
  file.close();
  if (vertices_->empty() || indices_->empty()) {
    throw std::out_of_range("Unable to parse the file!");
  }
  unsigned int max_index =
      *std::max_element(indices_->begin(), indices_->end());
  if (max_index > vertices_->size() / 3) {
    throw std::out_of_range("Invalid indices!");
  }
  double max = *(std::max_element(vertices_->begin(), vertices_->end()));
  double min = *(std::min_element(vertices_->begin(), vertices_->end()));
  max_vertex_ = std::max(std::abs(max), std::abs(min));
}

void Parser::ParseVertices(std::string &&line) {
  std::vector<double> vertices(3);
  std::istringstream stream(line);
  stream >> vertices[0] >> vertices[1] >> vertices[2];
  for (double &vertex : vertices) {
    vertices_->push_back(vertex);
  }
}

void Parser::ParseIndices(std::string &&line) {
  int first_index = LineToIndex(std::move(line));
  indices_->push_back(first_index);
  int line_size = line.size();
  for (int i = 0; i < line_size; ++i) {
    if (isdigit(line[i]) || line[i] == '-') {
      int second_index = LineToIndex(line.substr(i));
      while (line[i] && line[i] != ' ') {
        ++i;
      }
      indices_->push_back(second_index);
      indices_->push_back(second_index);
    }
  }
  indices_->push_back(first_index);
}

int Parser::LineToIndex(std::string &&line) {
  int index = std::stoi(line) - 1;
  if (index < 0) index = (int)vertices_->size() / 3 + index + 1;
  return index;
}

}  // namespace s21