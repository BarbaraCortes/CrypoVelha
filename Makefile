LINKS = -lsfml-graphics -lsfml-system -lsfml-window
OBJECTS = Fonts.o Button.o TextField.o

all: $(OBJECTS)
	g++ -o main main.cpp -std=c++0x $(OBJECTS) $(LINKS) -I./include -L./lib
	g++ -o client client.cpp
	g++ -o server server.cpp
%.o: %.cpp
	g++ -o $@ -c $< -std=c++0x -I./include
clean:
	rm *.o
