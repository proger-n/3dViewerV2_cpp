#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include "../model/facade.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Facade *Facade);
  ~Controller() = default;

  void ParseObj();
  void Transform(int command, double value);

  void SetFileName(const std::string &file_name);
  std::vector<double> &GetVertices() noexcept;
  std::vector<unsigned int> &GetIndices() noexcept;
  double GetMaxVertex() const noexcept;

 private:
  Facade *facade_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_CONTROLLER_H_