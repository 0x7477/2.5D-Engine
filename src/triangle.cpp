#include "triangle.hpp"
#include <iostream>

Triangle::Triangle(Screen* screen,Pixel* color, ScreenPoint p1, ScreenPoint p2, ScreenPoint p3)
:edges{Edge(this, p1.x, p1.y, p2.x, p2.y),Edge(this, p2.x, p2.y, p3.x, p3.y),Edge(this, p3.x, p3.y, p1.x, p1.y)}, screen{screen}, color{*color}
{
    //lets get longest Edge
    if(edges[0].getLength() > edges[1].getLength())
        long_edge = (edges[0].getLength() > edges[2].getLength())?0:2;
    else
        long_edge = (edges[1].getLength() > edges[2].getLength())?1:2;

    short_edge1 = (long_edge + 1) % 3;
    short_edge2 = (long_edge + 2) % 3;
}

void Triangle::draw()
{
    edges[long_edge].drawSpans(edges[short_edge1]);
    edges[long_edge].drawSpans(edges[short_edge2]);
}

