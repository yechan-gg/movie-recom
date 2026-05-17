# 컴파일러 설정
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# 파일 설정
TARGET = Movie_Recommender
SRCDIR = src
OBJDIR = obj

SRCS = 	$(SRCDIR)/main.cpp \
		$(SRCDIR)/Movie.cpp \
		$(SRCDIR)/Rating.cpp \
		$(SRCDIR)/User.cpp \
		$(SRCDIR)/MovieManager.cpp \
		$(SRCDIR)/UserManager.cpp \
		$(SRCDIR)/RatingManager.cpp
		
OBJS = 	$(OBJDIR)/main.o \
		$(OBJDIR)/Movie.o \
		$(OBJDIR)/Rating.o \
		$(OBJDIR)/User.o \
		$(OBJDIR)/MovieManager.o \
		$(OBJDIR)/UserManager.o \
		$(OBJDIR)/RatingManager.o

# 기본 타겟
all: $(TARGET)

# 링크
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 컴파일 규칙
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(OBJDIR):
	mkdir -p $(OBJDIR)

# 정리
clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$<

# .PHONY: 파일이 아닌 타겟 명시
.PHONY: all clean