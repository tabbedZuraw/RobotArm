//Author: Bartosz Zurawski (c00165634)
//Date: 24/11/16
// Robot Arm
#include "SFML/Graphics.hpp"

int main() {
	float rotation[4]={0.f,0.f,0.f, 0.f};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
	sf::RenderWindow window(sf::VideoMode(1000, 500, 64), "RobotArm:    Controls: z,x,a,s,q,w", sf::Style::Default, settings);
	window.setFramerateLimit(60);


	sf::VertexArray mainArm(sf::Quads,4);
	sf::Vector2f possition[4];
	possition[0] = sf::Vector2f(0  , 0);
	possition[1] = sf::Vector2f(160, 0);
	possition[2] = sf::Vector2f(160, 40);
	possition[3] = sf::Vector2f(0  , 40);
	for(int i=0;i<4;i++) {
	mainArm[i].texCoords = possition[i];
    mainArm[i].color = sf::Color::Red;      }
	sf::Vector2f mainArmPos(500.f, 330.f);

	sf::VertexArray secondArm(sf::Quads, 4);
	sf::Vector2f possition2[4];
	possition2[0]=sf::Vector2f(0,0);
	possition2[1]=sf::Vector2f(130,0);
	possition2[2]=sf::Vector2f(130,-40);
	possition2[3]=sf::Vector2f(0,-40);
	for(int i=0;i<4;i++) {
	secondArm[i].texCoords = possition2[i];
    secondArm[i].color = sf::Color::Blue;   }
	sf::Vector2f secArmPos(160.f, 40.f);

	sf::VertexArray clawOne(sf::Quads, 4);
	sf::Vector2f possition3[4];
	possition3[0]=sf::Vector2f(0,0);
	possition3[1]=sf::Vector2f(50,0);
	possition3[2]=sf::Vector2f(50,-13);
	possition3[3]=sf::Vector2f(0,-13);
	for(int i=0;i<4;i++) {
	clawOne[i].texCoords = possition3[i];
    clawOne[i].color = sf::Color::Green;    }
    sf::Vector2f clawOnePos(120.f,0.f);

	sf::VertexArray clawTwo(sf::Quads, 4);
	sf::Vector2f possition4[4];
	possition4[0]=sf::Vector2f(0,0);
	possition4[1]=sf::Vector2f(50,0);
	possition4[2]=sf::Vector2f(50,13);
	possition4[3]=sf::Vector2f(0,13);
	for(int i=0;i<4;i++) {
	clawTwo[i].texCoords = possition4[i];
    clawTwo[i].color = sf::Color::Green;    }
	sf::Vector2f clawTwoPos(120.f,-40.f);

	sf::VertexArray clawSubOne(sf::Quads, 4);
	sf::Vector2f possition5[4];
	possition5[0]=sf::Vector2f(0,0);
	possition5[1]=sf::Vector2f(-7,0);
	possition5[2]=sf::Vector2f(-7,-25);
	possition5[3]=sf::Vector2f(0,-25);
	for(int i=0;i<4;i++) {
	clawSubOne[i].texCoords = possition5[i];
	clawSubOne[i].color = sf::Color::Yellow;    }
	sf::Vector2f clawSubOnePos(50.f,0.f);

	sf::VertexArray clawSubTwo(sf::Quads, 4);
	sf::Vector2f possition6[4];
	possition6[0]=sf::Vector2f(0,0);
	possition6[1]=sf::Vector2f(7,0);
	possition6[2]=sf::Vector2f(7,25);
	possition6[3]=sf::Vector2f(0,25);
	for(int i=0;i<4;i++) {
	clawSubTwo[i].texCoords = possition6[i];
    clawSubTwo[i].color = sf::Color::Yellow;    }
	sf::Vector2f clawSubTwoPos(43.f,0.f);

    bool loop = true;
	while (loop == true){
		sf::Event Event;
		while (window.pollEvent(Event)){

			if (Event.key.code == sf::Keyboard::Escape){
				loop = false;}
			if (Event.key.code == sf::Keyboard::X){
				if (rotation[0] < 90)
					rotation[0]+=5;
			}
			if (Event.key.code == sf::Keyboard::Z){
                if (rotation[0] > -90)
					rotation[0]-=5;
			}
			if (Event.key.code == sf::Keyboard::A){
				if (rotation[1] > -90)
					rotation[1]-=5;
			}
			if (Event.key.code == sf::Keyboard::S){
				if (rotation[1] < 90)
					rotation[1]+=5;
			}
			if (Event.key.code == sf::Keyboard::W){
				if (rotation[2] > 0){
					rotation[2]-=5;
					rotation[3]+=5;
				}
			}
			if (Event.key.code == sf::Keyboard::Q){
				if (rotation[2] < 45){
					rotation[2]+=5;
					rotation[3]-=5;
				}
			}
		}

		sf::Transform T;
		T.translate(mainArmPos);
		sf::Transform R;
		R.rotate(rotation[0]);
		sf::Transform M=T*R;

		sf::Transform T2;
		T2.translate(secArmPos);
		sf::Transform R2;
		R2.rotate(rotation[1]);
		sf::Transform M2=M*T2*R2;

		sf::Transform T3;
		T3.translate(clawOnePos);
		sf::Transform R3;
		R3.rotate(rotation[2]);
		sf::Transform M3=M2*T3*R3;

		sf::Transform T4;
		T4.translate(clawTwoPos);
		sf::Transform R4;
		R4.rotate(rotation[3]);
		sf::Transform M4=M2*T4*R4;

		sf::Transform T5;
		T5.translate(clawSubOnePos);
		sf::Transform M5=M3*T5;

		sf::Transform T6;
		T6.translate(clawSubTwoPos);
		sf::Transform M6=M4*T6;

		for(int i=0;i<4;i++) {
			mainArm[i].position=M.transformPoint(possition[i]);
			secondArm[i].position=M2.transformPoint(possition2[i]);
			clawOne[i].position=M3.transformPoint(possition3[i]);
			clawTwo[i].position=M4.transformPoint(possition4[i]);
			clawSubOne[i].position=M5.transformPoint(possition5[i]);
			clawSubTwo[i].position=M6.transformPoint(possition6[i]);
		}

		window.clear();
		window.draw(mainArm);
		window.draw(clawOne);
		window.draw(clawTwo);
		window.draw(secondArm);
		window.draw(clawSubOne);
		window.draw(clawSubTwo);
		window.display();

	}
}
