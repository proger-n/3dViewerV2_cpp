#include "controller.h"

namespace s21 {

Controller::Controller(Facade *facade) : facade_(facade) {}

void Controller::ParseObj() { facade_->ParseObj(); }

void Controller::Transform(int command, double value) {
  facade_->Transform(command, value);
}

void Controller::SetFileName(const std::string &file_name) {
  facade_->SetFileName(file_name);
}

std::vector<double> &Controller::GetVertices() noexcept {
  return facade_->GetVertices();
}

std::vector<unsigned int> &Controller::GetIndices() noexcept {
  return facade_->GetIndices();
}

double Controller::GetMaxVertex() const noexcept {
  return facade_->GetMaxVertex();
}

}  // namespace s21