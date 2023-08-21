#pragma once
class Location
{
private:
	int Location_X;
	int Location_Y;
public:
	int getLocationX() const;
	int getLocationY() const;

	void setLocationX(const int LocX);
	void setLocationY(const int LocY);
};

