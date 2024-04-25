#include "../controller/singleton.h"
#include "gtest/gtest.h"

s21::Controller *s21::Singleton::instance_ = nullptr;

static const double kPrecision = 1e5;

TEST(Test3DViewer, TestRead) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  std::size_t vertices =
      s21::Singleton::GetInstance()->GetVertices().size() / 3;
  std::size_t indices = s21::Singleton::GetInstance()->GetIndices().size() / 2;
  EXPECT_EQ(vertices, 6122);
  EXPECT_EQ(indices, 38148);
}

TEST(Test3DViewer, TestExceptions) {
  s21::Singleton::GetInstance()->SetFileName("");
  EXPECT_THROW(s21::Singleton::GetInstance()->ParseObj(), std::out_of_range);
}

TEST(Test3DViewer, TestRotateX) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kRotateX, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[0], -2.40469,
              kPrecision);
}

TEST(Test3DViewer, TestRotateY) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kRotateY, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[1], 2.71917,
              kPrecision);
}

TEST(Test3DViewer, TestRotateZ) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kRotateZ, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[3], -2.33435,
              kPrecision);
}

TEST(Test3DViewer, TestMoveX) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kMoveX, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[0], -1.40469,
              kPrecision);
}

TEST(Test3DViewer, TestMoveY) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kMoveY, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[1], 3.71917,
              kPrecision);
}

TEST(Test3DViewer, TestMoveZ) {
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kMoveZ, 1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetVertices()[2], -1.89007,
              kPrecision);
}

TEST(Test3DViewer, TestScale) {
  double max_vert = 7.31788;
  s21::Singleton::GetInstance()->SetFileName(
      std::string("../data-samples/skull.obj"));
  s21::Singleton::GetInstance()->ParseObj();
  s21::Singleton::GetInstance()->Transform(s21::Command::kScale, 1.1);
  EXPECT_NEAR(s21::Singleton::GetInstance()->GetMaxVertex(), max_vert,
              kPrecision);
}

int main(int argc, char **argv) {
  s21::Facade facade;
  s21::Singleton::GetInstance(&facade);
  testing::InitGoogleTest(&argc, argv);
  int tests = RUN_ALL_TESTS();
  s21::Singleton::DestroyInstance();
  return tests;
}