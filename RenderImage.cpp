#include "stdafx.h"
#include "RenderImage.h"


RenderImage::RenderImage()
{
}

RenderImage::RenderImage(int resH, int resV){
	img.create(resH, resV);
}


RenderImage::~RenderImage()
{
}

void RenderImage::setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
	img.setPixel(x, y, sf::Color(r, g, b));
}


std::vector<char> RenderImage::getPixel(int x, int y) {
	sf::Color pixelColor= img.getPixel(x, y);
	return std::vector<char>( {char(pixelColor.r), char(pixelColor.g), char(pixelColor.b)} );
}


void RenderImage::saveImage(std::string fileName) {
	img.saveToFile(fileName);
}


void RenderImage::loadImage(std::string fileName) {
	img.loadFromFile(fileName);
}

int RenderImage::getResH() {
	return img.getSize().x;
}

int RenderImage::getResV() {
	return img.getSize().y;
}

sf::Image RenderImage::getImage() {
	return img;
}