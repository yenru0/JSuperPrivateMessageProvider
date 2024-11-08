CXX := g++
CXXFLAGS := -std=c++11

BUILD_DIR = ./build

CLIENT_TARGET = client.run

CLIENT_SRC_DIR = ./Client/src
CLIENT_BUILD_DIR = ./build/client
CLIENT_BUILD_OBJS_DIR = ./build/client/objs

CLIENT_SRCS = $(wildcard $(CLIENT_SRC_DIR)/*.cpp)
CLIENT_OBJS = $(CLIENT_SRCS:$(CLIENT_SRC_DIR)/%.cpp=$(CLIENT_BUILD_OBJS_DIR)/%.o)

SERVER_TARGET = server.run

SERVER_SRC_DIR = ./Server/src
SERVER_BUILD_DIR = ./build/server
SERVER_BUILD_OBJS_DIR = ./build/server/objs

SERVER_SRCS = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJS = $(SERVER_SRCS:$(SERVER_SRC_DIR)/%.cpp=$(SERVER_BUILD_OBJS_DIR)/%.o)

COMMON_SRC_DIR = ./Common/src
COMMON_BUILD_DIR = ./build/common
COMMON_BUILD_OBJS_DIR = ./build/common/objs

COMMON_SRCS = $(wildcard $(COMMON_SRC_DIR)/*.cpp)
COMMON_OBJS = $(COMMON_SRCS:$(COMMON_SRC_DIR)/%.cpp=$(COMMON_BUILD_OBJS_DIR)/%.o)

COMMON_INCLUDE = $(wildcard $(COMMON_SRC_DIR)/*.h)
all: build

build: common_init client_build server_build

clean: client_clean server_clean common_clean

client_build: client_init $(COMMON_OBJS) $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJS) $(COMMON_OBJS) -o $(BUILD_DIR)/$(CLIENT_TARGET)

client_init:
	mkdir -p $(CLIENT_BUILD_DIR)
	mkdir -p $(CLIENT_BUILD_OBJS_DIR)

$(CLIENT_BUILD_OBJS_DIR)/%.o: $(CLIENT_SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) -I $(COMMON_SRC_DIR) -o $@ $<

client_clean:
	rm -rf $(CLIENT_BUILD_DIR)

client_run: client_build
	$(BUILD_DIR)/$(CLIENT_TARGET)

server_build: server_init $(COMMON_OBJS) $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJS) $(COMMON_OBJS) -o $(BUILD_DIR)/$(SERVER_TARGET)

server_init:
	mkdir -p $(SERVER_BUILD_DIR)
	mkdir -p $(SERVER_BUILD_OBJS_DIR)

$(SERVER_BUILD_OBJS_DIR)/%.o: $(SERVER_SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) -I $(COMMON_SRC_DIR) -o $@ $<

server_clean:
	rm -rf $(SERVER_BUILD_DIR)

server_run: server_build
	$(BUILD_DIR)/$(SERVER_TARGET)

common_init:
	mkdir -p $(COMMON_BUILD_DIR)
	mkdir -p $(COMMON_BUILD_OBJS_DIR)

$(COMMON_BUILD_OBJS_DIR)/%.o: $(COMMON_SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

common_clean:
	rm -rf $(COMMON_BUILD_DIR)