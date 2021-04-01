//Individual Project 2D Game Application -- Todescu Paul Eugen

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
// set the default values
double basket_position = 0;

double square1_x1 = -6;
double square1_x2 = -7;
double square1_y = 14;

double square2_x1 = -3;
double square2_x2 = -4;
double square2_y = 22;

double square3_x1 = -0;
double square3_x2 = -1;
double square3_y = 10;

double square4_x1 = 3;
double square4_x2 = 2;
double square4_y = 18;

double square5_x1 = 6;
double square5_x2 = 5;
double square5_y = 26;

int score = 0;
int stage = 1;
double countdown = 11;
int lives = 5;

double speed_multiplier = 0.0;

bool startRound = false;
bool pauseRound = false;
bool endRound = false;
bool rulesMenu = false;

int startMenuOption = 0;
int pauseMenuOption = 0;
int endMenuOption = 0;
int rulesMenuOption = 0;

string Score = "SCORE:     ";
const char* getScore() // updates the score
{
	string str = to_string(score);
	if (str.length() == 1)
		Score[7] = str[0];
	if (str.length() == 2) {
		Score[7] = str[0];
		Score[8] = str[1];
	}
	if (str.length() == 3) {
		Score[7] = str[0];
		Score[8] = str[1];
		Score[9] = str[2];
	}
	if (str.length() == 4) {
		Score[7] = str[0];
		Score[8] = str[1];
		Score[9] = str[2];
		Score[10] = str[3];
	}
	return Score.c_str();
}

string Remaining_time = "TIME LEFT:   ";
const char* remainng_time() //updates the countdown
{
	if (countdown >= 0) {
		string str = to_string((int)countdown);
		if (str.length() == 1) {
			Remaining_time[11] = '0';
			Remaining_time[12] = str[0];
		}
		if (str.length() == 2) {
			Remaining_time[11] = str[0];
			Remaining_time[12] = str[1];
		}
		return Remaining_time.c_str();
	}
}

string Stage = "STAGE:   ";
const char* current_stage() // updates the stage
{
	string str = to_string(stage);
	if (str.length() == 1)
		Stage[7] = str[0];
	if (str.length() == 2) {
		Stage[7] = str[0];
		Stage[8] = str[1];
	}
	return Stage.c_str();
}

string Remaining_lives = "LIVES:   ";
const char* remaining_lives() // updates the remaining lives
{
	if (lives >= 0) {
		string str = to_string(lives);
		if (str.length() == 1) {
			Remaining_lives[7] = ' ';
			Remaining_lives[8] = str[0];
		}
	}
	return Remaining_lives.c_str();
}


void renderBitmapString(float x, float y, const char* string) // renders text
{
	int len;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2i(x, y);

	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)string[i]);
	}
}

void resetGame()
{   // reset all variables to their default values
	basket_position = 0;
	square1_x1 = -6;
	square1_x2 = -7;
	square1_y = 14;
	square2_x1 = -3;
	square2_x2 = -4;
	square2_y = 22;
	square3_x1 = -0;
	square3_x2 = -1;
	square3_y = 10;
	square4_x1 = 3;
	square4_x2 = 2;
	square4_y = 18;
	square5_x1 = 6;
	square5_x2 = 5;
	square5_y = 26;
	score = 0;
	stage = 1;
	countdown = 11;
	lives = 5;
	speed_multiplier = 0.0;
	startRound = false;
	pauseRound = false;
	endRound = false;
	rulesMenu = false;
	startMenuOption = 0;
	pauseMenuOption = 0;
	endMenuOption = 0;
	Score = "SCORE:     ";
	Remaining_time = "TIME LEFT:   ";
	Stage = "STAGE:   ";
	Remaining_lives = "LIVES:   ";
}

void regularKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 13: // carriage return key
		if (startMenuOption == 0 && startRound == false)
			startRound = true;

		else if (pauseMenuOption == 0 && pauseRound == true)
			pauseRound = false;

		else if (startMenuOption == 1 && startRound == false && rulesMenu == false) {
			rulesMenu = true;
		}

		else if (rulesMenuOption == 0 && rulesMenu == true) {
			rulesMenu = false;
		}

		else if (pauseMenuOption == 1) {
			exit(0);
		}

		else if (startMenuOption == 2)
			exit(0);


		else if (endMenuOption == 0) {
			resetGame();
		}

		else if (endMenuOption == 1)
			exit(0);

		break;

	case 27: // escape key
		pauseRound = true;
		break;
	}
}

void specialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		if (basket_position > -7)
		{
			basket_position -= 1;
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		if (basket_position < 7)
		{
			basket_position += 1;
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_UP:
		if (startMenuOption > 0)
			startMenuOption -= 1;
		if (pauseMenuOption > 0)
			pauseMenuOption -= 1;
		if (endMenuOption > 0)
			endMenuOption -= 1;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		if (startMenuOption < 2)
			startMenuOption += 1;
		if (pauseMenuOption < 1)
			pauseMenuOption += 1;
		if (endMenuOption < 1)
			endMenuOption += 1;
		glutPostRedisplay();
		break;
	}
}

int randomPosition() // generate a random number between 7 and 20
{
	srand((unsigned)time(0));
	int randomNumber;
	randomNumber = (rand() % 20);
	int ok = 0;
	while (ok == 0)
	{
		if (randomNumber >= 7 && randomNumber <= 20)
		{
			ok = 1;
		}
		else
			randomNumber = (rand() % 20);
	}
	return randomNumber;
}

double fallingSpeed() // increase the speed at which the squares fall
{
	double speed = 0.05;
	return speed + speed_multiplier;
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);

	if (startRound == true && pauseRound == false && endRound == false)
	{
		if (countdown > 1) {
			countdown -= 1.0 / 60.0;
		}
		else {
			countdown = 11;
			lives = 5;
			stage += 1;
			speed_multiplier += 0.01;
		}

		if (square1_y > -10)
			square1_y -= fallingSpeed();
		else
		{
			square1_y = randomPosition();
			if (lives >= 0)
				lives -= 1;
		}

		if (square2_y > -10)
			square2_y -= fallingSpeed();
		else
		{
			square2_y = randomPosition();
			if (lives >= 0)
				lives -= 1;
		}

		if (square3_y > -10)
			square3_y -= fallingSpeed();
		else
		{
			square3_y = randomPosition();
			if (lives >= 0)
				lives -= 1;
		}

		if (square4_y > -10)
			square4_y -= fallingSpeed();
		else
		{
			square4_y = randomPosition();
			if (lives >= 0)
				lives -= 1;
		}

		if (square5_y > -10)
			square5_y -= fallingSpeed();
		else
		{
			square5_y = randomPosition();
			if (lives >= 0)
				lives -= 1;
		}
	}

}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void bar()
{
	glBegin(GL_QUADS); // object made with help of quads
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-10, 8);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(10, 8);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(10, 7);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-10, 7);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void square_color()
{
	srand((unsigned)time(0));
	int randomNumber;
	randomNumber = (rand() % 5) + 1;
	switch (randomNumber)
	{
	case 1:
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);  //blue
		break;
	case 2:
		glColor3f(0.0f, 1.0f, 0.0f);  //green
		break;
	case 3:
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);  //yellow
		break;
	case 4:
		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);  //red
		break;
	case 5:
		glColor3f(1.0f, 0.5f, 0.0f);  //orange
		break;
	}
}

void falling_square(double x1, double x2, double y)
{
	square_color();
	if (y <= 7)
	{
		glBegin(GL_POLYGON);
		glVertex2f(x2, y);
		glVertex2f(x1, y);
		glVertex2f(x1, y - 1);
		glVertex2f(x2, y - 1);
		glEnd();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void detection()
{
	if (square1_y < -7 && square1_y > -7.3 && square1_x1 <= basket_position + 3 && square1_x2 >= basket_position - 3)
	{
		score += 10;
		square1_y = randomPosition();;
	}

	if (square2_y < -7 && square2_y > -7.3 && square2_x1 <= basket_position + 3 && square2_x2 >= basket_position - 3)
	{
		score += 10;
		square2_y = randomPosition();;
	}

	if (square3_y < -7 && square3_y > -7.3 && square3_x1 <= basket_position + 3 && square3_x2 >= basket_position - 3)
	{
		score += 10;
		square3_y = randomPosition();;
	}

	if (square4_y < -7 && square4_y > -7.3 && square4_x1 <= basket_position + 3 && square4_x2 >= basket_position - 3)
	{
		score += 10;
		square4_y = randomPosition();;
	}

	if (square5_y < -7 && square5_y > -7.3 && square5_x1 <= basket_position + 3 && square5_x2 >= basket_position - 3)
	{
		score += 10;
		square5_y = randomPosition();;
	}

}

void basket()
{
	glBegin(GL_QUADS); // object made with help of quads
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-3 + basket_position, -7);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(3 + basket_position, -7);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(3 + basket_position, -9);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-3 + basket_position, -9);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_LINES); //lines for the basket
	glVertex2f(-2.98 + basket_position, -7);
	glVertex2f(-2.98 + basket_position, -6);
	glEnd();

	glBegin(GL_LINES); //lines for the basket
	glVertex2f(3 + basket_position, -7);
	glVertex2f(3 + basket_position, -6);
	glEnd();
}

void startMenu()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	renderBitmapString(-2, 2, "START GAME");
	renderBitmapString(-1, 0, "RULES");
	renderBitmapString(-2, -2, "EXIT GAME!");


	switch (startMenuOption)
	{
	case 0:
		renderBitmapString(-1, 0, "RULES");
		renderBitmapString(-2, -2, "EXIT GAME!");
		glBegin(GL_QUADS);
		glVertex2f(-2.65, 3);
		glVertex2f(3, 3);
		glVertex2f(3, 1.5);
		glVertex2f(-2.65, 1.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-2, 2, "START GAME");
		glFlush();
		break;

	case 1:
		renderBitmapString(-2, 2, "START GAME");
		renderBitmapString(-2, -2, "EXIT GAME!");
		glBegin(GL_QUADS);
		glVertex2f(-2.65, 1);
		glVertex2f(3, 1);
		glVertex2f(3, -0.5);
		glVertex2f(-2.65, -0.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-1, 0, "RULES");
		glFlush();
		break;

	case 2:
		renderBitmapString(-2, 2, "START GAME");
		renderBitmapString(-1, 0, "RULES");
		glBegin(GL_QUADS);
		glVertex2f(-2.65, -1);
		glVertex2f(3, -1);
		glVertex2f(3, -2.5);
		glVertex2f(-2.65, -2.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-2, -2, "EXIT GAME!");
		glFlush();
		break;

	}
	glutPostRedisplay();
}

void pauseMenu()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	renderBitmapString(-2, 2, "RESUME GAME");
	renderBitmapString(-2, 0, "EXIT GAME");

	switch (pauseMenuOption)
	{
	case 0:
		renderBitmapString(-2, 0, "EXIT GAME");
		glBegin(GL_QUADS);
		glVertex2f(-2.65, 3);
		glVertex2f(3.5, 3);
		glVertex2f(3.5, 1.5);
		glVertex2f(-2.65, 1.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-2, 2, "RESUME GAME");
		glFlush();
		break;

	case 1:
		renderBitmapString(-2, 2, "RESUME GAME");
		glBegin(GL_QUADS);
		glVertex2f(-2.65, 1);
		glVertex2f(3.5, 1);
		glVertex2f(3.5, -0.5);
		glVertex2f(-2.65, -0.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-2, 0, "EXIT GAME");
		glFlush();
		break;

	}
	glutPostRedisplay();
}

void endMenu()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	renderBitmapString(-2, 6, "GAME OVER!");
	string final_stage = "YOU REACHED STAGE: " + to_string(stage);
	renderBitmapString(-4, 4, final_stage.c_str());
	string final_score = "OBTAINED SCORE: " + to_string(score);
	renderBitmapString(-3, 2, final_score.c_str());
	renderBitmapString(-2, 0, "TRY AGAIN!");
	renderBitmapString(-1, -2, "QUIT!");

	switch (endMenuOption)
	{
	case 0:
		renderBitmapString(-1, -2, "QUIT!");
		glBegin(GL_QUADS);
		glVertex2f(-2.5, 1);
		glVertex2f(2.5, 1);
		glVertex2f(2.5, -0.5);
		glVertex2f(-2.5, -0.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-2, 0, "TRY AGAIN!");
		glFlush();
		break;

	case 1:
		renderBitmapString(-2, 0, "TRY AGAIN!");
		glBegin(GL_QUADS);
		glVertex2f(-2.5, -1);
		glVertex2f(2.5, -1);
		glVertex2f(2.5, -2.5);
		glVertex2f(-2.5, -2.5);
		glEnd();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		renderBitmapString(-1, -2, "QUIT!");
		glFlush();
		break;

	}
	glutPostRedisplay();

}

void gameRules()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	renderBitmapString(-4, 8, "Press ENTER To Go Back");
	glBegin(GL_LINES); //lines for the basket
	glVertex2f(-4.1, 7.8);
	glVertex2f(3.7, 7.8);
	glEnd();
	renderBitmapString(-9.5, 5, "- Objective: Catch the falling squares before they hit the ground");
	renderBitmapString(-9.5, 4, "- Use the right and left arrow keys to control the basket");
	renderBitmapString(-9.5, 3, "- When the timer runs out, a new stage begins");
	renderBitmapString(-9.5, 2, "- Each stage lasts for 10 seconds");
	renderBitmapString(-9.5, 1, "- At each new stage: ");
	renderBitmapString(-5.5, 0, "- The speed at which the squares fall will increase");
	renderBitmapString(-5.5, -1, "- The number of lives will be reset to 5");
	renderBitmapString(-9.5, -2, "- The round ends when you fail to catch 5 squares at one stage");
	glutPostRedisplay();
}

void display()
{
	if (startRound == false && rulesMenu == false)
	{
		startMenu();
	}

	else if (startRound == false && rulesMenu == true)
	{
		gameRules();
	}

	else if (pauseRound == true)
	{
		pauseMenu();
	}

	else if (lives >= 0 && startRound == true && pauseRound == false && endRound == false)
	{
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();

		detection();
		renderBitmapString(-9, 9, getScore());
		renderBitmapString(-4.75, 9, remainng_time());
		renderBitmapString(2, 9, current_stage());
		renderBitmapString(6, 9, remaining_lives());

		bar();

		falling_square(square1_x1, square1_x2, square1_y);
		falling_square(square2_x1, square2_x2, square2_y);
		falling_square(square3_x1, square3_x2, square3_y);
		falling_square(square4_x1, square4_x2, square4_y);
		falling_square(square5_x1, square5_x2, square5_y);

		basket();
	}

	else
	{
		endMenu();
		endRound = true;
	}

	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(200, 100);
	glutInitWindowSize(700, 700);

	glutCreateWindow("FALLING SQUARES");

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	init();
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(regularKey);

	glutMainLoop();
}