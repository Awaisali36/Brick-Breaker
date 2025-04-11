#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
int level=1;
class Paddle;
class Ball;
class Food;

class Brick {
private:
    int x;
    int y;
    int width;
    int height;
    int collisionCount; 
    bool visible;
    int brickType;
    float color[3];

public:
    Brick() {}

    Brick(int x, int y, int width, int height,int brickType, float color[]) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->brickType = brickType;
        this->collisionCount = 0; // Initialize collision count to 0
        this->visible = true;
        for (int i = 0; i < 3; ++i) {
            this->color[i] = color[i];
        }
    }

    void Draw() {
        if (visible) {
            DrawRectangle(x, y, width, height, color);
        }
    }

    void Hide() {
        visible = false;
    }

    void Show() {
        visible = true;
    }

    bool IsVisible() const {
        return visible;
    }

    int GetX() const {
        return x;
    }

    int GetY() const {
        return y;
    }

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }

    bool CheckCollisionWithBall(float ballX, float ballY, float ballRadius) const {
        float closestX;
        if (ballX < x) {
            closestX = x;
        } else if (ballX > x + width) {
            closestX = x + width;
        } else {
            closestX = ballX;
        }
        float closestY;
        if (ballY < y) {
            closestY = y;
        } else if (ballY > y + height) {
            closestY = y + height;
        } else {
            closestY = ballY;
        }

       
        float distanceX = ballX - closestX;
        float distanceY = ballY - closestY;
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	return distanceSquared < (ballRadius * ballRadius);
    }

void IncrementCollisionCount() {
        
        if (brickType == 0 || brickType == 3) { 
            collisionCount++;         } else { 
            collisionCount += 2; 
        }
    }
    int GetCollisionCount() const {
        return collisionCount;
    }
    
     int GetBrickType() const {
        return brickType;
    }
    void  HandleBrickCollision(Brick& brick, Food foodArray[], int& foodCount);
};
class Paddle {
private:
    int x; // x-coordinate of the paddle
    int y; // y-coordinate of the paddle
    int width; // width of the paddle
    int height; // height of the paddle
    float color[3]; // color of the paddle
public:
    Paddle(int x, int y, int width, int height, float color[]) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        for (int i = 0; i < 3; ++i) {
            this->color[i] = color[i];
        }
    }

    void Draw() {
        DrawRectangle(x, y, width, height, color);
    }

    void MoveLeft() {
    	if(x>0)
        x -= 10; // adjust the value as needed
    }

    void MoveRight() {
    	if(x<550)
        x += 10; // adjust the value as needed
    }

    void SetX(int newX) {
        x = newX;
    }

    void SetY(int newY) {
        y = newY;
    }

    void SetWidth(int newWidth) {
        width = newWidth;
    }

    void SetHeight(int newHeight) {
        height = newHeight;
    }

    void SetColor(float newColor[]) {
        for (int i = 0; i < 3; ++i) {
            color[i] = newColor[i];
        }
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }

    int GetWidth() {
        return width;
    }

    int GetHeight() {
        return height;
    }
 const float* GetColor() {
        return color;
    }
};
Paddle bottomPaddle(500, 20, 100, 20, colors[BLUE]);
class Ball {
private:
    float x; // x-coordinate of the ball
    float y; // y-coordinate of the ball
    float radius; // radius of the ball
    float dx; // velocity of the ball in x-direction
    float dy; // velocity of the ball in y-direction
    float color[3]; // color of the ball

public:
		Ball(){}
  Ball(float dx, float dy) : dx(dx), dy(dy) {}
    Ball(float x, float y, float radius, float dx, float dy, float color[]) {
        this->x = x;
        this->y = y;
        this->radius = radius;
        this->dx = dx;
        this->dy = dy;
        for (int i = 0; i < 3; ++i) {
            this->color[i] = color[i];
        }
    }

    void Draw() {
        DrawCircle(x, y, radius, color);
    }

    void UpdatePosition() {
        x += dx;
        y += dy;

        // Check for collision with walls
        if (x - radius < 0 || x + radius >=650) {
            dx = -dx;
        }
        if (y + radius >650) {
            dy = -dy;
        }
    }
    
    bool CheckCollisionWithBrick(const Brick& brick) const {
    
    float closestX;
    if (x < brick.GetX()) {
        closestX = brick.GetX();
    } else if (x > brick.GetX() + brick.GetWidth()) {
        closestX = brick.GetX() + brick.GetWidth();
    } else {
        closestX = x;
    }

    
    float closestY;
    if (y < brick.GetY()) {
        closestY = brick.GetY();
    } else if (y > brick.GetY() + brick.GetHeight()) {
        closestY = brick.GetY() + brick.GetHeight();
    } else {
        closestY = y;
    }
    float distanceX = x - closestX;
    float distanceY = y - closestY;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    
    return distanceSquared <= (radius * radius);
}
    void ReverseYDirection() {
        dy = -dy;
    }

    void ReverseXDirection() {
        dx = -dx;
    }

   float GetX() {
        return x;
    }

    float GetY() {
        return y;
    }

    float GetRadius() {
        return radius;
    }
    void SetDX(float newDX) {
        dx = newDX;
    }

    void SetDY(float newDY) {
        dy = newDY;
    }
    void SetX(float newX) {
        x = newX;
    }

    void SetY(float newY) {
        y = newY;
    }

    float GetDX() const {
        return dx;
    }

    float GetDY() const {
        return dy;
    }
    const float* GetColor() const {
        return color;
    }
};
Ball ball(500, 300, 10, 2, -2, colors[RED]);
class Food {
private:
    float x; // x-coordinate of the food
    float y; // y-coordinate of the food
    float size; // size of the food
    float dy; // velocity of the food in y-direction
    int type; // type of the food (0 = power-up, 1 = power-down)
    float color[3]; // color of the food

public:
	Food(){}
    Food(float x, float y, float size, float dy, int type, float color[]) {
        this->x = x;
        this->y = y;
        this->size = size;
        this->dy = dy;
        this->type = type;
        for (int i = 0; i < 3; ++i) {
            this->color[i] = color[i];
        }
    }

    void Draw() {
        if (type == 0) {
            // Draw power-up
            if (size == 1) {
                DrawTriangle(x, y, x - 10, y - 15, x + 10, y - 15, color);
            } else if (size == 2) {
                DrawRectangle(x - 10, y - 10, 20, 20, color);
            } else if (size == 3) {
                DrawCircle(x, y, 10, color);
            }
        } else {
            // Draw power-down
            if (size == 1) {
                DrawRectangle(x - 10, y - 10, 20, 20, color);
            } else if (size == 2) {
                DrawRectangle(x - 15, y - 10, 30, 20, color);
            }
        }
    }

    void UpdatePosition() {
        // Move the food downwards
        y -= dy;
    }

    float GetX() const {
        return x;
    }

    float GetY() const {
        return y;
    }

    float GetSize() const {
        return size;
    }

    int GetType() const {
        return type;
    }
};
class Utility {
public:
    static void shuffleArray(int arr[], int size);
    static const int BRICK_ROWS = 4;
    static const int BRICK_COLS = 10;
    static const int BRICK_WIDTH = 60;
    static const int BRICK_HEIGHT = 20;
    static const int BRICK_GAP = 5;
};

class BrickArray {
private:
   
    Brick bricks[Utility::BRICK_ROWS * Utility::BRICK_COLS];

public:
    Brick& operator[](int index) {
        return bricks[index];
    }

    const Brick& operator[](int index) const {
        return bricks[index];
    }

    static BrickArray CreateBrickArray();
};


void Utility:: shuffleArray(int arr[], int size) {
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1); 
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
Paddle upperPaddle(500, 600, 100, 20, colors[GREEN]);

BrickArray BrickArray::CreateBrickArray()  {
    BrickArray brickArray;
    int brickTypes[] = {0, 1, 2, 3, 4}; 
    std::srand(std::time(nullptr));
    Utility s1;

    Utility::shuffleArray(brickTypes, 5); // Change the size to 5

    int startX = (650 - (s1.BRICK_COLS * (s1.BRICK_WIDTH + s1.BRICK_GAP))) / 2;
    int startY = 550 - (s1.BRICK_ROWS * (s1.BRICK_HEIGHT + s1.BRICK_GAP)) - 50;
    int index = 0; 
    bool positionsTaken[s1.BRICK_ROWS * s1.BRICK_COLS] = {false};

    for (int row = 0; row < s1.BRICK_ROWS; ++row) {
        for (int col = 0; col <s1. BRICK_COLS; ++col) {
            
            int position;
            do {
                position = rand() % (s1.BRICK_ROWS * s1.BRICK_COLS);
            } while (positionsTaken[position]);
            
            // Mark the position as used
            positionsTaken[position] = true;

            
            int x = startX + (position % s1.BRICK_COLS) * (s1.BRICK_WIDTH + s1.BRICK_GAP);
            int y = startY + (position / s1.BRICK_COLS) * (s1.BRICK_HEIGHT + s1.BRICK_GAP);

            int brickType = brickTypes[index % 5]; // Change the modulo value to 5
            index++;

            float color[3]; // Brick color

            switch (brickType) {
                case 0: // Green brick
                    color[0] = 0.0f;
                    color[1] = 1.0f;
                    color[2] = 0.0f;
                    break;
                case 1: // Pink brick
                    color[0] = 1.0f;
                    color[1] = 0.0f;
                    color[2] = 1.0f;
                    break;
                case 2: // Blue brick
                    color[0] = 0.0f;
                    color[1] = 0.0f;
                    color[2] = 1.0f;
                    break;
                case 3: // Red brick
                    color[0] = 1.0f;
                    color[1] = 0.0f;
                    color[2] = 0.0f;
                    break;
                case 4: // Yellow brick
                    color[0] = 1.0f;
                    color[1] = 1.0f;
                    color[2] = 0.0f;
                    break;
            }

            // Create brick and add it to the brick array
            brickArray[position] = Brick(x, y, s1.BRICK_WIDTH, s1.BRICK_HEIGHT,brickType, color);
        }
    }

    return brickArray;
}
class Game {
public:
	Game(){}
    void UpdatePosition(BrickArray& brickArray, Food foodArray[], int& foodCount, Paddle& bottomPaddle, Paddle& upperPaddle, Ball& ball);
    
static const int MAX_FOOD_COUNT = 40; 
    static Food foodArray[MAX_FOOD_COUNT]; 
    static int foodCount; 
   static int score ; 
   static int lives;
Brick bricks[Utility::BRICK_ROWS * Utility::BRICK_COLS]; 
};



void Brick:: HandleBrickCollision(Brick& brick, Food foodArray[], int& foodCount) {
    if (brick.IsVisible() && brick.CheckCollisionWithBall(ball.GetX(), ball.GetY(), ball.GetRadius())) {
        int brickType = brick.GetBrickType(); 
        cout << "Brick type is " << brickType << endl;
	Game g1;
        switch (brickType) {
            case 0: // Green brick
                brick.Hide(); 
                 ball.ReverseYDirection();// Hide the brick
                g1.score++; // Increment score
                
                if (foodCount < g1.MAX_FOOD_COUNT) {
                    foodArray[g1.foodCount++] = Food(brick.GetX()+30, brick.GetY()+30, 1, 2, 0, colors[GREEN]);
                }
                break;
            case 1: // Pink brick
            if (brick.GetCollisionCount() >= 2) {
                    brick.Hide();
                    ball.ReverseYDirection(); // Hide the brick
                    g1.score++; // Increment score
                    
                    if (foodCount < g1.MAX_FOOD_COUNT) {
                        g1.foodArray[g1.foodCount++] = Food(brick.GetX()+30, brick.GetY()+30, 1, 2, 1, colors[DEEP_PINK]);
                    }
                } else {
                    brick.IncrementCollisionCount(); // Increment collision count
                    ball.ReverseYDirection(); // Reflect the ball
                }
                break;
            case 2: // BLUE brick
                if (brick.GetCollisionCount() >= 3) {
                    brick.Hide(); 
                    ball.ReverseYDirection();// Hide the brick
                    g1.score++; // Increment score
                    
          	  if (foodCount < g1.MAX_FOOD_COUNT) {
                	g1.foodArray[foodCount++] = Food(brick.GetX()+30, brick.GetY()+30, 1, 2, 1, colors[BLUE]);
           	  }
                } else {
                    brick.IncrementCollisionCount(); // Increment collision count
                    ball.ReverseYDirection(); // Reflect the ball
                }
                break;
            case 3: // RED brick
            	 if (brick.GetCollisionCount() >= 3) {
                    brick.Hide();
                    ball.ReverseYDirection(); // Hide the brick
                    g1.score++; // Increment score
                    // Create blue or red power-up (circle)
                    if (foodCount < g1.MAX_FOOD_COUNT) {
                        foodArray[foodCount++] = Food(brick.GetX()+30, brick.GetY()+30, 1, 2, 1, colors[RED]);
                    }
                } else {
                    brick.IncrementCollisionCount(); // Increment collision count
                    ball.ReverseYDirection(); // Reflect the ball
                }
                break;
            case 4: 
            	 if (brick.GetCollisionCount() >= 2) {
                    brick.Hide();
                    ball.ReverseYDirection(); // Hide the brick
                    g1.score++; // Increment score
                    // Create blue or red power-up (circle)
                    if (foodCount < g1.MAX_FOOD_COUNT) {
                        
                        foodArray[foodCount++] = Food(brick.GetX()+30, brick.GetY()+30, 3, 2, 0, colors[YELLOW]);
                    }
                } else {
                    brick.IncrementCollisionCount(); // Increment collision count
                    ball.ReverseYDirection(); // Reflect the ball
                }
                break;
          }
    }
}

void Game::UpdatePosition(BrickArray& brickArray, Food foodArray[], int& foodCount, Paddle& bottomPaddle, Paddle& upperPaddle, Ball& ball ) {

    ball.UpdatePosition();
    
    
    if (ball.GetY() - ball.GetRadius() - 20 <= bottomPaddle.GetY() &&
        ball.GetX() >= bottomPaddle.GetX() && ball.GetX() <= bottomPaddle.GetX() + bottomPaddle.GetWidth()) {
        ball.ReverseYDirection();
    }
    
    
    if (ball.GetY() + ball.GetRadius() > upperPaddle.GetY() &&
        ball.GetX() >= upperPaddle.GetX() && ball.GetX() <= upperPaddle.GetX() + upperPaddle.GetWidth()) {
        ball.ReverseYDirection();
    }
    
    Brick b1;
    Utility s1;
    Game g1;
    
    
    for (int i = 0; i < s1.BRICK_ROWS * s1.BRICK_COLS; ++i) {
        Brick& brick = brickArray[i];
        
        if (brick.IsVisible() && ball.CheckCollisionWithBrick(brick)) {
            b1.HandleBrickCollision(brick, g1.foodArray, g1.foodCount);
        }
    }
    
    int MAX_BALLS = 40;
    Ball balls[MAX_BALLS];
    int numBalls = 1; // Initially, there's only one ball
    
    // Check for collision with power-ups and power-downs
    for (int i = 0; i < g1.foodCount; ++i) {
        Food& food = g1.foodArray[i];
        if (food.GetType() == 0) { // Power-up
            if (food.GetX() >= bottomPaddle.GetX() && food.GetX() <= bottomPaddle.GetX() + bottomPaddle.GetWidth() &&
                food.GetY() <= bottomPaddle.GetY() + bottomPaddle.GetHeight()) {
                // Apply power-up effect
                switch (static_cast<int>(food.GetSize())) {
                    case 1: // Green power-up (increase paddle size)
                        bottomPaddle.SetWidth(bottomPaddle.GetWidth() * 2);
                        break;
                    case 2: 
                        ball.SetDX(ball.GetDX() / 2);
                        ball.SetDY(ball.GetDY() / 2); // Decrease ball speed by half
                        break;
                    case 3: 
                    {
                        
                        Ball newBall1(ball.GetX(), ball.GetY(), ball.GetRadius(), ball.GetDX(), ball.GetDY(), colors[RED]);
                        Ball newBall2(ball.GetX(), ball.GetY(), ball.GetRadius(), ball.GetDX(), ball.GetDY(), colors[RED]);

                        // Add the new balls to the array
                        balls[numBalls++] = newBall1;
                        balls[numBalls++] = newBall2;

                        
                        if (numBalls > MAX_BALLS) {
                            numBalls = MAX_BALLS;
                        }
                    }
                    break;
                }
                // Remove food from array
                food = g1.foodArray[g1.foodCount - 1];
                g1.foodCount--;
            }
        } else { // Power-down
            if (food.GetX() >= bottomPaddle.GetX() && food.GetX() <= bottomPaddle.GetX() + bottomPaddle.GetWidth() &&
                food.GetY() <= bottomPaddle.GetY() + bottomPaddle.GetHeight()) {
                // Apply power-down effect
                switch (static_cast<int>(food.GetSize())) {
                    case 1: // Pink power-down (reduce paddle size)
                        bottomPaddle.SetWidth(bottomPaddle.GetWidth() / 2);
                        break;
                    case 2: // Rectangle power-down (speed up ball)
                        ball.SetDX(ball.GetDX() * 2);
                        ball.SetDY(ball.GetDY() * 2); // Double ball speed
                        break;
                }
                // Remove food from array
                food = g1.foodArray[g1.foodCount - 1];
                g1.foodCount--;
            }
        }
    }
    
    for (int i = 0; i < numBalls; ++i) {
        balls[i].UpdatePosition();
        balls[i].Draw();
    }
}

//Brick brick(300,300,100,20,colors[YELLOW]);
 BrickArray brickArray = BrickArray::CreateBrickArray();
void GameDisplay()/**/{
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); 
	//Update the colors
	 bottomPaddle.Draw();
         upperPaddle.Draw();
         ball.Draw();
	Utility k1;
	Game g1;
    // Draw the array of bricks
    for (int i = 0; i < k1.BRICK_ROWS * k1.BRICK_COLS; ++i) {
        brickArray[i].Draw();
    }
    
	DrawString(50, 600, "Score=" + to_string(g1.score), colors[MISTY_ROSE]);
	
Game g2;
g2.UpdatePosition(brickArray, g2.foodArray, g2.foodCount, bottomPaddle, upperPaddle, ball);


 for (int i = 0; i < g1.foodCount; ++i) {
        g2.foodArray[i].Draw();
    }
    
      for (int i = 0; i < g2.foodCount; ++i) {
        g2.foodArray[i].UpdatePosition();
    }

	 DrawString(50, 570, "Lives: " + to_string(g2.lives), colors[MISTY_ROSE]);
     if (ball.GetY() - ball.GetRadius() < 0) {
        // Decrement the number of lives
        g2.lives--;

        // Reset the ball to its initial position
        ball.SetX(500);
        ball.SetY(300);
        ball.SetDX(2);
        ball.SetDY(-2);

        // If no lives remaining, end the game
        if (g2.lives == 0) {

         cout<<"GAME OVER"<<endl;
            
            exit(0); // Exit the game
        }
    }
	
	glutSwapBuffers(); // do not modify this line..

}
void NonPrintableKeys(int key, int x, int y) {
	if (key== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		 upperPaddle.MoveLeft();

	} else if (key== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	
		upperPaddle.MoveRight();
	} else if (key== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}
int Game::foodCount = 0;
Food Game::foodArray[MAX_FOOD_COUNT];
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}

void Timer(int m) {

	
	ball.UpdatePosition();


    if (ball.GetY() - ball.GetRadius()-20 <= bottomPaddle.GetY() &&
        ball.GetX() >= bottomPaddle.GetX() && ball.GetX() <= bottomPaddle.GetX() + bottomPaddle.GetWidth()) {
        ball.ReverseYDirection();
    }
    if (ball.GetY() + ball.GetRadius() > upperPaddle.GetY() &&
        ball.GetX() >= upperPaddle.GetX() && ball.GetX() <= upperPaddle.GetX() + upperPaddle.GetWidth()) {
        ball.ReverseYDirection();
    }

    glutPostRedisplay();
   // UpdateAndDrawFood();
   // UpdateGameState(ball, bottomPaddle, upperPaddle);

	glutTimerFunc(1000.0 / FPS, Timer, 0);

}

void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
int Game::score=0;
void MouseMoved(int x, int y) {
	if(x<570)
	 bottomPaddle.SetX(x);
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
int Game::lives = 2;
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}

int main(int argc, char*argv[]) {

	int width = 650, height = 650; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); 
	
	// tell library which function to call for printable ASCII characters
	glutTimerFunc(1000.0, Timer, 0);
	//Game g1;
	//g1.UpdatePosition(brickArray, foodArray, foodCount, bottomPaddle, upperPaddle, ball);
	glutMouseFunc(MouseClicked);
	
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
