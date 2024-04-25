#include "singleton.h"

namespace s21 {

Controller *Singleton::GetInstance(Facade *facade) {
  if (!instance_) {
    instance_ = new Controller(facade);
  }
  return instance_;
}

void Singleton::DestroyInstance() {
  if (instance_) {
    delete instance_;
  }
  instance_ = nullptr;
}

}  // namespace s21