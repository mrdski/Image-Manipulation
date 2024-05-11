//
// Created by Matthew Dylewski on 3/24/22.
//

#ifndef PROJECT2_PIXEL_H
#define PROJECT2_PIXEL_H

class Pixel{
    unsigned char red, green, blue;
public:
    Pixel();
    Pixel(unsigned char red, unsigned char green, unsigned char blue);
    unsigned char getColor(unsigned int c);
};

#endif //PROJECT2_PIXEL_H
