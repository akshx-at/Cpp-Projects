/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */
#include <iostream>
#include "cs225/PNG.h"
#include <cstdlib>
#pragma once
using namespace cs225;
    class Image:public PNG{
    public:
        Image();

        Image(unsigned int width, unsigned int height);

        void lighten();

        void lighten(double amount);//double because we want decimal inputs

        void darken();

        void darken(double amount);

        void saturate();

        void saturate(double amount);

        void desaturate();

        void desaturate(double amount);

        void grayscale();

        void rotateColor(double degrees);

        void illinify();

        void scale(double factor);

        void scale(unsigned w,unsigned h);

        unsigned int height_;
        unsigned int width_;
    };

