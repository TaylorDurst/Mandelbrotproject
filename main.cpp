#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main()
{

//size of window	
double width = VideoMode::getDesktopMode().width;
double height = VideoMode::getDesktopMode().height;
VideoMode vm(width, width);

//makes not distortd
double aspectRatio = height / width;
ComplexPlane complex_p(aspectRatio);

RenderWindow window(vm,"Mandelbrot Project!", Style::Default);
Text messageText;
Font font;

font.loadFromFile("./font/Game Of Squids.ttf");
messageText.setFont(font);

//each pixels
VertexArray vArray;
vArray.setPrimitiveType(Points);
vArray.resize(height*width);

windowStatus status= windowStatus::CALCULATING; // enum 
Event event;


    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            
            if(event.type == Event::Closed) 
            {
                window.close();
            }

            if(event.type == Event::MouseButtonPressed)
            { 

        
                Vector2i mouse_pos;
				Vector2f mouse_Coord; //vectors

                //get pos
				mouse_Coord = window.mapPixelToCoords(Mouse::getPosition(window),complex_p.getView());

				complex_p.setCenter(mouse_Coord);
                	
				if (event.mouseButton.button == Mouse::Right)
    			{
					complex_p.zoomOut();
				}
				
				if (event.mouseButton.button == Mouse::Left)
    			{
					complex_p.zoomIn();
					

				}
                complex_p.setCenter(mouse_Coord);
				status= windowStatus::CALCULATING;

			

            }
            
            if(event.type == Event::MouseMoved)
			{
				
				Vector2i mouse_pos;
				Vector2f mouse_Coord;

				mouse_pos = window.mapCoordsToPixel(Vector2f(event.mouseMove.x, event.mouseMove.y), complex_p.getView());
				mouse_Coord= Vector2f(mouse_pos);

				complex_p.setMouseLocation(mouse_Coord);
			}
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
       if (status == windowStatus::CALCULATING)
		{

			  for(int j = 0; j < width; j++)
                {
                    for(int i = 0; i < height; i++)
                    {
                        size_t counter = 0;
                        Uint8 r,g,b = 255;
                        vArray[j+i*width].position = {(float)j,(float)i};
                        Vector2i points{j,i};
                        Vector2f coords; 
                        coords = window.mapPixelToCoords(points,complex_p.getView());
                        counter = complex_p.countIterations(coords);
                        complex_p.iterationsToRGB(counter,r,g,b);
                        vArray[j+i*width].color = {r,g,b};
                    }
                }

			status = windowStatus::DISPLAYING;
			complex_p.loadText(messageText);
                
        }
            
                window.clear();
                window.draw(vArray);
                window.draw(messageText);
                window.display();
            
            
    }
return 0; 
}
