#include "edge.hpp"
#include "span.hpp"

Edge::Edge(Triangle* t,int x1_, int y1_, int x2_, int y2_)
:t{t}
{
    if(y1_ < y2_) 
	{
		x1 = x1_;
		y1 = y1_;
		x2 = x2_;
		y2 = y2_;
	} 
	else 
	{
		x1 = x2_;
		y1 = y2_;
		x2 = x1_;
		y2 = y1_;
	}
};

int Edge::getLength()
{
	return y2 - y1;
}

int Edge::getWidth()
{
	return x2 - x1;
}
void Edge::drawSpans(Edge edge2)
{
	if(getLength() == 0)return;
	if(edge2.getLength() == 0)return;

	float factor1 = (float)(edge2.y1 - y1) / getLength();
	float factorStep1 = 1.0f / getLength();

	float factor2 = 0;
	float factorStep2 = 1.0f / edge2.getLength();

	for(int y = edge2.y1; y < edge2.y2; y++) 
	{
		// create and draw span
		Span span(t, x1 + (int)(getWidth() * factor1),
		          edge2.x1 + (int)(edge2.getWidth() * factor2));

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;
		if(y <0) continue;
		if(y >= t->screen->height-1) continue;

		span.draw(y);
	}

}
