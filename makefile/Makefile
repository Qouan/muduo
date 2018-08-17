MUDUO_DIRECTORY = /home/qouan/Downloads/build/release-install
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib
SRC = ../src
#//Wall
CXXFLAGS = -g -O0  -Wextra -Werror -std=c++11\
	   -Wconversion -Wno-unused-parameter \
	   -Wold-style-cast -Woverloaded-virtual \
	   -Wpointer-arith -Wshadow -Wwrite-strings \
	   -march=native -rdynamic \
	   -I$(MUDUO_INCLUDE)

LDFLAGS = -L$(MUDUO_LIBRARY) -lmuduo_net -lmuduo_base -lpthread -lrt

all: main
clean:
	rm -f main *log
	#rm -f  *log

main: $(SRC)/main.cpp
	g++ $(CXXFLAGS) -o $@  $^ $(LDFLAGS)

#.PHONY: all clean
