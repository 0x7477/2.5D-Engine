#include "triangle.hpp"

Triangle::Triangle(Screen* screen,Pixel* color, int x1, int y1, int x2, int y2, int x3, int y3)
    :edges{Edge(this, x1, y1, x2, y2),
		Edge(this, x2, y2, x3, y3),
		Edge(this, x3, y3, x1, y1)}, screen{screen}, color{*color}
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

