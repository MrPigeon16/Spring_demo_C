#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>
#include <math.h>


#define WIDTH 800
#define HEIGHT 450
#define POINT_NUM 5
#define Y_LOW_SPRING 250
#define Y_HIGH_SPRING 200
#define LINE_THICKNESS 4

#define CALC_X(K,F) (F / K)

typedef struct Spring
{
    double distance;
    int point_number;
    double angle;
    double init_area;
    Rectangle rec[3];

}Spring;






void update_spring(Spring* s, int new_x)
{
    if(s->rec[s->point_number].x <= new_x)
    {
        for(int i = 0; i <= s->point_number; i++)
        { 
            s->rec[i].x += i / 1; 
            double current_d = s->rec[1].x;
            double h = (2 * s->init_area) / (0.5 * current_d); 
            Vector2 first_top = {s->rec[i].x + (0.5 * current_d), s->rec[i].y - h};
            Vector2 second_top = {s->rec[i].x - (0.5 * current_d), s->rec[i].y - h};
            if (i != s->point_number) DrawLineEx((Vector2){s->rec[i].x, s->rec[i].y}, first_top, LINE_THICKNESS, BLACK);
            if (i != 0) DrawLineEx((Vector2){s->rec[i].x, s->rec[i].y}, second_top, LINE_THICKNESS, BLACK);
            
            Rectangle mass = s->rec[s->point_number];
            mass.y -= 25;
            mass.height = 50;
            mass.width = mass.height;
            DrawRectangleRec(mass , BLACK);
            
            BeginDrawing();
        }
    }
}

// b / cos(a)


void draw_spring(Rectangle* rec)
{

    int add = 1;
    for(int i = 0; i < POINT_NUM; i++)
    {
        rec[i].x += add;
        add *= 1.5;
    }
    
}

int main(int argc, char** argv)
{
    /*
     * F = kx
     * x = F / k
     * Arg 1 = F
     * Arg 2 = k
     *
     * */


    printf("Spring with RayLib!\n");
    InitWindow(WIDTH, HEIGHT, "Spring Type shit");
    SetTargetFPS(30);
    
    Spring s = { 0 };
    s.distance = 20;
    s.point_number = POINT_NUM - 1;
    s.init_area = 0.5 * (s.distance * s.distance);
    Rectangle rec = {0, 200, 10 ,20};
    
    for(int i = 0; i < POINT_NUM; i++)
    {
           s.rec[i] = rec;
           rec.x += s.distance;
    }

    while(!WindowShouldClose())
    { 
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLineEx((Vector2){0,225}, (Vector2){WIDTH, 225}, 3, BLACK);
        update_spring(&s, (int)CALC_X(atoi(argv[2]),atoi(argv[1])));

        DrawText("Spring Demo!", 260, 10, 40, BLACK);
        EndDrawing();
    }
    CloseWindow();
    



    return 0;
}

