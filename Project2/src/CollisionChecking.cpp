///////////////////////////////////////
// COMP/ELEC/MECH 450/550
// Project 2
// Authors: FILL ME OUT!!
// Date: FILL ME OUT!!
//////////////////////////////////////

#include "CollisionChecking.h"
#include <vector>
#include <math.h>
// Intersect the point (x,y) with the set of rectangles. If the point lies
// outside of all obstacles, return true.
bool isValidPoint(double x, double y, const std::vector<Rectangle>& obstacles)
{
    // TODO: IMPLEMENT ME!!
    for(auto rec : obstacles){
    	if(x>=rec.x && x<=rec.x+rec.width && y>=rec.y && y<=rec.y+rec.height) 
    		return false;
    }
    return true;
}

// Intersect a circle with center (x,y) and given radius with the set of
// rectangles. If the circle lies outside of all obstacles, return true.
bool isValidCircle(double x, double y, double radius, const std::vector<Rectangle>& obstacles)
{
    // TODO: IMPLEMENT ME!!
    for(auto rec : obstacles){
    	if(rec.x-radius <= x && rec.x+rec.width+radius >= x && y >= rec.y && y <= rec.y+rec.height) return false;
    	if(rec.y-radius <= y && rec.y+rec.height+radius >= y && rec.x <= x && x <= rec.x+rec.width) return false;
    	double dx = rec.x - x, dy = rec.y - y;
    	if(dx*dx+dy*dy<=radius*radius) return false; 
    	dx += rec.width;
		if(dx*dx+dy*dy<=radius*radius) return false;		
		dy += rec.height;
    	if(dx*dx+dy*dy<=radius*radius) return false;
    	dx -= rec.width;
    	if(dx*dx+dy*dy<=radius*radius) return false;
    }
    return true;
}

// Intersect a square with center at (x,y), orientation theta, and the given
// side length with the set of rectangles. If the square lies outside of all
// obstacles, return true.
bool isValidSquare(double x, double y, double theta, double sideLength, const std::vector<Rectangle>& obstacles)
{
    // TODO: IMPLEMENT ME!!
    for(auto rec : obstacles){
    	if(x>=rec.x && x<=rec.x+rec.width && y>=rec.y && y<=rec.y+rec.height) 
    		return false;
    }
    bool isIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
	std::vector<double> v1;  				//Square x
	std::vector<double> v2;  				//Square y

	double di = sqrt(2)*sideLength/2.0;

	v1.push_back(di*cos(theta+M_PI/4.0)+x);
	v2.push_back(di*sin(theta+M_PI/4.0)+y);

	v1.push_back(di*cos(theta+M_PI/4.0+M_PI/2.0)+x);
	v2.push_back(di*sin(theta+M_PI/4.0+M_PI/2.0)+y);

	v1.push_back(di*cos(theta+M_PI/4.0+M_PI)+x);
	v2.push_back(di*sin(theta+M_PI/4.0+M_PI)+y);

	v1.push_back(di*cos(theta-M_PI/4.0)+x);
	v2.push_back(di*sin(theta-M_PI/4.0)+y);

	for (auto rec : obstacles)	
	{
        std::vector<double> v3;  				//Object x
		std::vector<double> v4;  				//object y;

		v3.push_back(rec.x);
		v4.push_back(rec.y);

		v3.push_back(rec.x+rec.width);
		v4.push_back(rec.y);

		v3.push_back(rec.x+rec.width);
		v4.push_back(rec.y+rec.height);

		v3.push_back(rec.x);
		v4.push_back(rec.y+rec.height);

	    double pp1x, pp2x, pp3x, pp4x, pp1y, pp2y, pp3y, pp4y;	
		for (int i = 0; i < 4; ++i)
		{
			if(i==3){
				pp1x = v1[3];
				pp1y = v2[3];
				pp2x = v1[0];
				pp2y = v2[0];
			}else{
				pp1x = v1[i];
				pp1y = v2[i];
				pp2x = v1[i+1];
				pp2y = v2[i+1];
			}
			for (int j = 0; j < 4; ++j)
			{
				if(j==3){
					pp3x = v3[3];
					pp3y = v4[3];
					pp4x = v3[0];
					pp4y = v4[0];
				}else{
					pp3x = v3[j];
					pp3y = v4[j];
					pp4x = v3[j+1];
					pp4y = v4[j+1];
				}
				if(isIntersect(pp1x, pp1y, pp2x, pp2y, pp3x, pp3y, pp4x, pp4y))
				{
					v1.clear(); v2.clear(); v3.clear(); v4.clear();
					return false;
				}
			}
		}
		v3.clear(); v4.clear();
	}
	v1.clear(); v2.clear();
    return true;
}

bool isIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	if(x1==x3&&y1==y3) return true;
	if(x2==x4&&y2==y4) return true;
	if(x1==x4&&y1==y4) return true;
	if(x2==x3&&y2==y3) return true;
	double dx1 = x2 - x1;
	double dy1 = y2 - y1;
	double dx2 = x4 - x3;
	double dy2 = y4 - y3;
	double s,t;
	if(dy1==0&&dy2==0){
	    if(y1!=y3) return false;
	    if(((x1<x3)&&(x3<x2))||((x1<x4)&&(x4<x2))) return true;
	    return false;
	}
	if(dx1==0&&dx2==0){
	    if(x1!=x3) return false;
	    if(((y1<y3)&&(y3<y2))||((y1<y4)&&(y4<y2))) return true;
	    return false;
	}
	if( dx1/dy1==dx2/dy2 ) {
	    if( ((x3-x1)/(y3-y1)) == ((x4-x1)/(y4-y1)) || ((x3-x2)/(y3-y2)) == ((x4-x2)/(y4-y2))) return true;
	    return false;
	}
	s = (-dy1*(x1-x3)+dx1*(y1-y3))/(-dx2*dy1+dx1*dy2);
	t = ( dx2*(y1-y3)-dy2*(x1-x3))/(-dx2*dy1+dx1*dy2);
	if(s>=0&&s<=1&&t>=0&&t<=1) return true;
	return false;
}

// Add any custom debug / development code here. This code will be executed
// instead of the statistics checker (Project2.cpp). Any code submitted here
// MUST compile, but will not be graded.
void debugMode(const std::vector<Robot>& /*robots*/, const std::vector<Rectangle>& /*obstacles*/, const std::vector<bool>& /*valid*/)
{
}
