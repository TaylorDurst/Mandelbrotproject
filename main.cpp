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

//makes not distort
double aspectRatio = height / width;
ComplexPlane complex_p(aspectRatio);

//renders window with the message Mandelbrot Project!
RenderWindow window(vm,"Mandelbrot Project!", Style::Default);
Text messageText;
Font font;

//Type of font
font.loadFromFile("./font/Game Of Squids.ttf");
messageText.setFont(font);

//each pixels
VertexArray vArray;
vArray.setPrimitiveType(Points);
vArray.resize(height*width);

//enum class
windowStatus status= windowStatus::CALCULATING; 
Event event;

//Starts when window opens
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            //Before it goes through anything, it checks if the window has closed   
            if(event.type == Event::Closed) 
            {
                window.close();
            }
            //Looks for user input - when the mouse has been pressed
            if(event.type == Event::MouseButtonPressed)
            { 
                //uses the vector to track the mouse position
                Vector2i mouse_pos;
				Vector2f mouse_Coord; 

                //get pos
				mouse_Coord = window.mapPixelToCoords(Mouse::getPosition(window),complex_p.getView());
				complex_p.setCenter(mouse_Coord);
                	
                //Zooms out if right clicked on mouse
				if (event.mouseButton.button == Mouse::Right)
    			{
					complex_p.zoomOut();
				}
				//Zooms in if left mouse click
				if (event.mouseButton.button == Mouse::Left)
    			{
					complex_p.zoomIn();
				}
                //Finds the center 
                complex_p.setCenter(mouse_Coord);
				status= windowStatus::CALCULATING;
            }
            
            //Checks if mouse has moved
            if(event.type == Event::MouseMoved)
			{
				Vector2i mouse_pos;
				Vector2f mouse_Coord;
                
                //Gets pos
				mouse_pos = window.mapCoordsToPixel(Vector2f(event.mouseMove.x, event.mouseMove.y), complex_p.getView());
				mouse_Coord= Vector2f(mouse_pos);

				complex_p.setMouseLocation(mouse_Coord);
			}
        }
        //After going through the if statments, it then checks to see if you have closed the window
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }

            //Where the calculations occur
       if (status == windowStatus::CALCULATING)
		{

			  for(int j = 0; j < width; j++)
                {
                    for(int i = 0; i < height; i++)
                    {
                        size_t counter = 0;
                        Uint8 r,g,b = 255;
                        vArray[j+i*width].position = {(float)j,(float)i};
                        //corresponds to pixel location
                        Vector2i points{j,i};
                        Vector2f coords; 
                        coords = window.mapPixelToCoords(points,complex_p.getView());
                        //Stores the coords and the number of iterations
                        counter = complex_p.countIterations(coords);
                        complex_p.iterationsToRGB(counter,r,g,b);
                        //colors
                        vArray[j+i*width].color = {r,g,b};
                    }
                }
            //Set state to display and call the messageText
			status = windowStatus::DISPLAYING;
			complex_p.loadText(messageText);
                
        }
            //Draws the Scene segment
                window.clear();
                window.draw(vArray);
                window.draw(messageText);
                window.display();
            
            
    }
return 0; 
}
