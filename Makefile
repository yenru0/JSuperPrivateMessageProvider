CXX := g++
CXXFLAGS := -std=c++11

BUILD_DIR = ./build

CLIENT_TARGET = client.run

CLIENT_SRC_DIR = ./Client/src
CLIENT_BUILD_DIR = ./build/client
CLIENT_BUILD_OBJS_DIR = ./build/client/objs

CLIENT_SRCS = $(wildcard $(CLIENT_SRC_DIR)/*.cpp)
CLIENT_OBJS = $(CLIENT_BUILD_OBJS_DIR)/$(notdir $(CLIENT_SRCS:.cpp=.o))

SERVER_TARGET = server.run

SERVER_SRC_DIR = ./Server/src
SERVER_BUILD_DIR = ./build/server
SERVER_BUILD_OBJS_DIR = ./build/server/objs

SERVER_SRCS = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJS = $(SERVER_BUILD_OBJS_DIR)/$(notdir $(SERVER_SRCS:.cpp=.o))

COMMON_SRC_DIR = ./Common/src
COMMON_BUILD_DIR = ./build/common
COMMON_BUILD_OBJS_DIR = ./build/common/objs

COMMON_SRCS = $(wildcard $(COMMON_SRC_DIR)/*.cpp)
COMMON_OBJS = $(COMMON_BUILD_OBJS_DIR)/$(notdir $(COMMON_SRCS:.cpp=.o))

COMMON_INCLUDE = $(wildcard $(COMMON_SRC_DIR)/*.h)
all: build

build: client_build server_build

clean: client_clean server_clean common_clean

client_build: client_init common_compile client_compile
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) $(COMMON_OBJS) -o $(BUILD_DIR)/$(CLIENT_TARGET)

client_init:
	mkdir -p $(CLIENT_BUILD_DIR)
	mkdir -p $(CLIENT_BUILD_OBJS_DIR)

client_compile:
	$(CXX) -c $(CXXFLAGS) $(CLIENT_SRCS) -I $(COMMON_SRC_DIR) -o $(CLIENT_OBJS)

client_clean:
	rm -rf $(CLIENT_BUILD_DIR)

client_run: client_build
	$(BUILD_DIR)/$(CLIENT_TARGET)

server_build: server_init common_compile server_compile
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) $(COMMON_OBJS) -o $(BUILD_DIR)/$(SERVER_TARGET)

server_init:
	mkdir -p $(SERVER_BUILD_DIR)
	mkdir -p $(SERVER_BUILD_OBJS_DIR)

server_compile:
	$(CXX) -c $(CXXFLAGS) $(SERVER_SRCS) -I $(COMMON_SRC_DIR) -o $(SERVER_OBJS)

server_clean:
	rm -rf $(SERVER_BUILD_DIR)

server_run: server_build
	$(BUILD_DIR)/$(SERVER_TARGET)

common_init:
	mkdir -p $(COMMON_BUILD_DIR)
	mkdir -p $(COMMON_BUILD_OBJS_DIR)

common_compile: common_init
	$(CXX) -c $(CXXFLAGS) $(COMMON_SRCS) -o $(COMMON_OBJS)

common_clean:
	rm -rf $(COMMON_BUILD_DIR)