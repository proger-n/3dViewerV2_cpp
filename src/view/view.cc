#include "view.h"

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "./ui_view.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::View), gif_(nullptr) {
  ui_->setupUi(this);
  setWindowTitle("3DViewer");
  LoadUiState();
  connect(&timer_, SIGNAL(timeout()), this, SLOT(CreateGif()));
  ConnectButtons();
}

View::~View() {
  delete ui_;
  if (gif_) {
    delete gif_;
  }
  Singleton::DestroyInstance();
}

void View::OpenFile() {
  setlocale(LC_ALL, "C");
  QString path =
      QFileDialog::getOpenFileName(nullptr, "Open a file", "", "file(*.obj)");
  try {
    Singleton::GetInstance()->SetFileName(path.toStdString());
    Singleton::GetInstance()->ParseObj();
  } catch (std::exception &e) {
    path = "Choose .obj file";
    Singleton::GetInstance()->SetFileName("");
    QMessageBox::information(nullptr, "Error", "Unable to load an object.");
  }
  ui_->ObjectName->setText(path);
  ui_->VerticesCount->setText(
      QString::number(Singleton::GetInstance()->GetVertices().size() / 3));
  ui_->EdgesCount->setText(
      QString::number(Singleton::GetInstance()->GetIndices().size() / 2));
}

void View::SetBackgroundColor() {
  GetColorPicker(&ui_->Render->style_.back_red, &ui_->Render->style_.back_green,
                 &ui_->Render->style_.back_blue,
                 &ui_->Render->style_.back_alfa);
}

void View::SetVerticesColor() {
  GetColorPicker(
      &ui_->Render->style_.vertex_red, &ui_->Render->style_.vertex_green,
      &ui_->Render->style_.vertex_blue, &ui_->Render->style_.vertex_alfa);
}

void View::SetEdgesColor() {
  GetColorPicker(&ui_->Render->style_.edge_red, &ui_->Render->style_.edge_green,
                 &ui_->Render->style_.edge_blue,
                 &ui_->Render->style_.edge_alfa);
}

void View::SetVerticesWidth(double arg1) {
  ui_->Render->style_.vertex_width = arg1;
}

void View::SetEdgesWidth(double arg1) { ui_->Render->style_.line_width = arg1; }

void View::SetProjection() {
  ui_->Render->style_.projection_type = ui_->CentralProjection->isChecked();
}

void View::SetVerticesType() {
  if (ui_->VerticesTypeNone->isChecked()) {
    ui_->Render->style_.vertex_type = 0;
  } else if (ui_->VerticesTypeCircle->isChecked()) {
    ui_->Render->style_.vertex_type = 1;
  } else {
    ui_->Render->style_.vertex_type = 2;
  }
}

void View::SetEdgesType() {
  ui_->Render->style_.edge_type = ui_->EdgesTypeDashed->isChecked();
}

void View::MakeScreenshot() {
  QString path = QFileDialog::getSaveFileName(nullptr, "Save Screenshot", "",
                                              "BMP (*.bmp);;JPEG (*.jpg)");
  if (!path.isEmpty()) {
    ui_->Render->grabFramebuffer().save(path);
  }
}

void View::MakeRecord() {
  if (!gif_) {
    gif_ = new QGifImage;
    timer_.start(100);
  }
}

void View::CreateGif() {
  if (frame_count_ < 50) {
    QImage image_ = ui_->Render->grabFramebuffer();
    gif_->addFrame(image_);
    ++frame_count_;
  } else {
    frame_count_ = 0;
    timer_.stop();
    QString filename = QFileDialog::getSaveFileName(nullptr, tr("Save a gif"),
                                                    "", tr("gif (*.gif)"));
    if (!filename.isEmpty()) {
      gif_->save(filename);
    }
    delete gif_;
    gif_ = nullptr;
  }
}

void View::RotateXLeft() {
  Singleton::GetInstance()->Transform(Command::kRotateX,
                                      -(ui_->RotationAngleValue->value()));
}

void View::RotateXRight() {
  Singleton::GetInstance()->Transform(Command::kRotateX,
                                      ui_->RotationAngleValue->value());
}

void View::RotateYLeft() {
  Singleton::GetInstance()->Transform(Command::kRotateY,
                                      -(ui_->RotationAngleValue->value()));
}

void View::RotateYRight() {
  Singleton::GetInstance()->Transform(Command::kRotateY,
                                      ui_->RotationAngleValue->value());
}

void View::RotateZLeft() {
  Singleton::GetInstance()->Transform(Command::kRotateZ,
                                      -(ui_->RotationAngleValue->value()));
}

void View::RotateZRight() {
  Singleton::GetInstance()->Transform(Command::kRotateZ,
                                      ui_->RotationAngleValue->value());
}

void View::TranslateXLeft() {
  Singleton::GetInstance()->Transform(Command::kMoveX,
                                      -(ui_->TranslateStepValue->value()));
}

void View::TranslateXRight() {
  Singleton::GetInstance()->Transform(Command::kMoveX,
                                      ui_->TranslateStepValue->value());
}

void View::TranslateYLeft() {
  Singleton::GetInstance()->Transform(Command::kMoveY,
                                      -ui_->TranslateStepValue->value());
}

void View::TranslateYRight() {
  Singleton::GetInstance()->Transform(Command::kMoveY,
                                      ui_->TranslateStepValue->value());
}

void View::TranslateZLeft() {
  Singleton::GetInstance()->Transform(Command::kMoveZ,
                                      -(ui_->TranslateStepValue->value()));
}

void View::TranslateZRight() {
  Singleton::GetInstance()->Transform(Command::kMoveZ,
                                      ui_->TranslateStepValue->value());
}

void View::ScaleDown() {
  Singleton::GetInstance()->Transform(Command::kScale, 0.9);
}

void View::ScaleUp() {
  Singleton::GetInstance()->Transform(Command::kScale, 1.1);
}

void View::GetColorPicker(double *red, double *green, double *blue,
                          double *alpha) {
  QColorDialog dialog(nullptr);
  int red_int = 0, green_int = 0, blue_int = 0, alpha_int = 0;
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  QColor color = dialog.getColor();
  if (color.isValid()) {
    color.getRgb(&red_int, &green_int, &blue_int, &alpha_int);
    *red = red_int / 255.0;
    *green = green_int / 255.0;
    *blue = blue_int / 255.0;
    *alpha = alpha_int / 255.0;
  }
}

void View::LoadUiState() {
  if (!ui_->Render->style_.projection_type) {
    ui_->ParallelProjection->setChecked(true);
  } else {
    ui_->CentralProjection->setChecked(true);
  }

  if (!ui_->Render->style_.vertex_type) {
    ui_->VerticesTypeNone->setChecked(true);
  } else if (ui_->Render->style_.vertex_type == 1) {
    ui_->VerticesTypeCircle->setChecked(true);
  } else {
    ui_->VerticesTypeSquare->setChecked(true);
  }

  if (!ui_->Render->style_.edge_type) {
    ui_->EdgesTypeSolid->setChecked(true);
  } else {
    ui_->EdgesTypeDashed->setChecked(true);
  }

  ui_->EdgesWidthValue->setValue(ui_->Render->style_.line_width);
  ui_->VerticesWidthValue->setValue(ui_->Render->style_.vertex_width);
}

void View::ConnectButtons() {
  connect(ui_->OpenFile, SIGNAL(clicked(bool)), this, SLOT(OpenFile()));
  connect(ui_->BackgroundColor, SIGNAL(clicked(bool)), this,
          SLOT(SetBackgroundColor()));
  connect(ui_->VerticesColor, SIGNAL(clicked(bool)), this,
          SLOT(SetVerticesColor()));
  connect(ui_->EdgesColor, SIGNAL(clicked(bool)), this, SLOT(SetEdgesColor()));
  connect(ui_->VerticesWidthValue, SIGNAL(valueChanged(double)), this,
          SLOT(SetVerticesWidth(double)));
  connect(ui_->EdgesWidthValue, SIGNAL(valueChanged(double)), this,
          SLOT(SetEdgesWidth(double)));
  connect(ui_->ParallelProjection, SIGNAL(clicked(bool)), this,
          SLOT(SetProjection()));
  connect(ui_->CentralProjection, SIGNAL(clicked(bool)), this,
          SLOT(SetProjection()));
  connect(ui_->VerticesTypeNone, SIGNAL(clicked(bool)), this,
          SLOT(SetVerticesType()));
  connect(ui_->VerticesTypeCircle, SIGNAL(clicked(bool)), this,
          SLOT(SetVerticesType()));
  connect(ui_->VerticesTypeSquare, SIGNAL(clicked(bool)), this,
          SLOT(SetVerticesType()));
  connect(ui_->EdgesTypeDashed, SIGNAL(clicked(bool)), this,
          SLOT(SetEdgesType()));
  connect(ui_->EdgesTypeSolid, SIGNAL(clicked(bool)), this,
          SLOT(SetEdgesType()));
  connect(ui_->MakeScreenshot, SIGNAL(clicked(bool)), this,
          SLOT(MakeScreenshot()));
  connect(ui_->MakeRecord, SIGNAL(clicked(bool)), this, SLOT(MakeRecord()));
  connect(ui_->RotateXLeft, SIGNAL(clicked(bool)), this, SLOT(RotateXLeft()));
  connect(ui_->RotateXRight, SIGNAL(clicked(bool)), this, SLOT(RotateXRight()));
  connect(ui_->RotateYLeft, SIGNAL(clicked(bool)), this, SLOT(RotateYLeft()));
  connect(ui_->RotateYRight, SIGNAL(clicked(bool)), this, SLOT(RotateYRight()));
  connect(ui_->RotateZLeft, SIGNAL(clicked(bool)), this, SLOT(RotateZLeft()));
  connect(ui_->RotateZRight, SIGNAL(clicked(bool)), this, SLOT(RotateZRight()));
  connect(ui_->TranslateXLeft, SIGNAL(clicked(bool)), this,
          SLOT(TranslateXLeft()));
  connect(ui_->TranslateXRight, SIGNAL(clicked(bool)), this,
          SLOT(TranslateXRight()));
  connect(ui_->TranslateYLeft, SIGNAL(clicked(bool)), this,
          SLOT(TranslateYLeft()));
  connect(ui_->TranslateYRight, SIGNAL(clicked(bool)), this,
          SLOT(TranslateYRight()));
  connect(ui_->TranslateZLeft, SIGNAL(clicked(bool)), this,
          SLOT(TranslateZLeft()));
  connect(ui_->TranslateZRight, SIGNAL(clicked(bool)), this,
          SLOT(TranslateZRight()));
  connect(ui_->ScaleDown, SIGNAL(clicked(bool)), this, SLOT(ScaleDown()));
  connect(ui_->ScaleUp, SIGNAL(clicked(bool)), this, SLOT(ScaleUp()));
}

}  // namespace s21
