#ifndef point

class Point {
private:
	int x;
	int y;
public:
	int getX(void);
	int getY(void);

	Point(int xx, int yy); 

	void setX(int xx);
	void setY(int yy);
};

int Point::getX(void){
	return x;
}

int Point::getY(void){
	return y;
}

void Point::setX(int xx) {
	x=xx;
}

void Point::setY(int yy) {
	y=yy;
}

Point::Point(int xx, int yy){
	x = xx;
	y=yy;
}

#endif // !point
