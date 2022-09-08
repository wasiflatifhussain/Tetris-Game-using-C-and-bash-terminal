FLAGS = -pthread -pedantic-errors -std=c++11 -g

game: main.o io.o game_type.o
	g++ $(FLAGS) $^ -o game
	rm -f *.o
game_type.o: ./source/game_type.cpp ./source/game_type.h
	g++ $(FLAGS) -c $<
io.o: ./source/io.cpp ./source/io.h ./source/game_type.h
	g++ $(FLAGS) -c $<
main.o: ./source/main.cpp ./source/game_type.h ./source/io.h
	g++ $(FLAGS) -c $<

clean:
	rm -f *.o game
.PHONY: clean