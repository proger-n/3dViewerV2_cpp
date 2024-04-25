#ifndef CPP4_3DVIEWER_V2_0_VIEW_RENDER_H_
#define CPP4_3DVIEWER_V2_0_VIEW_RENDER_H_

#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QMouseEvent>
#include <QOpenGLFunctions>

#include "view.h"

namespace s21 {

struct Style {
  double back_red, back_green, back_blue, back_alfa;
  double vertex_red, vertex_green, vertex_blue, vertex_alfa;
  double edge_red, edge_green, edge_blue, edge_alfa;
  double vertex_width, line_width;
  int projection_type, vertex_type, edge_type;
};

class Render : public QOpenGLWidget {
  Q_OBJECT
  friend class View;

 public:
  explicit Render(QWidget *parent = nullptr);
  ~Render();

 private:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *event) override;
  void SaveSettings();
  void LoadSettings();
  void SetProjection();
  void DrawLines();
  void DrawPoints();

  double x_rotate_{}, y_rotate_{};
  double x_move_{}, y_move_{};
  double x_start_{}, y_start_{};
  Style style_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_VIEW_RENDER_H_
