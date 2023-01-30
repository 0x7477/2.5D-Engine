#include "span.hpp"
#include <algorithm>
Span::Span(Triangle* t, int x1_, float z1_, int x2_, float z2_)
:t{t}
{

    if(x1_ < x2_) 
    {
		x1 = x1_;
		depth1 = z1_;
		x2 = x2_;
		depth2 = z2_;
	} 
    else 
    {
		x1 = x2_;
		depth1 = z2_;
		x2 = x1_;
		depth2 = z1_;
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

	float depth_delta = depth2 - depth1;
    	// draw each pixel in the span
	for(int x = std::max(x1,0); x < std::min(x2,t->screen->width); x++) 
    {
		auto depth = depth1 + depth_delta * factor;
		factor += factorStep;
		if(t->screen->getDepth(x,y) < depth)
			continue;

        t->screen->setColor(x,y,t->color);
        t->screen->setDepth(x,y,depth);
	}
}