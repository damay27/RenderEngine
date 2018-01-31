#include "stdafx.h"
#include "color.h"

color::color() : r(255), g(255), b(255)
{

}


color::color(unsigned int red, unsigned int green, unsigned int blue) : r(red), g(green), b(blue)
{
}


color::color(const color &copyColor) {
	r = copyColor.getRed();
	g = copyColor.getGreen();
	b = copyColor.getBlue();
}


void color::operator=(const color &copyColor) {
	r = copyColor.getRed();
	g = copyColor.getGreen();
	b = copyColor.getBlue();
}


color::~color()
{
}


void color::setColor(unsigned char red, unsigned char green, unsigned char blue) {
	r = red;
	g = green;
	b = blue;
}

unsigned int color::getRed()const {
	return r;
}


unsigned int color::getGreen()const {
	return g;
}


unsigned int color::getBlue()const {
	return b;
}


unsigned char color::getRed8bit()const {

	if (r > 255) { return 255; }
	else { return r; }
}


unsigned char color::getGreen8bit()const {
	if (g > 255) { return 255; }
	else { return g; }
}


unsigned char color::getBlue8bit()const {
	if (b > 255) { return 255; }
	else { return b; }
}

color color::operator-(const color &c) {
	unsigned int red = this->r - c.getRed();
	unsigned int green = this->g - c.getGreen();
	unsigned int blue = this->b - c.getBlue();

	return color(red, green, blue);

}


color color::operator+(const color &c) {
	unsigned int red = this->r + c.getRed();
	unsigned int green = this->g + c.getGreen();
	unsigned int blue = this->b + c.getBlue();

	return color(red, green, blue);
}


color color::operator*(float scalar) {
	unsigned int red = static_cast<unsigned int>(this->r*scalar);
	unsigned int green = static_cast<unsigned int>(this->g*scalar);
	unsigned int blue = static_cast<unsigned int>(this->b*scalar);
	return color(red, green, blue);
}


color color::average(const color &c, float inputWeight) {//input weight should be < 1
	float thisColorWeight = 1 - inputWeight;

	unsigned int red = static_cast<unsigned int>( this->r*thisColorWeight + c.getRed()*inputWeight );
	unsigned int green = static_cast<unsigned int>( this->g*thisColorWeight + c.getGreen()*inputWeight );
	unsigned int blue = static_cast<unsigned int>( this->b*thisColorWeight + c.getBlue()*inputWeight );

	return color(red, green, blue);
}