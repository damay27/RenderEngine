#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <vector>

class RenderImage
{
public:
	RenderImage();
	RenderImage(int resH, int resV);
	~RenderImage();
	void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
	std::vector<char> getPixel(int x, int y);
	void saveImage(std::string fileName);
	void loadImage(std::string fileName);
	int getResH();
	int getResV();
	sf::Image getImage();


private:
	sf::Image img;
};

