#include <src/TriangularPrism.h>
#include <stdio.h>

TriangularPrism::TriangularPrism(vector<Point2D*> points, float height,
		Texture* texture) {
	this->basePoints = points;
	this->height = height;
	this->texture = texture;

	int mult = 1;
	for (unsigned int i = 0, j = 0; j < 2; i++) {
		Point2D* p = basePoints[i];
		drawPoints.push_back(
				new Point3D(height / 2 * mult, p->getY(), p->getX()));

		if (i == 2)
			mult = -1, i = -1, j++;
	}

	top = new Triangle((*drawPoints[2]), (*drawPoints[0]), (*drawPoints[1]),
			this->texture);
	base = new Triangle((*drawPoints[3]), (*drawPoints[5]), (*drawPoints[4]),
			this->texture);

	//calculating angles and sides
	Point3D* p1 = drawPoints[0], *p2 = drawPoints[1], *p3 = drawPoints[2];
	float a, b, c, alpha, beta, omega;

	a = sqrt(
			pow(p1->getX() - p3->getX(), 2) + pow(p1->getY() - p3->getY(), 2)
					+ pow(p1->getZ() - p3->getZ(), 2));
	b = sqrt(
			pow(p2->getX() - p1->getX(), 2) + pow(p2->getY() - p1->getY(), 2)
					+ pow(p2->getZ() - p1->getZ(), 2));
	c = sqrt(
			pow(p3->getX() - p2->getX(), 2) + pow(p3->getY() - p2->getY(), 2)
					+ pow(p3->getZ() - p2->getZ(), 2));

	alpha = acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c));
	beta = acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c));
	omega = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));

	// saving right sides
	/*sides.push_back(
	 new Rectangle(Point3D(height / (-2), 0, 0),
	 Point3D(height / 2, b, 0), this->texture));

	 sides.push_back(
	 new Rectangle(Point3D(height / (-2), 0, 0),
	 Point3D(height / 2, a, 0), this->texture));

	 sides.push_back(
	 new Rectangle(Point3D(height / (-2), 0, 0),
	 Point3D(height / 2, c, 0), this->texture));*/

	for (unsigned int i = 0; i < 3; i++)
		sides.push_back(new Plane(20, this->texture));

	// saving base sides
	baseSides.push_back(a);
	baseSides.push_back(b);
	baseSides.push_back(c);

	// saving angles
	angles.push_back(radToDeg(alpha));
	angles.push_back(radToDeg(beta));
	angles.push_back(radToDeg(omega));

}

TriangularPrism::~TriangularPrism() {

}

void TriangularPrism::draw() {
	top->draw();
	base->draw();

	// side 1
	glPushMatrix();
	glRotatef(angles[0], 1, 0, 0);
	glScalef(height, 1, baseSides[1]);
	sides[0]->draw();
	glPopMatrix();

	// side 2
	glPushMatrix();
	glTranslatef(0, 0, baseSides[2] / (-2));
	glRotatef(angles[1] * (-1), 1, 0, 0);
	glScalef(height, 1, baseSides[0]);
	sides[1]->draw();
	glPopMatrix();

	// side 3
	glPushMatrix();
	glTranslatef(0, baseSides[0] / (-2), 0);
	glRotatef(angles[1] * (-2), 1, 0, 0);
	glScalef(height, 1, baseSides[2]);
	sides[2]->draw();
	glPopMatrix();
}
