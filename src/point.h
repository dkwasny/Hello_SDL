#include <gl/GL.h>
#include <cstdlib>

class Point {
public:
	Point(float pX, float pY, float pR, float pG, float pB) {
		x = pX;
		y = pY;
		r = pR;
		g = pG;
		b = pB;
	}

	float getX() { return x; }
	float getY() { return y; }
	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }

	void setX(float pX) { x = pX; }
	void setY(float pY) { y = pY; }
	void setR(float pR) { r = pR; }
	void setG(float pG) { g = pG; }
	void setB(float pB) { b = pB; }

	void nudgePoint() {
		x = nudgeValue(x, positionNudgeAmount);
		y = nudgeValue(y, positionNudgeAmount);
	}

	void nudgeColor() {
		r = nudgeValue(r, colorNudgeAmount);
		g = nudgeValue(g, colorNudgeAmount);
		b = nudgeValue(b, colorNudgeAmount);
	}

	void draw() {
		glColor3f(r, g, b);
		glVertex2f(x, y);
	}

private:
	float x;
	float y;
	float r;
	float g;
	float b;
	const float positionNudgeAmount = 0.01f;
	const float colorNudgeAmount = 0.1f;

	float nudgeValue(float input, float nudgeAmount) {
		int shouldNudge = rand() % 3;
		float retVal = input;
		switch (shouldNudge) {
		case 0:
			// no nudge
			break;
		case 1:
			//positive nudge
			retVal += nudgeAmount;
			break;
		case 2:
			// negative nudge
			retVal -= nudgeAmount;
			break;
		}
		return retVal;
	}

};
