#include "raylib.h"
#include <math.h>

#define WIDTH 900
#define HEIGHT 600


float time = 0;
float sunY = 120;
float cloudX = -200;
float birdX = -100;
float wavePower = 10;



void DrawCloud(float x, float y)
{
    DrawCircle(x,y,35,WHITE);
    DrawCircle(x+40,y,45,WHITE);
    DrawCircle(x+80,y,35,WHITE);
    DrawRectangle(x-20,y,120,35,WHITE);
}



void DrawSun()
{
    DrawCircle(
        WIDTH/2,
        sunY,
        70,
        ORANGE
    );

    DrawCircle(
        WIDTH/2,
        sunY,
        55,
        YELLOW
    );
}



void DrawOcean()
{

    DrawRectangle(
        0,
        350,
        WIDTH,
        250,
        BLUE
    );


    for(int y=360;y<600;y+=25)
    {

        for(int x=0;x<WIDTH;x+=20)
        {

            float wave =
            sin(time*3+x*0.05)
            *wavePower;


            DrawLine(
                x,
                y+wave,
                x+15,
                y+wave,
                SKYBLUE
            );

        }
    }

}



void DrawPalmTree(int x,int y)
{

    float wind =
    sin(time*2)*5;


    DrawLineEx(
        (Vector2){x,y},
        (Vector2){x,y-150},
        12,
        BROWN
    );


    DrawLineEx(
        (Vector2){x,y-150},
        (Vector2){x-80+wind,y-200},
        8,
        DARKGREEN
    );


    DrawLineEx(
        (Vector2){x,y-150},
        (Vector2){x+80+wind,y-200},
        8,
        DARKGREEN
    );


    DrawLineEx(
        (Vector2){x,y-150},
        (Vector2){x,y-230},
        8,
        DARKGREEN
    );

}



void DrawBird(float x,float y)
{

    DrawLine(
        x,y,
        x+15,y-10,
        BLACK
    );


    DrawLine(
        x+15,y-10,
        x+30,y,
        BLACK
    );

}



void DrawStars()
{

    if(sunY>220)
    {

        for(int i=0;i<100;i++)
        {

            int x=(i*71)%WIDTH;
            int y=(i*37)%200;


            DrawCircle(
                x,
                y,
                2,
                WHITE
            );

        }

    }

}




int main()
{

    InitWindow(
        WIDTH,
        HEIGHT,
        "Ocean Sunset Animation"
    );


    SetTargetFPS(60);



    while(!WindowShouldClose())
    {

        time += GetFrameTime();



        // Sun movement

        sunY += GetFrameTime()*5;


        if(sunY>250)
            sunY=120;



        // Cloud movement

        cloudX += GetFrameTime()*30;


        if(cloudX>WIDTH+200)
            cloudX=-250;



        // Bird movement

        birdX += GetFrameTime()*50;


        if(birdX>WIDTH+100)
            birdX=-100;



        // Wave control

        if(IsKeyDown(KEY_SPACE))
            wavePower=25;
        else
            wavePower=10;



        BeginDrawing();



        if(sunY>220)
            ClearBackground(DARKBLUE);
        else
            ClearBackground(SKYBLUE);



        DrawStars();



        DrawCloud(
            cloudX,
            100
        );


        DrawCloud(
            cloudX-300,
            170
        );



        DrawSun();



        DrawOcean();



        // Sun reflection

        DrawRectangle(
            WIDTH/2-40,
            350,
            80,
            200,
            Fade(YELLOW,0.3)
        );



        // Palm trees

        DrawPalmTree(
            120,
            450
        );


        DrawPalmTree(
            760,
            450
        );



        // Birds

        DrawBird(
            birdX,
            150
        );


        DrawBird(
            birdX+180,
            200
        );



        DrawText(
            "SPACE = Strong Waves",
            20,
            20,
            20,
            WHITE
        );



        EndDrawing();

    }



    CloseWindow();


    return 0;
}