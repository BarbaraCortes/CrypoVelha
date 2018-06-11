LINKS_C = -framework OpenGL -framework GLUT
LINKS_S =
OBJECTS_C = object.o button.o textfield.o gameboard.o label.o board.o client.o protocol.o
OBJECTS_S = bigGame.o game.o server.o gameController.o

all: $(OBJECTS_C) $(OBJECTS_S)
	g++ -g -o main main.cpp -std=c++0x $(OBJECTS_C) $(LINKS_C) -I.
	g++ -g -o server mainServer.cpp -std=c++0x $(OBJECTS_S) $(LINKS_S) -I.
server: $(OBJECTS_S)
	g++ -o server mainServer.cpp -std=c++0x $(OBJECTS_S) $(LINKS_S) -I.
client: $(OBJECTS_C)
	g++ -o main main.cpp -std=c++0x $(OBJECTS_C) $(LINKS_C) -I.
%.o: %.cpp
	g++ -o $@ -c $< -std=c++0x -I.

clean:
	rm *.o
