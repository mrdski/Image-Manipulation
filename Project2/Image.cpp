//
// Created by Matthew Dylewski on 3/24/22.
//

#include "Image.h"

using namespace std;

Image::Image(){
    headerObject.idLength = 0;
    headerObject.width = 0;
    headerObject.height = 0;
}
Image::Image(Header h){
    headerObject = h;
}
void Image::AddPixel(Pixel p){
    ps.push_back(p);
}
Image::Header Image::getHeader(){
    return headerObject;
}
Pixel Image::getPixelIndex(unsigned int index){
    return ps.at(index);
}
int Image::getPixelCount(){
    return ps.size();
}