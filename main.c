#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH  500
#define SCREEN_HEIGHT 500

#define PADDLE_HEIGHT 75
#define PADDLE_WIDTH  15

#define BALL_SPEED 1


bool isCursorOnScreen(int pos);

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
  HideCursor();
  int gradient = 0;
  Direction dir = LEFT;
  
  
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
    ball.y += gradient;

    if (CheckCollisionRecs(ball, p1)) {
      dir = RIGHT;
    }
    if (CheckCollisionRecs(ball, p2)) {
      dir = LEFT;
    }

    BeginDrawing();
        DrawRectangleLinesEx(border, 5.0, WHITE);
        DrawRectangleRec(p1, WHITE);
        DrawRectangleRec(p2, WHITE);
        DrawRectangleRec(ball, WHITE); 
    ClearBackground(BLACK);
    EndDrawing();
  }
}

bool isCursorOnScreen(int pos) {
  if (pos > SCREEN_HEIGHT || pos < 0) {
    return false;
  } 
  return true;
}
