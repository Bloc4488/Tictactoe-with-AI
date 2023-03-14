#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17

__start__: tictactoe
	./tictactoe

tictactoe: obj obj/main.o obj/Board.o obj/Game.o obj/Player.o
	g++ -Wall -pedantic -std=c++17 -o tictactoe obj/main.o obj/Board.o obj/Game.o obj/Player.o

obj:
	mkdir obj

obj/main.o: src/main.cpp 
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Board.o: src/Board.cpp inc/Board.hpp
	g++ -c ${CXXFLAGS} -o obj/Board.o src/Board.cpp

obj/Game.o: src/Game.cpp inc/Game.hpp
	g++ -c ${CXXFLAGS} -o obj/Game.o src/Game.cpp
	
obj/Player.o: src/Player.cpp inc/Player.hpp
	g++ -c ${CXXFLAGS} -o obj/Player.o src/Player.cpp

clean:
	rm -f obj/*.o tictactoe
