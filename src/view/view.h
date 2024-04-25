#ifndef CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
#define CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_

#include <QMainWindow>
#include <QTimer>

#include "../controller/singleton.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void OpenFile();
  void SetBackgroundColor();
  void SetVerticesColor();
  void SetEdgesColor();
  void SetVerticesWidth(double arg1);
  void SetEdgesWidth(double arg1);
  void SetProjection();
  void SetVerticesType();
  void SetEdgesType();
  void MakeScreenshot();
  void MakeRecord();
  void CreateGif();
  void RotateXLeft();
  void RotateXRight();
  void RotateYLeft();
  void RotateYRight();
  void RotateZLeft();
  void RotateZRight();
  void TranslateXLeft();
  void TranslateXRight();
  void TranslateYLeft();
  void TranslateYRight();
  void TranslateZLeft();
  void TranslateZRight();
  void ScaleDown();
  void ScaleUp();

 private:
  void GetColorPicker(double *red, double *green, double *blue, double *alpha);
  void LoadUiState();
  void ConnectButtons();

  Ui::View *ui_;
  QGifImage *gif_;
  QTimer timer_;
  int frame_count_{};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
