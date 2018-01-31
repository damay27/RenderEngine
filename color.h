#pragma once
class color
{

public:
	color();
	color(unsigned int red, unsigned int green, unsigned int blue);
	color(const color &copyColor);
	void operator=(const color &copyColor);
	~color();
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	unsigned int getRed()const;
	unsigned int getGreen()const;
	unsigned int getBlue()const;
	unsigned char getRed8bit()const;
	unsigned char getGreen8bit()const;
	unsigned char getBlue8bit()const;
	color operator-(const color &c);
	color operator+(const color &c);
	color operator*(float);//this is scalar multiply
	color average(const color &c, float inputWeight=.5);//wieght is the weight for the input color

private:
	unsigned int r, g, b;
};

