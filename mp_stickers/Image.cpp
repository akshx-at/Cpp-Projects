#include <iostream>
#include "Image.h"
#include "string.h"
#include "cs225/PNG.h"
using namespace std;


    Image::Image(){
    }
    Image::Image(unsigned int width, unsigned int height): PNG(width, height){
        // height_ = height;
        // width_ = width;
    }
    void Image::darken(){
        //Darkens the image by decreasing its luminance by 0.1 and makes sure that
        // the luminance is between 0 & 1
        for(unsigned i = 0; i < height();i++){
            for(unsigned j = 0; j < width();j++){
                cs225::HSLAPixel& singlepixel = getPixel(j,i);
                singlepixel.l -= 0.1;
                if (singlepixel.l < 0 ){
                    singlepixel.l = 0;
                }
            }
        }
    }
    void Image::darken(double amount){
        //Darkens the image by decreasing its luminance by the amount given and makes sure that
        // the luminance is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel & singlepixel1 = getPixel(j,i);
                singlepixel1.l -= amount;
                if (singlepixel1.l < 0 ){
                    singlepixel1.l = 0;
                }
            }
        }
    }
    void Image::desaturate(){
        //Darkens the image by decreasing its saturation by 0.1 and makes sure that
        // the saturation is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                singlepixel2.s -= 0.1;
                if (singlepixel2.s < 0 ){
                    singlepixel2.s = 0;
                }
            }
        }
    }
    void Image::desaturate(double amount){
        //Darkens the image by decreasing its saturation by the amount and makes sure that
        // the saturation is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel3 = getPixel(j,i);
                singlepixel3.s -= amount;
                if (singlepixel3.s < 0 ){
                    singlepixel3.s = 0;
                }
                else if(singlepixel3.l < 0){
                    singlepixel3.l = 0;
                }
            }
        }
    }
    void Image::lighten(){
        //lighten the image by increasing its luminance by 0.1 and makes sure that
        // the saturation is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                singlepixel2.l += 0.1;
                if (singlepixel2.l > 1 ){
                    singlepixel2.l = 1;
                }
                else if(singlepixel2.l < 0){
                    singlepixel2.l = 0;
                }
            }
        }
    }
    void Image::lighten(double amount){
        //lightens the image by increasing its luminance by the amount and makes sure that
        // the luminnace  is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                singlepixel2.l += amount;
                if (singlepixel2.l > 1 ){
                    singlepixel2.l = 1;
                }
            }
        }
    }
    void Image::saturate(){
        //Darkens the image by decreasing its saturation by 0.1 and makes sure that
        // the saturation is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                singlepixel2.s += 0.1;
                if (singlepixel2.s > 1 ){
                    singlepixel2.s = 1;
                }
            }
        }
    }
    void Image::saturate(double amount){
        //Darkens the image by decreasing its saturation by 0.1 and makes sure that
        // the saturation is between 0 & 1
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                singlepixel2.s += amount;
                if (singlepixel2.s > 1 ){
                    singlepixel2.s = 1;
                }
            }
        }
    }
    void Image::grayscale(){
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
            cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
            singlepixel2.s = 0; //we set the saturation to 0 because saturation defers the color for the pixel from grey
            }
        }
    }
    void Image::illinify(){
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                //illini orange = 11
                //illini blue = 216
                double hueval = singlepixel2.h;
                if (hueval < 113.5 | hueval > 293.5){
                    singlepixel2.h = 11;
                }
                else{
                    singlepixel2.h = 216;
                }
            }
        }
    }
    void Image::rotateColor(double degrees){
        for(unsigned i = 0; i<height();i++){
            for(unsigned j = 0; j<width();j++){
                cs225::HSLAPixel& singlepixel2 = getPixel(j,i);
                double wheel = singlepixel2.h;
                if (degrees >= 0 ){
                    wheel += degrees;
                    if ( wheel > 360){
                        double diff = wheel - 360;
                        wheel =  diff;
                        singlepixel2.h=wheel;
                    }
                    else{
                        singlepixel2.h=wheel;
                    }
                }
                else if (degrees < 0){
                     wheel += degrees;
                    if (wheel < 0){
                        double diff = wheel + 360;
                        wheel = diff;
                        singlepixel2.h = wheel;
                    }
                    else{
                    singlepixel2.h=wheel;
                    }
                }
            }
        }
    }
        void Image::scale(double factor){
        PNG *image = new PNG(*this);
        resize(width() * factor, height() * factor);
        for (size_t i = 0; i < width(); i++){
            for (size_t j = 0; j < height(); j++) {
                cs225::HSLAPixel& pixel1 = getPixel(i,j);
                cs225::HSLAPixel& pixel2 = image->getPixel(i/factor,j/factor);
                pixel1 = pixel2;
            }
        }
        delete image;  
    }
        void Image::scale(unsigned w, unsigned h){ 
        double factor2 = (h*1.0)/height();
        double factor3 = (w*1.0)/width();
        double factor =min(factor3,factor2);
        scale(factor); 

    }
