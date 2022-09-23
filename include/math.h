#pragma once

#include <iostream>

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    Vector2f operator+(Vector2f &that) 
    {   
        Vector2f res;
        res.x = this->x + that.x;
        res.y = this->y + that.y;
        return res;
    }

    Vector2f operator*(double that) 
    {   
        Vector2f res;
        res.x = this->x * that;
        res.y = this->y * that;
        return res;
    }

    Vector2f operator/(int that) 
    {   
        Vector2f res;
        res.x = this->x / that;
        res.y = this->y / that;
        return res;
    }

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }
    
    float x, y;
};