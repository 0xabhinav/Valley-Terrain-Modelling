#pragma once
struct point{
    double x,y,z;
};
point origin = {0,0,0};
point camera = {0,0,10};
point dirn = {0,0,0};
point bgcolor = {0,0,1};
point points[8] = {
    {-1.0,-1.0,1.0},
    {-1.0,1.0,1.0},
    {1.0,1.0,1.0},
    {1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},
    {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},
};
float color[8][4] = {
    {1.0,1.0,1.0,1.},
    {1.0,0.0,1.0,1.},
    {1.0,1.0,0.0,1.},
    {0.0,1.0,1.0,1.},
    {0.0,0.0,1.0,1.},
    {0.0,1.0,0.0,1.},
    {1.0,0.0,0.0,1.},
    {0.0,0.0,0.0,1.},
};
