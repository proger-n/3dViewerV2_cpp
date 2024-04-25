#include "command.h"

#include <cmath>

namespace s21 {

RotateX::RotateX(std::vector<double> *vertices) : vertices_(vertices) {}

void RotateX::Transform(double value) noexcept {
  value *= M_PI / 180;
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    double temp_y = vertices_->operator[](i + 1);
    double temp_z = vertices_->operator[](i + 2);
    vertices_->operator[](i + 1) =
        temp_y * std::cos(value) + temp_z * std::sin(value);
    vertices_->operator[](i + 2) =
        -temp_y * std::sin(value) + temp_z * std::cos(value);
  }
}

RotateY::RotateY(std::vector<double> *vertices) : vertices_(vertices) {}

void RotateY::Transform(double value) noexcept {
  value *= M_PI / 180;
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    double temp_x = vertices_->operator[](i);
    double temp_z = vertices_->operator[](i + 2);
    vertices_->operator[](i) =
        temp_x * std::cos(value) + temp_z * std::sin(value);
    vertices_->operator[](i + 2) =
        -temp_x * std::sin(value) + temp_z * std::cos(value);
  }
}

RotateZ::RotateZ(std::vector<double> *vertices) : vertices_(vertices) {}

void RotateZ::Transform(double value) noexcept {
  value *= M_PI / 180;
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    double temp_x = vertices_->operator[](i);
    double temp_y = vertices_->operator[](i + 1);
    vertices_->operator[](i) =
        temp_x * std::cos(value) + temp_y * std::sin(value);
    vertices_->operator[](i + 1) =
        -temp_x * std::sin(value) + temp_y * std::cos(value);
  }
}

MoveX::MoveX(std::vector<double> *vertices) : vertices_(vertices) {}

void MoveX::Transform(double value) noexcept {
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    vertices_->operator[](i) += value;
  }
}

MoveY::MoveY(std::vector<double> *vertices) : vertices_(vertices) {}

void MoveY::Transform(double value) noexcept {
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    vertices_->operator[](i + 1) += value;
  }
}

MoveZ::MoveZ(std::vector<double> *vertices) : vertices_(vertices) {}

void MoveZ::Transform(double value) noexcept {
  for (std::size_t i = 0; i < vertices_->size(); i += 3) {
    vertices_->operator[](i + 2) += value;
  }
}

Scale::Scale(std::vector<double> *vertices) : vertices_(vertices) {}

void Scale::Transform(double value) noexcept {
  for (double &vertex : *vertices_) {
    vertex *= value;
  }
}

}  // namespace s21