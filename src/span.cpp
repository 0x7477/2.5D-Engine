#include "span.hpp"
#include <algorithm>
Span::Span(Triangle* t, int x1_, int x2_)
:t{t}
{

    if(x1_ < x2_) 
    {
		x1 = x1_;
		x2 = x2_;
	} 
    else 
    {
		x1 = x2_;
		x2 = x1_;
	}
}

int Span::getLength()
{
    return x2-x1;
}


void Span::draw(int y)
{
	float factor = 0.0f;
	float factorStep = 1.0f / (float)getLength();

    	// draw each pixel in the span
	for(int x = std::max(x1,0); x < std::min(x2,t->screen->width); x++) 
    {
        t->screen->setColor(x,y,t->color);
		factor += factorStep;
	}
}