# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lgtest -lgtest_main -pthread

# Directories
BUILD_DIR = build
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
TESTS_DIR = tests

# Source files
CLIENT_SRC = $(SRC_DIR)/client
SERVER_SRC = $(SRC_DIR)/server
COMMON_SRC = $(SRC_DIR)/common

# Test source files
CLIENT_TEST = $(TESTS_DIR)/client
SERVER_TEST = $(TESTS_DIR)/server
COMMON_TEST = $(TESTS_DIR)/common


# Targets
all: client server


# Main executables
client: $(BUILD_DIR)/client-main.o $(BUILD_DIR)/tcp-client.o $(BUILD_DIR)/utils.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^

server: $(BUILD_DIR)/server-main.o $(BUILD_DIR)/tcp-server.o $(BUILD_DIR)/utils.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^


# Object files for main executables
$(BUILD_DIR)/client-main.o: $(CLIENT_SRC)/client-main.cpp $(INCLUDE_DIR)/client/client-main.hpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

$(BUILD_DIR)/tcp-client.o: $(CLIENT_SRC)/tcp-client.cpp $(INCLUDE_DIR)/client/tcp-client.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

$(BUILD_DIR)/server-main.o: $(SERVER_SRC)/server-main.cpp $(INCLUDE_DIR)/server/server-main.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

$(BUILD_DIR)/tcp-server.o: $(SERVER_SRC)/tcp-server.cpp $(INCLUDE_DIR)/server/tcp-server.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

$(BUILD_DIR)/utils.o: $(COMMON_SRC)/utils.cpp $(INCLUDE_DIR)/common/utils.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)


# Test targets
test: client-test server-test

client-test: $(BUILD_DIR)/tcp-client-test.o $(BUILD_DIR)/utils-test.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

server-test: $(BUILD_DIR)/tcp-server-test.o $(BUILD_DIR)/utils-test.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)


# Object files for test targets
$(BUILD_DIR)/tcp-client-test.o: $(CLIENT_TEST)/tcp-client-test.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) -I$(SRC_DIR)

$(BUILD_DIR)/tcp-server-test.o: $(SERVER_TEST)/tcp-server-test.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) -I$(SRC_DIR)

$(BUILD_DIR)/utils-test.o: $(COMMON_TEST)/utils-test.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR) -I$(SRC_DIR)


# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

