//
// Created by Matthew Dylewski on 3/24/22.
//
#include "Methods.h"
#include "Pixel.h"
using namespace std;
Image Methods::read(string f){
    ifstream file(f, ios_base::binary);
    Image::Header h;
    file.read(&h.idLength, sizeof(h.idLength));
    file.read(&h.colorMapType, sizeof(h.colorMapType));
    file.read(&h.dataTypeCode, sizeof(h.dataTypeCode));
    file.read((char*)&h.colorMapOrigin, sizeof(h.colorMapOrigin));
    file.read((char*)&h.colorMapLength, sizeof(h.colorMapLength));
    file.read((char*)&h.colorMapDepth, sizeof(h.colorMapDepth));
    file.read((char*)&h.xOrigin, sizeof(h.xOrigin));
    file.read((char*)&h.yOrigin, sizeof(h.yOrigin));
    file.read((char*)&h.width, sizeof(h.width));
    file.read((char*)&h.height, sizeof(h.height));
    file.read(&h.bitsPerPixel, sizeof(h.bitsPerPixel));
    file.read(&h.imageDescriptor, sizeof(h.imageDescriptor));
    Image image = Image(h);
    unsigned char b, g, r;
    for(unsigned int i = 0; i < h.width*h.height; i++){
        file.read((char*)&b, sizeof(b));
        file.read((char*)&g, sizeof(g));
        file.read((char*)&r, sizeof(r));
        Pixel p = Pixel(r,g,b);
        image.AddPixel(p);
    }
    file.close();
    return image;
}
void Methods::write(string f, Image image){
    ofstream file(f, ios_base::binary);
    Image::Header h = image.getHeader();
    file.write(&h.idLength, sizeof(h.idLength));
    file.write(&h.colorMapType, sizeof(h.colorMapType));
    file.write(&h.dataTypeCode, sizeof(h.dataTypeCode));
    file.write((char*)&h.colorMapOrigin, sizeof(h.colorMapOrigin));
    file.write((char*)&h.colorMapLength, sizeof(h.colorMapLength));
    file.write((char*)&h.colorMapDepth, sizeof(h.colorMapDepth));
    file.write((char*)&h.xOrigin, sizeof(h.xOrigin));
    file.write((char*)&h.yOrigin, sizeof(h.yOrigin));
    file.write((char*)&h.width, sizeof(h.width));
    file.write((char*)&h.height, sizeof(h.height));
    file.write(&h.bitsPerPixel, sizeof(h.bitsPerPixel));
    file.write(&h.imageDescriptor, sizeof(h.imageDescriptor));
    unsigned char colors[3];
    for(unsigned int i = 0; i < image.getPixelCount(); i++){
        Pixel p = image.getPixelIndex(i);
        for(unsigned int j = 0; j < 3; j++){
            colors[j] = p.getColor(j);
        }
        file.write((char*)&colors[2], sizeof(colors[2]));
        file.write((char*)&colors[1], sizeof(colors[1]));
        file.write((char*)&colors[0], sizeof(colors[0]));
    }
    file.close();

}
Image Methods::Multiply(Image t, Image b){
    Image image = Image(t.getHeader());
    for(int i = 0; i < t.getPixelCount(); i++){
        Pixel top = t.getPixelIndex(i);
        Pixel bottom = b.getPixelIndex(i);
        float tc[3];
        float bc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
            bc[j] = bottom.getColor(j);
        }
        unsigned char nc[3];
        for(int k = 0; k < 3; k++){
            float temp = ((tc[k]*bc[k])/255) + 0.5f;
            if(temp > 255){
                temp = 255 + 0.5f;
            }
            nc[k] = (unsigned char)temp;
        }
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::Subtract(Image t, Image b){
    Image image = Image(t.getHeader());
    for(int i = 0; i < t.getPixelCount(); i++){
        Pixel top = t.getPixelIndex(i);
        Pixel bottom = b.getPixelIndex(i);
        float tc[3];
        float bc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
            bc[j] = bottom.getColor(j);
        }
        unsigned char nc[3];
        for(int k = 0; k < 3; k++){
            float temp = (bc[k]-tc[k]);
            if(temp < 0){
                temp = 0;
            }
            nc[k] = (unsigned char)temp;
        }
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::Screen(Image t, Image b, Image s){
    Image image = Image(t.getHeader());
    Image m = Multiply(t,b);
    for(int i = 0; i < s.getPixelCount(); i++){
        Pixel top = s.getPixelIndex(i);
        Pixel bottom = m.getPixelIndex(i);
        float tc[3];
        float bc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
            bc[j] = bottom.getColor(j);
        }
        unsigned char nc[3];
        for(int k = 0; k < 3; k++){
            float temp = (1-((1-(tc[k]/255)) * (1-(bc[k]/255))));
            if(temp > 1) temp = 1;
            if(temp < 0) temp = 0;
            temp = temp * 255 + 0.5f;
            nc[k] = (unsigned char)temp;
        }
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::Overlay(Image t, Image b){
    Image image = Image(t.getHeader());
    for(int i = 0; i < t.getPixelCount(); i++){
        Pixel top = t.getPixelIndex(i);
        Pixel bottom = b.getPixelIndex(i);
        float tc[3];
        float bc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
            bc[j] = bottom.getColor(j);
        }
        unsigned char nc[3];
        for(int k = 0; k < 3; k++){
            if((bc[k]/255) <= .5){
                float temp = (2 * (tc[k]/255) * (bc[k]/255));
                if(temp > 1) temp = 1;
                if(temp < 0) temp = 0;
                temp = temp * 255 + 0.5f;
                nc[k] = (unsigned char)temp;
            }
            else{
                float temp = ((1-2*(1-(tc[k]/255))*(1-(bc[k]/255))));
                if(temp > 1) temp = 1;
                if(temp < 0) temp = 0;
                temp = temp * 255 + 0.5f;
                nc[k] = (unsigned char)temp;
            }
        }
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::AddColor(Image t, unsigned char r, unsigned char g, unsigned char b){
    Image image = Image(t.getHeader());
    for(int i = 0; i < t.getPixelCount(); i++){
        Pixel top = t.getPixelIndex(i);
        float tc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
        }
        unsigned char nc[3];
        float tr = (((tc[0]/255) + ((float)r/255)));
        if(tr > 1) tr = 1;
        if(tr < 0) tr = 0;
        tr = tr *255 +0.5f;
        float tg = (((tc[1]/255) + ((float)g/255)));
        if(tg > 1) tg = 1;
        if(tg < 0) tg = 0;
        tg = tg * 255 + 0.5f;
        float tb = (((tc[2]/255) + ((float)b/255)));
        if(tb > 1) tb = 1;
        if(tb < 0) tb = 0;
        tb = tb * 255 +0.5f;
        nc[0] = (unsigned char)tr;
        nc[1] = (unsigned char)tg;
        nc[2] = (unsigned char)tb;
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::Scale(Image t, float r, float g, float b){
    Image image = Image(t.getHeader());
    for(int i = 0; i < t.getPixelCount(); i++){
        Pixel top = t.getPixelIndex(i);
        float tc[3];
        for(int j = 0; j < 3; j++){
            tc[j] = top.getColor(j);
        }
        unsigned char nc[3];
        float tr = (((tc[0]/255) *(r)));
        if(tr > 1) tr = 1;
        if(tr < 0) tr = 0;
        tr = tr * 255 + 0.5f;
        float tg = (((tc[1]/255) *(g)));
        if(tg > 1) tg = 1;
        if(tg < 0) tg = 0;
        tg = tg * 255 + 0.5f;
        float tb = (((tc[2]/255) *(b)));
        if(tb > 1) tb = 1;
        if(tb < 0) tb = 0;
        tb = tb * 255 + 0.5f;
        nc[0] = (unsigned char)tr;
        nc[1] = (unsigned char)tg;
        nc[2] = (unsigned char)tb;
        Pixel p = Pixel(nc[0],nc[1],nc[2]);
        image.AddPixel(p);
    }
    return image;
}
vector <Image> Methods::Separate(Image image){
    vector<Image> temp;
    temp.push_back(Image(image.getHeader()));
    temp.push_back(Image(image.getHeader()));
    temp.push_back(Image(image.getHeader()));
    for(int i = 0; i < image.getPixelCount(); i++){
        Pixel p = image.getPixelIndex(i);
        unsigned char r = p.getColor(0);
        unsigned char g = p.getColor(1);
        unsigned char b = p.getColor(2);
        Pixel re = Pixel(r,r,r);
        Pixel gr = Pixel(g,g,g);
        Pixel bl = Pixel(b,b,b);
        temp.at(0).AddPixel(re);
        temp.at(1).AddPixel(gr);
        temp.at(2).AddPixel(bl);
    }
    return temp;
}
Image Methods::Combine(Image r, Image g, Image b){
    Image image = Image(r.getHeader());
    for(int i = 0; i < r.getPixelCount(); i++){
        unsigned char c[3];
        c[0] = r.getPixelIndex(i).getColor(0);
        c[1] = g.getPixelIndex(i).getColor(0);
        c[2] = b.getPixelIndex(i).getColor(0);
        Pixel p = Pixel(c[0],c[1],c[2]);
        image.AddPixel(p);
    }
    return image;
}
Image Methods::Rotate(Image im){
    Image image = Image(im.getHeader());
    for(int i = im.getPixelCount()-1; i >=0; i--){
        image.AddPixel(im.getPixelIndex(i));
    };
    return image;
}
void Methods::Compare(Image mine, Image example){
    bool error = false;
    if(mine.getHeader().idLength != example.getHeader().idLength){
        cout<<"Error idlength"<<endl;
        error = true;
    }
    if(mine.getHeader().colorMapType != example.getHeader().colorMapType){
        cout<<"Error colormaptype"<<endl;
        error = true;
    }
    if(mine.getHeader().dataTypeCode != example.getHeader().dataTypeCode){
        cout<<"Error datatypecode"<<endl;
        error = true;
    }
    if(mine.getHeader().colorMapOrigin != example.getHeader().colorMapOrigin){
        cout<<"Error colormaporigin"<<endl;
        error = true;
    }
    if(mine.getHeader().colorMapLength != example.getHeader().colorMapLength){
        cout<<"Error colormaplength"<<endl;
        error = true;
    }
    if(mine.getHeader().colorMapDepth != example.getHeader().colorMapDepth){
        cout<<"Error colormapdepth"<<endl;
        error = true;
    }
    if(mine.getHeader().xOrigin != example.getHeader().xOrigin){
        cout<<"Error xOrigin"<<endl;
        error = true;
    }
    if(mine.getHeader().yOrigin != example.getHeader().yOrigin){
        cout<<"Error yOrigin"<<endl;
        error = true;
    }
    if(mine.getHeader().width != example.getHeader().width){
        cout<<"Error width"<<endl;
        error = true;
    }
    if(mine.getHeader().height != example.getHeader().height){
        cout<<"Error height"<<endl;
        error = true;
    }
    if(mine.getHeader().bitsPerPixel != example.getHeader().bitsPerPixel){
        cout<<"Error bitsPerpixel"<<endl;
        error = true;
    }
    if(mine.getHeader().imageDescriptor != example.getHeader().imageDescriptor){
        cout<<"Error imageDescriptor"<<endl;
        error = true;
    }
    for(int i = 0; i < example.getPixelCount(); i++){
        for(int j = 0; j < 3; j++){
            if(mine.getPixelIndex(i).getColor(j) != example.getPixelIndex(i).getColor(j)){
                cout<<"Error pixels";
                error = true;
            }
        }
        if(error==true){
            break;
        }
    }
    if(error == false){
        cout<<"Complete"<<endl;
    }
    else{
        cout<<"Error"<<endl;
    }
}
Image Methods::ExtraCredit(Image a, Image b, Image c, Image d){
    Image::Header head = a.getHeader();
    head.width = a.getHeader().width+b.getHeader().width;
    head.height = c.getHeader().height+a.getHeader().height;
    Image im = Image(head);
    for(int i = 0; i < d.getHeader().height; i++){
        for(int j = 0; j < c.getHeader().width; j++){
            im.AddPixel(c.getPixelIndex(j+(c.getHeader().width*i)));
        }
        for(int j = 0; j < d.getHeader().width; j++){
            im.AddPixel(d.getPixelIndex(j+(d.getHeader().width*i)));
        }
    }
    for(int i = 0; i < a.getHeader().height; i++){
        for(int j = 0; j < a.getHeader().width; j++){
            im.AddPixel(a.getPixelIndex(j+(a.getHeader().width*i)));
        }
        for(int j = 0; j < b.getHeader().width; j++){
            im.AddPixel(b.getPixelIndex(j+(b.getHeader().width*i)));
        }
    }
    return im;
}

