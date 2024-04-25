#include "facade.h"

namespace s21 {

Facade::Facade() : parser_(new Parser(&vertices_, &indices_)) {
  commands_.push_back(new RotateX(&vertices_));
  commands_.push_back(new RotateY(&vertices_));
  commands_.push_back(new RotateZ(&vertices_));
  commands_.push_back(new MoveX(&vertices_));
  commands_.push_back(new MoveY(&vertices_));
  commands_.push_back(new MoveZ(&vertices_));
  commands_.push_back(new Scale(&vertices_));
}

Facade::~Facade() {
  delete parser_;
  for (Command *command : commands_) {
    delete command;
  }
}

void Facade::SetFileName(const std::string &file_name) {
  parser_->SetFileName(file_name);
}

void Facade::ParseObj() { parser_->ParseObj(); }

std::vector<double> &Facade::GetVertices() noexcept { return vertices_; }

std::vector<unsigned int> &Facade::GetIndices() noexcept { return indices_; }

double Facade::GetMaxVertex() const noexcept { return parser_->GetMaxVertex(); }

void Facade::Transform(int command, double value) noexcept {
  commands_[command]->Transform(value);
}

}  // namespace s21