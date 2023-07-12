//
// Created by Jose Antonio on 1/5/22.
//

#ifndef PRACTICA5_AG_COLOR_H
#define PRACTICA5_AG_COLOR_H


class Color {
private:
    float r,g,b;
public:
    Color(){};
    Color(float r, float g, float b);
    Color(const Color& orig);
    virtual ~Color();
    bool operator==(const Color & c);
    float* getColor();
    void setR(float value);
    void setG(float value);
    void setB(float value);
    float getR(){return r;};
    float getG(){return g;};
    float getB(){return b;};
};


#endif //PRACTICA5_AG_COLOR_H
