#include <QApplication>

#include "view.h"

s21::Controller *s21::Singleton::instance_ = nullptr;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade facade;
  s21::Singleton::GetInstance(&facade);
  s21::View view;
  view.show();
  return a.exec();
}