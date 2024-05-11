#include <iostream>
#include <vector>
#include "Image.h"
#include "Methods.h"
using namespace std;
int main() {
    Methods m;
    Image t1 = m.read("input/layer1.tga");
    Image b1 = m.read("input/pattern1.tga");
    Image p1 = m.Multiply(t1,b1);
    m.write("output/part1.tga", p1);
    Image ex1 = m.read("examples/EXAMPLE_part1.tga");
    cout<<"Test 1 ";
    m.Compare(p1, ex1);

    Image t2 = m.read("input/layer2.tga");
    Image b2 = m.read("input/car.tga");
    Image p2 = m.Subtract(t2,b2);
    m.write("output/part2.tga",p2);
    Image ex2 = m.read("examples/EXAMPLE_part2.tga");
    cout<<"Test 2 ";
    m.Compare(p2, ex2);

    Image t3 = m.read("input/layer1.tga");
    Image b3 = m.read("input/pattern2.tga");
    Image s = m.read("input/text.tga");
    Image p3 = m.Screen(t3,b3,s);
    m.write("output/part3.tga",p3);
    Image ex3 = m.read("examples/EXAMPLE_part3.tga");
    cout<<"Test 3 ";
    m.Compare(p3, ex3);

    Image t4 = m.read("input/layer2.tga");
    Image b4 = m.read("input/circles.tga");
    Image mtb = m.Multiply(t4,b4);
    Image load4 = m.read("input/pattern2.tga");
    Image p4 = m.Subtract(load4, mtb);
    m.write("output/part4.tga",p4);
    Image ex4 = m.read("examples/EXAMPLE_part4.tga");
    cout<<"Test 4 ";
    m.Compare(p4, ex4);

    Image t5 = m.read("input/layer1.tga");
    Image b5 = m.read("input/pattern1.tga");
    Image p5 = m.Overlay(t5,b5);
    m.write("output/part5.tga", p5);
    Image ex5 = m.read("examples/EXAMPLE_part5.tga");
    cout<<"Test 5 ";
    m.Compare(p5, ex5);

    Image t6 = m.read("input/car.tga");
    Image p6 = m.AddColor(t6, 0, 200, 0);
    m.write("output/part6.tga", p6);
    Image ex6 = m.read("examples/EXAMPLE_part6.tga");
    cout<<"Test 6 ";
    m.Compare(p6, ex6);

    Image t7 = m.read("input/car.tga");
    Image p7 = m.Scale(t7, 4, 1, 0);
    m.write("output/part7.tga", p7);
    Image ex7 = m.read("examples/EXAMPLE_part7.tga");
    cout<<"Test 7 ";
    m.Compare(p7, ex7);

    Image t8 = m.read("input/car.tga");
    vector<Image> p8 = m.Separate(t8);
    m.write("output/part8_r.tga", p8.at(0));
    m.write("output/part8_g.tga", p8.at(1));
    m.write("output/part8_b.tga", p8.at(2));
    Image ex8r = m.read("examples/EXAMPLE_part8_r.tga");
    cout<<"Test 8 Red ";
    m.Compare(p8.at(0), ex8r);
    Image ex8g = m.read("examples/EXAMPLE_part8_g.tga");
    cout<<"Test 8 Green ";
    m.Compare(p8.at(1), ex8g);
    Image ex8b = m.read("examples/EXAMPLE_part8_b.tga");
    cout<<"Test 8 Blue ";
    m.Compare(p8.at(2), ex8b);

    Image t9r = m.read("input/layer_red.tga");
    Image t9g = m.read("input/layer_green.tga");
    Image t9b = m.read("input/layer_blue.tga");
    Image p9 = m.Combine(t9r, t9g, t9b);
    m.write("output/part9.tga", p9);
    Image ex9 = m.read("examples/EXAMPLE_part9.tga");
    cout<<"Test 9 ";
    m.Compare(p9, ex9);

    Image t10 = m.read("input/text2.tga");
    Image p10 = m.Rotate(t10);
    m.write("output/part10.tga", p10);
    Image ex10 = m.read("examples/EXAMPLE_part10.tga");
    cout<<"Test 10 ";
    m.Compare(p10, ex10);

    Image t11Car = m.read("input/car.tga");
    Image t11Circle = m.read("input/circles.tga");
    Image t11Pattern = m.read("input/pattern1.tga");
    Image t11Text = m.read("input/text.tga");
    Image p11 = m.ExtraCredit(t11Car, t11Circle, t11Text, t11Pattern);
    m.write("output/extracredit.tga", p11);
    Image ex11 = m.read("examples/EXAMPLE_extracredit.tga");
    cout<<"Test ExtraCredit ";
    m.Compare(p11, ex11);

    return 0;
}