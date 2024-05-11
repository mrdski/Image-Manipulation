//
// Created by Matthew Dylewski on 3/24/22.
//

#ifndef PROJECT2_METHODS_H
#define PROJECT2_METHODS_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.h"

using namespace std;
class Methods{
public:
    Image read(string f);
    void write(string f, Image i);
    Image Multiply(Image t, Image b);
    Image Subtract(Image t, Image b);
    Image Screen(Image t, Image b, Image s);
    Image Overlay(Image t, Image b);
    Image AddColor(Image t, unsigned char r, unsigned char g, unsigned char b);
    Image Scale(Image t, float r, float g, float b);
    vector <Image> Separate(Image i);
    Image Combine(Image r, Image g, Image b);
    Image Rotate(Image i);
    void Compare(Image mine, Image example);
    Image ExtraCredit(Image a, Image b, Image c, Image d);
};

#endif //PROJECT2_METHODS_H
