#ifndef CPP4_3DVIEWER_V2_0_MODEL_COMMAND_H_
#define CPP4_3DVIEWER_V2_0_MODEL_COMMAND_H_

#include <vector>

namespace s21 {

class Command {
 public:
  enum Commands {
    kRotateX,
    kRotateY,
    kRotateZ,
    kMoveX,
    kMoveY,
    kMoveZ,
    kScale
  };

  virtual ~Command() = default;

  virtual void Transform(double value) noexcept = 0;
};

class RotateX : public Command {
 public:
  explicit RotateX(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class RotateY : public Command {
 public:
  explicit RotateY(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class RotateZ : public Command {
 public:
  explicit RotateZ(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class MoveX : public Command {
 public:
  explicit MoveX(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class MoveY : public Command {
 public:
  explicit MoveY(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class MoveZ : public Command {
 public:
  explicit MoveZ(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

class Scale : public Command {
 public:
  explicit Scale(std::vector<double> *vertices);
  void Transform(double value) noexcept override;

 private:
  std::vector<double> *vertices_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_MODEL_COMMAND_H_