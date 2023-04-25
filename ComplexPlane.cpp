#include "ComplexPlane.h"

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
    m_aspectRatio = aspectRatio;
    m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio); 
    m_view.setCenter(0.0, 0.0);
    m_zoomCount = 0;
}
View ComplexPlane::getView()
{
return m_view;
}

//Mouse click
void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_view.setSize(x_size, y_size);
}


void ComplexPlane::setCenter(Vector2f coord)
{
    m_view.setCenter(coord);
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
    m_mouseLocation = coord;
}
void ComplexPlane::loadText(Text& text){

    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setPosition(50,50);
    
    //text variable
    Vector2f point;
    point = m_view.getCenter();
    ostringstream string;
    string << "Mandelbrot Project!" << endl;
    string << "Center: (" << point.x << ", " << point.y << ")" << endl;
    string << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    string << "Left click to Zoom in" << endl;
    string << "Right click to Zoom out" << endl;

    text.setString(string.str());

}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    complex<double> c(coord.x, coord.y);
    complex<double> z(0,0);
    size_t count = 0;

    while(abs(z) < 2 && count < MAX_ITER)
    {
        
        z = z*z + c;
        count++;
    }
    return count;
}

//colors decide
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    
    if (count == MAX_ITER)
    {
        r=0;
        g=0;
        b=0;

    }

    else if (count>57){
        r=150;
        g=164;
        b=248;

    }

    else if (count>49){
        r=185;
        g=249;
        b=196;
    }

    else if (count>41)
    {
        r=251;
        g=188;
        b=235;

    }

    else if (count>33)
    {
        r=251;
        g=228;
        b=188;

    }

    else if (count>25)
    {
        r=205;
        g=188;
        b=251;

    }

    else if (count>17)
    {
        r=251;
        g=188;
        b=201;

    }

    else if (count>9)
    {
        r=239;
        g=143;
        b=206;

    }

    else
    {
        r=7;
        g=61;
        b=115;
    }



   
}
