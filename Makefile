CXX = g++

CXXFLAGS = -g -Wall -Wextra -std=c++17

TARGET = RatingList
SRCS = RatingListDriver.cpp RatingItem.cpp RatingHash.cpp Filename_AVL.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) core
