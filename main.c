#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 500

#define PADDLE_HEIGHT 75
#define PADDLE_WIDTH  15

#define BALL_SPEED 5

//Function declerations
bool isCursorOnScreen(int pos);
int calculateGradient(Rectangle ball, Rectangle paddle);
void resetBall(Rectangle* ball);

typedef enum {
  LEFT,
  RIGHT
} Direction;

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PONG");
  SetTargetFPS(60);

  Rectangle border = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  Rectangle p1 = {SCREEN_WIDTH - 30, 200, PADDLE_WIDTH, PADDLE_HEIGHT};
  Rectangle p2 = {15, 200, PADDLE_WIDTH, PADDLE_HEIGHT};
  Rectangle ball = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 15, 15};

  Rectangle top = {0, 0, SCREEN_WIDTH, 5};
  Rectangle bottom = {0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5};
  Rectangle p1Gate = {SCREEN_WIDTH - 5, 0, 5, SCREEN_HEIGHT};
  Rectangle p2Gate = {0, 0, 5, SCREEN_HEIGHT};


  HideCursor();

  int gradient = 0;
  Direction dir = LEFT;
  
  int scores[] = {0, 0}; //player 1 score [0], player 2 score[1]
  char p1Score[3];
  char p2Score[3];
  
  while(!WindowShouldClose()) {
    int cursorY = GetMouseY();
    if (isCursorOnScreen(cursorY)){
      p1.y = cursorY - (PADDLE_HEIGHT / 2); 
    }
    switch (dir) {
    case LEFT:
      ball.x = ball.x + BALL_SPEED;
      break;
    case RIGHT:
      ball.x = ball.x - BALL_SPEED;
      break;
    }

    if (CheckCollisionRecs(ball, top) || CheckCollisionRecs(ball, bottom)) {
      gradient = gradient * -1;
    }

    ball.y += gradient;

    p2.y = ball.y;

    if (CheckCollisionRecs(ball, p1)) {
      gradient = calculateGradient(ball, p1);
      dir = RIGHT;
    }
    if (CheckCollisionRecs(ball, p2)) {
      gradient = calculateGradient(ball, p2);
      dir = LEFT;
    }

    if (CheckCollisionRecs(ball, p1Gate)) {
      resetBall(&ball);
      scores[1] += 1;
    }

    if (CheckCollisionRecs(ball, p2Gate)) {
      resetBall(&ball);
      scores[0] += 1;
    }

    sprintf(p1Score, "%d", scores[0]);
    sprintf(p2Score, "%d", scores[1]);


    BeginDrawing();
        DrawText(p1Score, (SCREEN_WIDTH / 2) + 50, 10, 40, WHITE);
        DrawText(p2Score, (SCREEN_WIDTH / 2) - 50, 10, 40, WHITE);
        DrawRectangleLinesEx(border, 5.0, WHITE);
        DrawRectangleRec(p1, WHITE);
        DrawRectangleRec(p2, WHITE);
        DrawRectangleRec(ball, WHITE); 
	ClearBackground(BLACK);
    EndDrawing();
  }
}

//TODO: this needs to be better
//idea convert to float div by ten and round to nearest dp
int calculateGradient(Rectangle ball, Rectangle paddle) {
  Rectangle collision = GetCollisionRec(ball, paddle);
  int collisionCentre = collision.y + (collision.height / 2);
  int paddleCentre = paddle.y + (paddle.height / 2);
  int gradient = (paddleCentre - collisionCentre);
  return (gradient / 10) * -1;
}

bool isCursorOnScreen(int pos) {
  if (pos > SCREEN_HEIGHT || pos < 0) {
    return false;
  } 
  return true;
}

void resetBall(Rectangle* ball) {
  ball->x = SCREEN_WIDTH / 2;
  ball->y = SCREEN_HEIGHT / 2;
}
