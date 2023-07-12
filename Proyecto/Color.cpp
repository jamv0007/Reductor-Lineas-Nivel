//
// Created by Jose Antonio on 1/5/22.
//

#include "Color.h"

Color::Color(float r, float g, float b):r(r),g(g),b(b) {

}

Color::~Color() {

}

Color::Color(const Color &orig) {
    this->r = orig.r;
    this->g = orig.g;
    this->b = orig.b;
}

bool Color::operator==(const Color &c) {
    return (r == c.r && g == c.g && b == c.b);
}

float *Color::getColor() {
    float c[3];
    c[0] = r;
    c[1] = g;
    c[2] = b;
    return c;
}

void Color::setR(float value) {
    r = value;
}

void Color::setG(float value) {
    g = value;
}

void Color::setB(float value) {
    b = value;
}