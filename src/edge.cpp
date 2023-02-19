#include "edge.hpp"
#include "span.hpp"
#include "game.hpp"

Edge::Edge(Triangle *t, const ScreenPoint &p1_, const ScreenPoint &p2_, const UVPoint &uv1_, const UVPoint &uv2_)
	: t{t}
{
	// p1 is the lower point
	if (p1_.y < p2_.y)
	{
		p1 = p1_;
		p2 = p2_;
		uv1 = uv1_;
		uv2 = uv2_;
	}
	else
	{
		p1 = p2_;
		p2 = p1_;
		uv1 = uv2_;
		uv2 = uv1_;
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
void Edge::drawSpans(const Edge &edge2)
{
	if (getLength() == 0)
		return;
	if (edge2.getLength() == 0)
		return;

	float factor1 = (float)(edge2.p1.y - p1.y) / getLength();
	float factorStep1 = 1.0f / getLength();

	float factor2 = 0;
	float factorStep2 = 1.0f / edge2.getLength();

	for (int y = edge2.p1.y; y <= edge2.p2.y; y++)
	{
		int x1 = p1.x + (int)(getWidth() * factor1);
		int x2 = edge2.p1.x + (int)(edge2.getWidth() * factor2);

		float z1 = p1.z + getDepth() * factor1;
		float z2 = edge2.p1.z + edge2.getDepth() * factor2;

		double uv1_u = uv1.u + (uv2.u - uv1.u) * factor1;
		double uv1_v = uv1.v + (uv2.v - uv1.v) * factor1;

		double uv2_u = edge2.uv1.u + (edge2.uv2.u - edge2.uv1.u) * factor2;
		double uv2_v = edge2.uv1.v + (edge2.uv2.v - edge2.uv1.v) * factor2;


		// create and draw span
		Span span(t, x1, z1, x2, z2, {uv1_u, uv1_v},{uv2_u, uv2_v});

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;

		// continue if out of bounds
		if (y < 0)
			continue;
		if (y >= t->screen->height - 1)
			continue;

		span.draw(y);
	}
}
