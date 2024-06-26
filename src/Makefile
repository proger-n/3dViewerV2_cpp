OS = $(shell uname)
CC = -Wall -Wextra -Werror -std=c++17
FLAGS = -lgtest -lpthread -fprofile-arcs -ftest-coverage
TEST_C = $(shell find tests -name "*.cc")
CONTROLLER_C = $(shell find controller -name "*.cc")
MODEL_C = $(shell find model -name "*.cc")

ifeq ($(OS),Darwin)
	OPEN_CMD = open
	APP = 3DViewerV2.0.app
	OPEN_APP = $(OPEN_CMD) $(APP)
else
	FLAGS += -lm -lrt -lsubunit
	OPEN_CMD = xdg-open
	APP = 3DViewerV2.0
	OPEN_APP = ./$(APP)
endif

all: clean install open

install: clean
	cd view && qmake6 && make && make clean

uninstall:
	cd view && rm -rf Makefile ../$(APP) view.pro.user .qmake.stash .qtc_clangd .tmp

open:
	$(OPEN_APP)

dvi:
	$(OPEN_CMD) README.md

dist: clean install
	cd .. && tar -czvf src/3DViewerV2.0.tar.gz src

clang:
	clang-format --style=Google -i $(shell find . -name "*.cc" -o -name "*.h")

test: clean
	g++ $(CC) $(TEST_C) $(CONTROLLER_C) $(MODEL_C) $(FLAGS) -lgcov -coverage -o test
	./test

gcov_report: clean test
	lcov -t "./test"  -o report.info --ignore-errors mismatch --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

clean: uninstall
	rm -rf $(shell find . -name "*.o") *.a test *.gcda *.gcno *.info report 3DViewerV2.0.tar.gz