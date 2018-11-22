//Author: Bartosz Zurawski (c00165634)
//Date: 24/11/16
// openGL .////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <GL/glut.h>




////////////////////////////////////////////////////////////
///Entrypoint of application
////////////////////////////////////////////////////////////
void drawSquare();


int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL");


    //prepare OpenGL surface for HSR
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour

	double tx = -0.5, ty = -0.5;
	double speed = 0.01;

    // Start game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left))
				tx -= speed;
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down))
				ty -= speed;
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right))
				tx += speed;
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up))
				ty += speed;


        }

        //Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);//draw a Triangle
			glColor3d(0, 1, 1);//cyan
			glVertex2d(0,0);
			glColor3d(1, 1, 0);//yellow
			glVertex2d(0.5,0.5);
			glColor3d(1, 0, 1);//magenta
			glVertex2d(0, -1);
		glEnd();

		glColor3d(1, 1, 1);
		glBegin(GL_LINE_LOOP);
			glVertex2d(-.99, -.99);
			glVertex2d(+.99, -.99);
			glVertex2d(+.99, +.99);
			glVertex2d(-.99, +.99);
		glEnd();


		glBegin(GL_TRIANGLES);
		glColor3d(1, 0.5, 0.2);
		glVertex2d(tx,ty);
		glVertex2d(tx+0.25,ty+ 0.25);
		glVertex2d(tx+ 0.25,ty);

		glEnd();


        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
