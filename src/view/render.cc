#include "render.h"

#include <QSettings>
#include <cmath>

namespace s21 {

Render::Render(QWidget *parent) : QOpenGLWidget(parent) { LoadSettings(); }

Render::~Render() { SaveSettings(); }

void Render::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
}

void Render::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Render::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(style_.back_red, style_.back_green, style_.back_blue,
               style_.back_alfa);
  if (!Singleton::GetInstance()->GetVertices().empty() &&
      !Singleton::GetInstance()->GetIndices().empty()) {
    SetProjection();
    glRotated(x_rotate_, 1, 0, 0);
    glRotated(y_rotate_, 0, 1, 0);
    glTranslated(x_move_, y_move_, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0,
                    Singleton::GetInstance()->GetVertices().data());
    DrawLines();
    DrawPoints();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  update();
}

void Render::mousePressEvent(QMouseEvent *mouse) {
  x_start_ = mouse->pos().x();
  y_start_ = mouse->pos().y();
}

void Render::mouseMoveEvent(QMouseEvent *mouse) {
  if (mouse->buttons() & Qt::LeftButton) {
    y_rotate_ = y_rotate_ + (mouse->pos().x() - x_start_);
    x_rotate_ = x_rotate_ + (mouse->pos().y() - y_start_);
  } else if (mouse->buttons() & Qt::RightButton) {
    x_move_ += ((mouse->pos().x() - x_start_) / 200 *
                Singleton::GetInstance()->GetMaxVertex());
    y_move_ -= ((mouse->pos().y() - y_start_) / 200 *
                Singleton::GetInstance()->GetMaxVertex());
  }
  x_start_ = mouse->pos().x();
  y_start_ = mouse->pos().y();
}

void Render::wheelEvent(QWheelEvent *event) {
  float step = 1.0 + event->angleDelta().y() / 100 * 0.1;
  Singleton::GetInstance()->Transform(Command::kScale, step);
}

void Render::SaveSettings() {
  QSettings settings("Setting", "3D_Viewer");
  settings.setValue("back_red", style_.back_red);
  settings.setValue("back_green", style_.back_green);
  settings.setValue("back_blue", style_.back_blue);
  settings.setValue("back_alfa", style_.back_alfa);
  settings.setValue("edge_red", style_.edge_red);
  settings.setValue("edge_green", style_.edge_green);
  settings.setValue("edge_blue", style_.edge_blue);
  settings.setValue("edge_alfa", style_.edge_alfa);
  settings.setValue("vertex_red", style_.vertex_red);
  settings.setValue("vertex_green", style_.vertex_green);
  settings.setValue("vertex_blue", style_.vertex_blue);
  settings.setValue("vertex_alfa", style_.vertex_alfa);
  settings.setValue("vertex_width", style_.vertex_width);
  settings.setValue("line_width", style_.line_width);
  settings.setValue("projection_type", style_.projection_type);
  settings.setValue("vertex_type", style_.vertex_type);
  settings.setValue("edge_type", style_.edge_type);
  settings.sync();
}

void Render::LoadSettings() {
  QSettings settings("Setting", "3D_Viewer");
  style_.back_red = settings.value("back_red", 0.0f).toDouble();
  style_.back_green = settings.value("back_green", 0.0f).toDouble();
  style_.back_blue = settings.value("back_blue", 0.0f).toDouble();
  style_.back_alfa = settings.value("back_alfa", 1.0f).toDouble();
  style_.edge_red = settings.value("edge_red", 0.20784313725f).toDouble();
  style_.edge_green = settings.value("edge_green", 0.06274509803f).toDouble();
  style_.edge_blue = settings.value("edge_blue", 0.74901960784f).toDouble();
  style_.edge_alfa = settings.value("edge_alfa", 1.0f).toDouble();
  style_.vertex_red = settings.value("vertex_red", 0.54509803921f).toDouble();
  style_.vertex_green =
      settings.value("vertex_green", 0.0862745098f).toDouble();
  style_.vertex_blue = settings.value("vertex_blue", 1.0f).toDouble();
  style_.vertex_alfa = settings.value("vertex_alfa", 1.0f).toDouble();
  style_.vertex_width = settings.value("vertex_width", 0.0f).toDouble();
  style_.line_width = settings.value("line_width", 0.0f).toDouble();
  style_.projection_type = settings.value("projection_type", 0).toInt();
  style_.vertex_type = settings.value("vertex_type", 1).toInt();
  style_.edge_type = settings.value("edge_type", 0).toInt();
}

void Render::SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double draw_range = Singleton::GetInstance()->GetMaxVertex() * 2;
  if (!style_.projection_type) {
    glOrtho(-draw_range, draw_range, -draw_range, draw_range, -draw_range,
            draw_range * 5);
  } else {
    float fov = 60.0 * M_PI / 180;
    float heap_height = draw_range / (2 * std::tan(fov / 2));
    glFrustum(-draw_range, draw_range, -draw_range, draw_range, heap_height,
              draw_range * 5);
    glTranslated(0, 0, -heap_height * 3);
  }
}

void Render::DrawLines() {
  glColor4d(style_.edge_red, style_.edge_green, style_.edge_blue,
            style_.edge_alfa);
  glEnable(GL_LINE_STIPPLE);
  if (style_.edge_type) {
    glLineStipple(1, 0x00ff);
  } else {
    glLineStipple(0, 0xffff);
  }
  glLineWidth(style_.line_width);
  glDrawElements(GL_LINES, Singleton::GetInstance()->GetIndices().size(),
                 GL_UNSIGNED_INT,
                 Singleton::GetInstance()->GetIndices().data());
  glDisable(GL_LINE_STIPPLE);
}

void Render::DrawPoints() {
  if (style_.vertex_type) {
    glPointSize(style_.vertex_width);
    glColor4d(style_.vertex_red, style_.vertex_green, style_.vertex_blue,
              style_.vertex_alfa);
    if (style_.vertex_type == 1) glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0,
                 Singleton::GetInstance()->GetVertices().size() / 3);
    if (style_.vertex_type == 1) glDisable(GL_POINT_SMOOTH);
  }
}

}  // namespace s21