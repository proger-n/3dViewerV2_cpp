#ifndef CPP4_3DVIEWER_V2_0_MODEL_FACADE_H_
#define CPP4_3DVIEWER_V2_0_MODEL_FACADE_H_

#include <string>
#include <vector>

#include "command.h"
#include "parser.h"

namespace s21 {

class Facade {
 public:
  Facade();
  ~Facade();

  void ParseObj();
  void Transform(int command, double value) noexcept;
  void SetFileName(const std::string &file_name);
  std::vector<double> &GetVertices() noexcept;
  std::vector<unsigned int> &GetIndices() noexcept;
  double GetMaxVertex() const noexcept;

 private:
  std::vector<double> vertices_;
  std::vector<unsigned int> indices_;
  Parser *parser_;
  std::vector<Command *> commands_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_MODEL_FACADE_H_