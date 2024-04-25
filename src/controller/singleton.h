#ifndef CPP4_3DVIEWER_V2_0_CONTROLLER_SINGLETON_H_
#define CPP4_3DVIEWER_V2_0_CONTROLLER_SINGLETON_H_

#include "controller.h"

namespace s21 {

class Singleton {
 public:
  Singleton() = delete;
  Singleton(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;

  Singleton &operator=(const Singleton &other) = delete;

  static Controller *GetInstance(Facade *facade = nullptr);
  static void DestroyInstance();

 private:
  static Controller *instance_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_CONTROLLER_SINGLETON_H_