LINKS = -lsfml-graphics -lsfml-system -lsfml-window
OBJECTS = Fonts.o Button.o TextField.o

all: $(OBJECTS)
	g++ -o main main.cpp $(OBJECTS) $(LINKS) -I./include
	g++ -o client client.cpp
	g++ -o server server.cpp
%.o: %.cpp
	g++ -o $@ -c $< -std=c++11 -I./include
clean:
	rm *.o