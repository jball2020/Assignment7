MyOthello: main.o game.o MyOthello.o Space.o
	g++ main.o game.o MyOthello.o Space.o -o MyOthello

main.o: main.cc
	g++ -c -Wall main.cc

game.o: game.cc
	g++ -c -Wall game.cc

MyOthello.o: MyOthello.cc
	g++ -c -Wall MyOthello.cc

Space.o: Space.cc
	g++ -c -Wall Space.cc

clean:
	rm -f *.o *~
