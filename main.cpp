#include <GL/glut.h>
#include <stdio.h>
#include <string>

int flag =0;

const int mazeSize = 21;

const int artifactSize = 25;

float quadx = 0.0f;
float quady = 0.0f;

int playerRow = 3;
int playerCol = 3;

int item1Row = 5;
int item1Col = 3;

int item2Row = 9;
int item2Col = 17;

int item3Row = 16;
int item3Col = 5;

int item4Row = 9;
int item4Col = 15;

int finishRow = 17;
int finishCol = 18;

int counter = 0;

const float cellSize = 1.0f;
const float artSize = 0.053f;

int timerSeconds = 45;

int timerOut = 0;
int gameLost = 0;
int gameWon = 0;



int currentPage = 1;

int maze[mazeSize][mazeSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};



int artifact[artifactSize][artifactSize] = {
    {},{},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,1,0,0,1,3,2,1,0,0,0,0},
    {0,0,0,0,1,3,3,3,1,1,3,3,3,1,0,0,0,0},
    {0,0,0,0,0,1,3,2,2,2,2,3,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,4,5,3,3,4,5,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,6,2,2,6,4,1,0,0,0,0,0},
    {0,0,1,1,0,1,3,3,2,2,3,3,1,0,1,1,0,0},
    {0,0,1,2,1,1,1,7,3,3,7,1,1,1,2,1,0,0},
    {0,0,1,2,3,3,3,7,1,1,7,3,3,2,3,1,0,0},
    {0,0,0,1,1,2,3,2,7,7,2,3,2,1,1,0,0,0},
    {0,0,0,0,0,1,3,2,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,1,1,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,3,3,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,3,1,1,3,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},

};
int artifact2[artifactSize][artifactSize] = {
    {},{},
    {},{},{},
    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,1,0,0,1,3,2,1,0,0,0,0},
    {0,0,0,0,1,3,3,3,1,1,3,3,3,1,0,0,0,0},
    {0,0,0,0,0,1,3,2,2,2,2,3,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,4,5,3,3,4,5,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,6,2,2,6,4,1,0,0,0,0,0},
    {0,0,1,1,0,1,3,3,2,2,3,3,1,0,1,1,0,0},
    {0,0,1,2,1,1,1,7,3,3,7,1,1,1,2,1,0,0},
    {0,0,1,2,3,3,3,7,1,1,7,3,3,2,3,1,0,0},
    {0,0,0,1,1,2,3,2,7,7,2,3,2,1,1,0,0,0},
    {0,0,0,0,0,1,3,2,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,1,1,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,3,3,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,3,1,1,3,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},

};
int artifact3[artifactSize][artifactSize] = {
    {},{},{},{},{},

    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,1,0,0,1,3,2,1,0,0,0,0},
    {0,0,0,0,1,3,3,3,1,1,3,3,3,1,0,0,0,0},
    {0,0,0,0,0,1,3,2,2,2,2,3,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,4,5,3,3,4,5,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,6,2,2,6,4,1,0,0,0,0,0},
    {0,0,1,1,0,1,3,3,2,2,3,3,1,0,1,1,0,0},
    {0,0,1,2,1,1,1,7,3,3,7,1,1,1,2,1,0,0},
    {0,0,1,2,3,3,3,7,1,1,7,3,3,2,3,1,0,0},
    {0,0,0,1,1,2,3,2,7,7,2,3,2,1,1,0,0,0},
    {0,0,0,0,0,1,3,2,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,1,1,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,3,3,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,3,1,1,3,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},

};

int artifact4[artifactSize][artifactSize] = {
    {},{},{},{},{},
    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,1,2,3,1,0,0,1,3,2,1,0,0,0,0},
    {0,0,0,0,1,3,3,3,1,1,3,3,3,1,0,0,0,0},
    {0,0,0,0,0,1,3,2,2,2,2,3,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,4,5,3,3,4,5,1,0,0,0,0,0},
    {0,0,0,0,0,1,5,6,2,2,6,4,1,0,0,0,0,0},
    {0,0,1,1,0,1,3,3,2,2,3,3,1,0,1,1,0,0},
    {0,0,1,2,1,1,1,7,3,3,7,1,1,1,2,1,0,0},
    {0,0,1,2,3,3,3,7,1,1,7,3,3,2,3,1,0,0},
    {0,0,0,1,1,2,3,2,7,7,2,3,2,1,1,0,0,0},
    {0,0,0,0,0,1,3,2,3,3,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,1,2,3,1,1,3,2,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,3,3,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,3,1,1,3,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},

};




void timer(int value) {
    if (timerSeconds > 0) {
        timerSeconds--;
        glutTimerFunc(1000, timer, 0);
        glutPostRedisplay();
    }

    if(gameWon == 1) {
        timerOut = false;
        gameLost = 0;
    }
    else if (timerSeconds == 0) {
        timerOut = true;
        gameLost = 1;
        currentPage = 4;
        finishRow = 0;
        finishCol = 0;
    }
}


void displayGame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();



    for (int row = 0; row < mazeSize; row++)
    {
        for (int col = 0; col < mazeSize; col++)
        {
            float x = col * cellSize;
            float y = row * cellSize;
            if (maze[row][col] == 1)
                glColor3f(0.86f, 0.75f, 0.54f);
            else
                glColor3f(0.42f, 0.39f, 0.37f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x, y + cellSize);
            glVertex2f(x + cellSize, y + cellSize);
            glVertex2f(x + cellSize, y);
            glEnd();
        }
    }



    float playerX = playerCol * cellSize;
    float playerY = playerRow * cellSize;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerX, playerY);
    glVertex2f(playerX, playerY + cellSize);
    glVertex2f(playerX + cellSize, playerY + cellSize);
    glVertex2f(playerX + cellSize, playerY);
    glEnd();


    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(0.8f, 0.9f);
    std::string timerText = "Timer: " + std::to_string(timerSeconds) + "s";
    for (char c : timerText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }




    if (item1Row != -1 && item1Col != -1)
    {
        for (int row = 0; row < artifactSize; row++) {
        for (int col = 0; col < artifactSize; col++) {
            quadx = 3+col * artSize;
            quady = 4.8+row * artSize;



             if (artifact[row][col] == 1) {
                glColor3f(0.5f, 0.35f, 0.05f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact[row][col] == 2) {
                glColor3f(1.0f, 0.968f, 0.831f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact[row][col] == 3) {
                glColor3f(0.7529f, 0.498f, 0.0f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact[row][col] == 4) {
                glColor3f(0.0f, 1.0f, 0.8667f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact[row][col] == 5) {
                glColor3f(0.0f, 1.0f, 0.67f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
             else if (artifact[row][col] == 6) {
                glColor3f(0.0784f, 0.7647f, 0.5568f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact[row][col] == 7) {
                glColor3f(0.792f, 0.5843f, 0.3607f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();

            }

        }
    }
    }

    if (item2Row != -1 && item2Col != -1)
    {
        for (int row = 0; row < artifactSize; row++) {
        for (int col = 0; col < artifactSize; col++) {
            quadx = 17+col * artSize;
            quady = 8.8+row * artSize;

        if (artifact2[row][col] == 1) {
                glColor3f(0.6f, 0.0f, 0.0f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact2[row][col] == 2) {
                glColor3f(0.933f, 0.4117f, 0.4117f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact2[row][col] == 3) {
                glColor3f(0.8627f, 0.0f, 0.0f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact2[row][col] == 4) {
                glColor3f(0.0f, 1.0f, 0.8667f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact2[row][col] == 5) {
                glColor3f(0.0f, 1.0f, 0.67f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
             else if (artifact2[row][col] == 6) {
                glColor3f(0.0784f, 0.7647f, 0.5568f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact2[row][col] == 7) {
                glColor3f(0.9254f, 0.498f, 0.749f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }

        }
    }
    }
    if (item3Row != -1 && item3Col != -1)
    {
        for (int row = 0; row < artifactSize; row++) {
        for (int col = 0; col < artifactSize; col++) {
            quadx = 5+col * artSize;
            quady = 15.8+row * artSize;

            if (artifact3[row][col] == 1) {
                glColor3f(0.0470f, 0.0745f, 0.3098f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact3[row][col] == 2) {
                glColor3f(0.098f, 0.6549f, 0.8078f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact3[row][col] == 3) {
                glColor3f(0.07843f, 0.40784f, 0.58f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact3[row][col] == 4) {
                glColor3f(1.0f, 0.9686f, 0.83137f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact3[row][col] == 5) {
                glColor3f(1.0f, 0.8509f, 0.3529f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
             else if (artifact3[row][col] == 6) {
                glColor3f(0.7529f, 0.498f, 0.0f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact3[row][col] == 7) {
                glColor3f(0.4745f, 0.8784f, 0.93333f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }

        }
    }
    }

    if (item4Row != -1 && item4Col != -1)
    {
        for (int row = 0; row < artifactSize; row++) {
        for (int col = 0; col < artifactSize; col++) {
            quadx = 15+col * artSize;
            quady = 8.8+row * artSize;

            if (artifact4[row][col] == 1) {
                glColor3f(0.1960f, 0.4f, 0.1098f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact4[row][col] == 2) {
                glColor3f(0.039f, 0.9372f, 0.4549f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact4[row][col] == 3) {
                glColor3f(1.0f, 0.9686f, 0.83137f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact4[row][col] == 4) {
                glColor3f(1.0f, 0.9686f, 0.83137f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact4[row][col] == 5) {
                glColor3f(1.0f, 0.8509f, 0.3529f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
             else if (artifact4[row][col] == 6) {
                glColor3f(0.7529f, 0.498f, 0.0f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }
            else if (artifact4[row][col] == 7) {
                glColor3f(0.7019f, 1.0f, 0.6823f); // Path color (white)
                glBegin(GL_QUADS);
                glVertex2f(quadx, quady);
                glVertex2f(quadx, quady + artSize);
                glVertex2f(quadx + artSize, quady + artSize);
                glVertex2f(quadx + artSize, quady);
                glEnd();
            }

        }
    }
    }

    if(playerX==finishCol && playerY == finishRow && counter >= 3) {
        gameWon = 1;
        currentPage = 5;
        printf("Game Won status: %d", gameWon);
        printf("\n");
        printf("GAME OVER ");
    }

    glutSwapBuffers();
    glFlush();
}
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, mazeSize * cellSize, mazeSize * cellSize, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}






void keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
        case GLUT_KEY_UP:
            if (playerRow > 0 && maze[playerRow - 1][playerCol] == 0)
                playerRow--;
            break;
        case 's':
        case 'S':
            if (playerRow < mazeSize - 1 && maze[playerRow + 1][playerCol] == 0)
                playerRow++;
            break;
        case 'a':
        case 'A':
            if (playerCol > 0 && maze[playerRow][playerCol - 1] == 0)
                playerCol--;
            break;
        case 'd':
        case 'D':
            if (playerCol < mazeSize - 1 && maze[playerRow][playerCol + 1] == 0)
                playerCol++;
            break;
    }

    if (playerRow == item1Row && playerCol == item1Col)
    {
        item1Row = -1;
        item1Col = -1;
        counter++;
    }
    if (playerRow == item2Row && playerCol == item2Col)
    {
        item2Row = -1;
        item2Col = -1;
        counter++;
    }
    if (playerRow == item3Row && playerCol == item3Col)
    {
        item3Row = -1;
        item3Col = -1;
        counter++;
    }

     if (playerRow == item4Row && playerCol == item4Col)
    {
        item4Row = -1;
        item4Col = -1;
        counter++;
    }

    glutPostRedisplay();
}

int game() {

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(750, 750);
    glutCreateWindow("Desert Pyramid Maze");
    glClearColor(0.86f, 0.75f, 0.54f, 1.0f);
    glutDisplayFunc(displayGame);
    glutTimerFunc(1000, timer, 0);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardFunc);
    glutMainLoop();
    return 0;
}

void displayFirstPage() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the heading in green color
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.8f);
    std::string heading = "COMPUTER GRAPHICS LAB MINI PROJECT";
    for (char c : heading) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the first subtext in red color
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.6f);
    std::string subtext1 = "Prateesh Sulikeri 2KL20CS057";
    for (char c : subtext1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw the second subtext in red color
    glRasterPos2f(-0.8f, 0.5f);
    std::string subtext2 = "Pratham Kadapatti 2KL20CS058";
    for (char c : subtext2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw "PRESS ENTER TO CONTINUE" in white color
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.8f, -0.8f);
    std::string pressEnter = "PRESS ENTER TO CONTINUE";
    for (char c : pressEnter) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glutSwapBuffers();
}

void displaySecondPage() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the heading in green color
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.8f);
    std::string heading = "Instructions";
    for (char c : heading) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the subtexts in red color
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.6f);
    std::string subtext1 = "Use WASD for movement";
    for (char c : subtext1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2f(-0.8f, 0.5f);
    std::string subtext2 = "You need to collect a minimum of 3 artifacts to win";
    for (char c : subtext2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2f(-0.8f, 0.4f);
    std::string subtext3 = "You only have 45 seconds to complete";
    for (char c : subtext3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glRasterPos2f(-0.8f, 0.3f);
    std::string subtext4 = "The exit is at the bottom right corner of the maze";
    for (char c : subtext4) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    // Draw "PRESS ENTER TO CONTINUE" in white color
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.8f, -0.8f);
    std::string pressEnter = "PRESS ENTER TO CONTINUE";
    for (char c : pressEnter) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }


    glutSwapBuffers();
}

void displayGameSeq() {
}

void displayGameOverPage() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the heading in green color
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.8f);
    std::string heading = "GAME OVER";
    for (char c : heading) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the subtext in red color
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.6f);
    std::string subtext = "You Lost";
    for (char c : subtext) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glutSwapBuffers();
}

void displayGameWonPage() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the heading in green color
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2f(-0.8f, 0.8f);
    std::string heading = "GAME OVER";
    for (char c : heading) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Draw the subtext in blue color
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(-0.8f, 0.6f);
    std::string subtext = "YOU WON";
    for (char c : subtext) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glutSwapBuffers();
}


void display() {
    switch (currentPage) {
        case 1:
            displayFirstPage();
            break;
        case 2:
            displaySecondPage();
            break;
        case 3:
            displayGameSeq();
            break;
        case 4:
            displayGameOverPage();
            break;
        case 5:
            displayGameWonPage();
            break;
        case 6:
            game();
            break;
        default:
            break;
    }
}




void keyboard(unsigned char key, int x, int y) {
    if (key == 13) { // 13 is the ASCII code for the Enter key
        if (currentPage == 1) {
            currentPage = 2;
            glutPostRedisplay();
        } else if (currentPage == 2) {
            currentPage = 6;
            glutPostRedisplay();
        }
    }
}



int main(int argc, char **argv)
{
   glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Pages");

    // Register callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}
