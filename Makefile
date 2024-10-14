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

all: build

build: client_build

clean: client_clean

client_build: client_init client_compile
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) -o $(BUILD_DIR)/$(CLIENT_TARGET)

client_init:
	mkdir -p $(CLIENT_BUILD_DIR)
	mkdir -p $(CLIENT_BUILD_OBJS_DIR)

client_compile:
	$(CXX) -c $(CXXFLAGS) $(CLIENT_SRCS) -o $(CLIENT_OBJS)

client_clean:
	rm -rf $(CLIENT_BUILD_DIR)

client_run: client_build
	$(BUILD_DIR)/$(CLIENT_TARGET)

server_build: server_init server_compile
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) -o $(BUILD_DIR)/$(SERVER_TARGET)

server_init:
	mkdir -p $(SERVER_BUILD_DIR)
	mkdir -p $(SERVER_BUILD_OBJS_DIR)

server_compile:
	$(CXX) -c $(CXXFLAGS) $(SERVER_SRCS) -o $(SERVER_OBJS)

server_clean:
	rm -rf $(SERVER_BUILD_DIR)

server_run: server_build
	$(BUILD_DIR)/$(SERVER_TARGET)