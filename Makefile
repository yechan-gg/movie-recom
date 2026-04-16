# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# 파일 설정
TARGET = Movie_Recommender
SRCS = main.cpp Movie.cpp Rating.cpp User.cpp MovieManager.cpp UserManager.cpp
OBJS = main.o Movie.o Rating.o User.o MovieManager.o UserManager.o

# 기본 타겟
all: $(TARGET)

# 링크
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 컴파일 규칙

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# main.o: main.cpp calculator.h
# 	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
# calculator.o: calculator.cpp calculator.h
# 	$(CXX) $(CXXFLAGS) -c calculator.cpp -o calculator.o


# 정리
clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$<

# .PHONY: 파일이 아닌 타겟 명시
.PHONY: all clean