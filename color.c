#include "fdf.h"

if (redValue1 == redValue2)
{
	redDifference = 0
}
else
{
	redDifference = absoluteValue(redValue1 - redValue2) / widthOfGradient
}

if (redValue1 > redValue2)
{
	redDifference *= -1
}
///////////////////////////////////////////////////////////////////////////////////
for	(int i = 0; i < widthOfGradient; i++) {
	int r = round(redValue1 + (i * redDifference))
	// ...repeat for green and blue
	drawLine(i, r, g, b)
}
