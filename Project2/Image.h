//
// Created by Matthew Dylewski on 3/24/22.
//

#ifndef PROJECT2_IMAGE_H
#define PROJECT2_IMAGE_H
#include <vector>
#include "Pixel.h"

using namespace std;
class Image{
public:
    struct Header{
        char  idLength;
        char  colorMapType;
        char  dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char  colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char  bitsPerPixel;
        char  imageDescriptor;
    };
    Image();
    Image(Header h);
    void AddPixel(Pixel p);
    Header getHeader();
    Pixel getPixelIndex(unsigned int index);
    int getPixelCount();
private:
    Header headerObject;
    //file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    //file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    vector<Pixel> ps;
};
#endif //PROJECT2_IMAGE_H
