#include <iostream>
#include <memory>
#include <vector>
#include <GL/glut.h>

#include "include/button.h"
#include "include/textfield.h"
#include "include/gameboard.h"
#include "include/client.h"

GLint WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

enum screen_t {
	SCREEN_NONE,
	SCREEN_HOME,
	SCREEN_CONNECT,
	SCREEN_GAME,
};

struct State {
	std::vector<std::unique_ptr<Object>> objects;
	screen_t currentScreen;
	screen_t nextScreen;

	std::vector<std::unique_ptr<Object>> toAddObjects;

	GLfloat mouseX, mouseY;
	GLint screenW, screenH;

	GameBoard *gameBoard;
	Label *statusLabel;

	std::unique_ptr<Client> client;

	State() : screenW(WINDOW_WIDTH), screenH(WINDOW_HEIGHT), nextScreen(SCREEN_NONE), gameBoard(nullptr) { }

	~State() {
		std::cout << "caboo" << std::endl;
	}

	void setNextScreen(screen_t screenId) {
		nextScreen = screenId;
	}

	void connect(std::string ip) {
		client.reset(new Client(ip, 5555));

		if (client->createConnection() != 0) {
			client.reset();

			statusLabel = new Label("Nao foi possivel conectar a " + ip + ":5555");
			statusLabel->setCoordinates(0.0, 0.92, 1.0, 0.08);

			toAddObjects.emplace_back(statusLabel);
		} else {
			std::cout << "deu bom\n";
		}
	}

	void setScreen(screen_t screenId) {
		currentScreen = screenId;

		objects.clear();

		Button *newGameButton, *connectButton;
		TextField *ipTextField;
		switch (screenId) {
			case SCREEN_HOME:
				newGameButton = new Button("Conectar ao meu pc", [&]() {
					connect("127.0.0.1");
				});
				newGameButton->setCoordinates(0.2, 0.2, 0.6, 0.2);

				connectButton = new Button("Conectar a outro pc", [&]() {
					setNextScreen(SCREEN_CONNECT);
				});
				connectButton->setCoordinates(0.2, 0.5, 0.6, 0.2);

				objects.clear();
				objects.emplace_back(newGameButton);
				objects.emplace_back(connectButton);
				break;
			case SCREEN_CONNECT:
				ipTextField = new TextField("IP: ", [&](std::string text) {
					std::string ip = text.substr(4);
					std::cerr << "Connecting to remote ip: " << ip << std::endl;
					connect(ip);
				});
				ipTextField->setCoordinates(0.3, 0.45, 0.4, 0.1);

				objects.clear();
				objects.emplace_back(ipTextField);
				break;
			case SCREEN_GAME:
				statusLabel = new Label("Status: ");
				statusLabel->setCoordinates(0.0, 0.92, 1.0, 0.08);

				gameBoard = new GameBoard();
				
				gameBoard->setSelectedBlock(0, 2);

				gameBoard->setCellCallback([&](GLint blockRow, GLint blockCol, GLint row, GLint col) {
					std::cout << "clicou no jogo (" << blockRow << ", " << blockCol << ") ";
					std::cout << "celula (" << row << ", " <<  col << ")\n";
				});

				/*Board b;
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						b.mat[i][j] = 1 + ((i + j) & 1);
					}
				}
				b.bigMat[0][1] = 1;
				b.bigMat[1][0] = 2;
				gameBoard->setBoard(b);*/

				objects.clear();
				objects.emplace_back(statusLabel);
				objects.emplace_back(gameBoard);
				break;
		}
	};

	void onMouseMoved(GLint x, GLint y) {
		mouseX = x / (1.0 * screenW);
		mouseY = 1.0 - y / (1.0 * screenH);
	}

	void onWindowResize(GLint newWidth, GLint newHeight) {
		screenW = newWidth;
		screenH = newHeight;
	}

	void onMouseClicked(GLint x, GLint y) {
		GLfloat mX = x / (1.0 * screenW);
		GLfloat mY = 1.0 - y / (1.0 * screenH);

		for (auto& obj : toAddObjects) {
			objects.emplace_back(obj.release());	
		}
		toAddObjects.clear();

		for (auto& obj : objects) {
			if (obj->isInside(mX, mY)) {
				obj->onClick(mX, mY);
			}
		}

		if (nextScreen != SCREEN_NONE) {
			setScreen(nextScreen);
			setNextScreen(SCREEN_NONE);
		}
	}

	void onKeyPressed(GLubyte key, GLint x, GLint y) {
		for (auto& obj : objects) {
			obj->onKeyPressed(key);
		}

		for (auto& obj : toAddObjects) {
			objects.emplace_back(obj.release());	
		}
		toAddObjects.clear();

		if (nextScreen != SCREEN_NONE) {
			setScreen(nextScreen);
			setNextScreen(SCREEN_NONE);
		}
	}

	void draw() {
		for (auto& obj : objects) {
			obj->draw(mouseX, mouseY, screenW, screenH);
		}
	}

	void update() {
		for (auto& obj : toAddObjects) {
			objects.emplace_back(obj.release());	
		}
		toAddObjects.clear();

		if (currentScreen == SCREEN_GAME) {
			if (gameBoard->isFinished()) {
				setNextScreen(SCREEN_HOME);
				gameBoard = nullptr;
				statusLabel = nullptr;
			}
		}

		if (nextScreen != SCREEN_NONE) {
			setScreen(nextScreen);
			setNextScreen(SCREEN_NONE);
		}
	}
} gState;

void init();
void displayFunc();
void mouseFunc(GLint button, GLint action, GLint x, GLint y);
void passiveFunc(GLint x, GLint y);
void reshapeFunc(GLint newWidth, GLint newHeight);
void keyboardFunc(GLubyte key, GLint x, GLint y);
void idleFunc();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	GLint screen_width = glutGet(GLUT_SCREEN_WIDTH),
	screen_height = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
	glutCreateWindow("CryptoVelha");

	init();

	gState.setScreen(SCREEN_HOME);

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutPassiveMotionFunc(passiveFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);

	glutMouseFunc(mouseFunc);

	glutMainLoop();

	return EXIT_SUCCESS;
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(0, 1, 0, 1);
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);

	gState.draw();
	
	glFlush();
}

void mouseFunc(GLint button, GLint action, GLint x, GLint y) {
	if (button == GLUT_LEFT && action == GLUT_DOWN) {
		gState.onMouseClicked(x, y);
	}
	glutPostRedisplay();
}

void passiveFunc(GLint x, GLint y) {
	gState.onMouseMoved(x, y);
	glutPostRedisplay();
}

void reshapeFunc(GLint newWidth, GLint newHeight) {
	gState.onWindowResize(newWidth, newHeight);

	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void keyboardFunc(GLubyte key, GLint x, GLint y) {
	gState.onKeyPressed(key, x, y);

	glutPostRedisplay();
}

void idleFunc() {
	gState.update();

	glutPostRedisplay();
}