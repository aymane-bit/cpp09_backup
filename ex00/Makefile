CXX = c++

CXXFLAGS = -Wall -Wextra -Werror  -std=c++98

TARGET = btc

Header = BitcoinExchange.hpp

SRC = main.cpp BitcoinExchange.cpp

all: $(TARGET)

$(TARGET): $(SRC) $(Header)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re