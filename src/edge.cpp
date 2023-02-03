#include "edge.hpp"
#include "span.hpp"

Edge::Edge(Triangle* t,const ScreenPoint& p1_, const ScreenPoint& p2_)
:t{t}
{
	//p1 is the lower point
    if(p1_.y < p2_.y) 
	{
		p1 = p1_;
		p2 = p2_;
	} 
	else 
	{
		p1 = p2_;
		p2 = p1_;
	}
};

int Edge::getWidth() const
{
	return p2.x - p1.x;
}

int Edge::getLength() const
{
	return p2.y - p1.y;
}

float Edge::getDepth() const
{
	return p2.z - p1.z;
}
void Edge::drawSpans(const Edge& edge2)
{
	if(getLength() == 0)return;
	if(edge2.getLength() == 0)return;

	float factor1 = (float)(edge2.p1.y - p1.y) / getLength();
	float factorStep1 = 1.0f / getLength();

	float factor2 = 0;
	float factorStep2 = 1.0f / edge2.getLength();

	for(int y = edge2.p1.y; y < edge2.p2.y; y++) 
	{
		// create and draw span
		Span span(t, p1.x + (int)(getWidth() * factor1), p1.z + getDepth() * factor1,
		          edge2.p1.x + (int)(edge2.getWidth() * factor2), edge2.p1.z + edge2.getDepth() * factor2);

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;

		//continue if out of bounds
		if(y <0) continue;
		if(y >= t->screen->height-1) continue;

		span.draw(y);
	}

}
