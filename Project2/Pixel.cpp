//
// Created by Matthew Dylewski on 3/24/22.
//

#include "Pixel.h"

Pixel::Pixel() {
    red = 0;
    green = 0;
    blue = 0;
}
Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}
unsigned char Pixel::getColor(unsigned int c){
    switch(c){
        case 0:
                return red;
        case 1:
                return green;
        case 2:
                return blue;
    }
    return 0;
}