#include "span.hpp"
#include <algorithm>
Span::Span(Triangle* t, int x1_, float z1_, int x2_, float z2_,const UVPoint& uv1_, const UVPoint& uv2_)
:t{t}
{
	//x is the leftmostr point
    if(x1_ < x2_) 
    {
		x1 = x1_;
		depth1 = z1_;
		uv1 = uv1_;
		x2 = x2_;
		depth2 = z2_;
		uv2 = uv2_;
	} 
    else 
    {
		x1 = x2_;
		depth1 = z2_;
		uv1 = uv2_;
		x2 = x1_;
		depth2 = z1_;
		uv2 = uv1_;
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

	double u_delta = uv2.u - uv1.u;
	double v_delta = uv2.v - uv1.v;

	// draw each pixel in the span
	for(int x = x1; x < x2; x++) 
    {
		auto depth = depth1 + depth_delta * factor;
		auto u = uv1.u + u_delta * factor;
		auto v = uv1.v + v_delta * factor;

		factor += factorStep;

		if(x < 0 || x >= (int)t->screen->width) continue;

		//skip if hidden
		if(t->screen->getDepth(x,y) < depth)
			continue;

		int sample_x = (int)(u * (t->texture->width-1));
		int sample_y = (int)(v * (t->texture->height-1));


		Pixel texture_sample = (*t->texture)(sample_x,sample_y);

		texture_sample.setBrightness(t->light_intensity);
 
        t->screen->setColor(x,y,texture_sample);
        t->screen->setDepth(x,y,depth);
	}
}