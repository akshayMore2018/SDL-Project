#pragma once
#include <vector>
class Vector2
{
public:
	float x;
	float y;
	Vector2()
		:x(0.0f)
		, y(0.0f)
	{}
	explicit Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{}

	
	
};
class Math
{
private:
	static std::vector<Vector2>  plotLineLow(int x0, int y0, int x1, int y1)
	{
		std::vector<Vector2> result;
		int dx, dy , yi , D , y, x;
		dx = x1 - x0;
		dy = y1 - y0;
		yi = 1;
		if (dy < 0)
		{
			yi = -1;
			dy = -dy;
		}
		
		else
		{
			D = 2 * dy - dx;
			y = y0;
		}
			

		for (x = x0; x < x1; x++)
		{
			result.push_back(Vector2(x,y));
				if (D > 0)
				{
					y = y + yi;
					D = D - 2 * dx;
				}
				else
				{
					D = D + 2 * dy;
				}
		}
		return result;
	}

	static std::vector<Vector2>  plotLineHigh(int x0, int y0, int x1, int y1)
	{
		std::vector<Vector2> result;
		int dx, dy, xi, D, y, x;
		dx = x1 - x0;
		dy = y1 - y0;
		xi = 1;
		if (dx < 0)
		{
			xi = -1;
			dx = -dx;
		}
		else
		{
			D = 2 * dx - dy;
			x = x0;
		}
		for (y = y0; y < y1; y++)
		{
			result.push_back(Vector2(x, y));
			if (D > 0)
			{
				x = x + xi;
				D = D - 2 * dy;
			}
			else
			{
				D = D + 2 * dx;
			}
		}
		return result;
	}

public:
	static std::vector<Vector2> Bresenham(int x0, int y0, int x1, int y1)
	{
		if (abs(y1 - y0) < abs(x1 - x0))
		{
			if (x0 > x1)
				return plotLineLow(x1, y1, x0, y0);
			else
				return plotLineLow(x0, y0, x1, y1);		
		}
		else
		{
			if (y0 > y1)
				return plotLineHigh(x1, y1, x0, y0);
			else
				return plotLineHigh(x0, y0, x1, y1);
		}		
	}
};