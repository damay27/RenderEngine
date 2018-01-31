
#include "stdafx.h"
#include <iostream>
#include "Triangle.hpp"
#include "Vector3D.h"
#include "Raycast.h"
//#include "SFML\Graphics.hpp"
//#include "RaycastCamera.h"
#include "matrix.h"
#include "matrixSizeException.h"
#include "TransformMatrix.h"
#include "Camera.h"
#include "Transform3D.h"
#include "Light.h"
using namespace std;

int main()
{
	/*Vector3D a(5, -1, 0);
	Vector3D b(1, 1, 0);
	Vector3D c(1, 0, 1);
	Vector3D x(c);
	Triangle t(a, b, c, x);

	Vector3D origin(0, 0, 0);
	float planeWidth = 1;
	float planeHieght = .75;
	float focalLenght = .25;
	int resH = 640;
	int resV = 480;
	float stepH = planeWidth / resH;
	float stepV = planeHieght / resV;
	float posX = -planeWidth/2;
	float posY = planeHieght / 2;
	sf::Image img;
	img.create(resH, resV);

	cout << "Vertices:" << endl;
	cout << "<" << a.getX() << ", " << a.getY() << ", " << a.getZ() << ">" << endl;
	cout << "<" << b.getX() << ", " << b.getY() << ", " << b.getZ() << ">" << endl;
	cout << "<" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ">" << endl;

	for (int x = 0; x < resH; x++) {

		for (int y = 0; y < resV; y++) {
			Vector3D cast = Raycast(origin, Vector3D(focalLenght, posX, posY), t);

			if (cast.isNull()==false) {
				img.setPixel(x, y, sf::Color::White);
			}

			posY -= stepV;

		}

		posX += stepH;
		posY = planeHieght / 2;
	}


	sf::RenderWindow window(sf::VideoMode(resH, resV), "My window");
	sf::Texture tex;
	tex.create(resH, resV);
	tex.update(img);

	sf::Event event;
	while (1) {
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		window.clear();
		window.draw(sf::Sprite(tex));
		window.display();

	}*/

	/*RaycastCamera camera(640, 480, 90, 67.5);
	camera.setAngles(90, 0);
	camera.setPosition(0, 1, 0);

	Vector3D a(5, 1, 0);
	Vector3D b(5, -1, 0);
	Vector3D c(5, 0, 1);
	Triangle t(a, b, c);

	Vector3D vec = Raycast(Vector3D(0, 0, 0), Vector3D(1, 0, 0), t);

	Object object(vector<Triangle>({ t }), Vector3D(1, 0, 0));

	RenderImage rImg;

	rImg=camera.Render(vector<Object>({ object }));

	sf::Image img = rImg.getImage();

	sf::RenderWindow window(sf::VideoMode(640,480), "My window");
	sf::Texture tex;
	tex.create(640, 480);
	tex.update(img);

	sf::Event event;
	while (1) {
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		window.clear();
		window.draw(sf::Sprite(tex));
		window.display();

	}


	return 0;*/

	//create and position the camera
	Transform3D cameraTransform;
	cameraTransform.translate(-5, 0, 0);
	Camera cam(cameraTransform, 640, 480);

	//create the vertices of the main shape
	Vector3D v1(6, -5, -1), v2(0, 1, -1), v3(5, -5, 2), v4(6,2,-1);

	//now creat the triangles that make up the faces of the shape using the vertices defined above
	Triangle tri1(v1, v2, v3);
	Triangle tri2(v4, v3, v2);
	Triangle tri3(v1, v3, v4);
	Triangle tri4(v1, v3, v4);

	vector<Triangle> triVec;

	triVec.push_back(tri1);
	triVec.push_back(tri2);
	triVec.push_back(tri3);
	triVec.push_back(tri4);

	Material objectMaterial(LAMBERTIAN, color(0, 128, 0), 4);

	Object obj(triVec, v3, objectMaterial);


	//create a triangle for the floor
	Triangle floor(Vector3D(0, -100, -1), Vector3D(100, 100,-1), Vector3D(-100, 100, -1));

	//create the floors material
	Material floorMaterial(LAMBERTIAN, color(0, 0, 128), 4);

	//put the triangle and material together in one object
	Object floorObj;
	floorObj.addTriangle(floor);
	floorObj.setMaterial(floorMaterial);

	//create three lights for the scene
	Light light(Vector3D(3, 2, 4), color(255, 255, 255), .9f);
	Light light1(Vector3D(3, -5, 3), color(255, 255, 255), .5f);
	Light light2(Vector3D(6, 0, 3), color(255, 255, 255), .3f);

	vector<Light> lightVec;

	lightVec.push_back(light);
	lightVec.push_back(light1);
	lightVec.push_back(light2);

	//put both objects into a vector of objects
	vector<Object> objVec;
	objVec.push_back(obj);
	objVec.push_back(floorObj);


	RenderImage rImg = cam.render(objVec, lightVec);

	sf::Image img = rImg.getImage();

	sf::RenderWindow window(sf::VideoMode(640, 480), "My window");
	sf::Texture tex;
	tex.create(640, 480);
	tex.update(img);

	sf::Event event;
	while (1) {
		window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		window.clear();
		window.draw(sf::Sprite(tex));
		window.display();

	}

}

