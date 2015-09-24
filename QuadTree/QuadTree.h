#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <list>


class QuadTree
{
	QuadTree *nw;
	QuadTree *ne;
	QuadTree *se;
	QuadTree *sw;

	point ul;
	point lr;

	std::list<polygon> polygons;

public:
	QuadTree(float x0, float x1, float y0, float y1);

	nw = NULL;
	ne = NULL;
	se = NULL;
	sw = NULL;

	ul.x = std::min(x0, x1);
	ul.y = std::max(y0, y1);
	lr.x = std::max(x0, x1);
	lr.y = std::min(y0, y1);

	~QuadTree();
};
#endif;
