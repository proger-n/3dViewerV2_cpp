#ifndef CPP4_3DVIEWER_V2_0_MODEL_PARSER_H_
#define CPP4_3DVIEWER_V2_0_MODEL_PARSER_H_

namespace s21 {

class Parser {
 public:
  Parser(std::vector<double> *vertices, std::vector<unsigned int> *indices);
  ~Parser() = default;

  void ParseObj();
  void SetFileName(const std::string &file_name);
  double GetMaxVertex() const noexcept;

 private:
  void ParseVertices(std::string &&line);
  void ParseIndices(std::string &&line);
  int LineToIndex(std::string &&line);

  std::string file_name_;
  std::vector<double> *vertices_;
  std::vector<unsigned int> *indices_;
  double max_vertex_{};
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_MODEL_PARSER_H_
