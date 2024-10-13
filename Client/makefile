CXX := g++
CXXFLAGS := -std=c++11
TARGET := client

SRC_DIR = ./src
BUILD_DIR = ./build
BUILD_OBJS_DIR = ./build/objs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(BUILD_OBJS_DIR)/$(notdir $(SRCS:.cpp=.o))

all: $(TARGET)

init:
	mkdir $(BUILD_DIR)
	mkdir $(BUILD_OBJS_DIR)

compile:
	$(CXX) -c $(CXXFLAGS) $(SRCS) -o $(OBJS)

$(TARGET): compile
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BUILD_DIR)/$@

clean:
	rm -rf ./build

run: all
	./build/$(TARGET)
