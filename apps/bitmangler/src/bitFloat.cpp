#include "bitFloat.h"

bitFloat::bitFloat (float v)
{
	currentValue.f = v;
}

bitFloat::bitFloat()
{
	currentValue.f = 0.0f;
}

void bitFloat::setValue (float v)
{
	currentValue.f = v;
}

float bitFloat::getValue ()
{
	return (currentValue.f);
}

String bitFloat::getBinaryString (floatint b, int d)
{
	String r;
	while (--d >= 0)
	{
		r << String::formatted (T("%d"), ((b >> d) & 1));
	}

	return (r);
}

String bitFloat::getFloatAsString ()
{
	floatint e,m;
	String str;

	if (currentValue.i & SIGN_FLT)
	{
		str << T("-:");
	}
	else
	{
		 str << T("+:");
	}

	currentValue.i &= ~SIGN_FLT;
	e = currentValue.i >> MANT_FLT;
	str << getBinaryString (e, BITS_FLT-1-MANT_FLT);
	str << T(":");

	m	= (currentValue.i & (((floatint)1 << MANT_FLT) - 1));

	str << getBinaryString(m, MANT_FLT);

	return (str);
}

floatint bitFloat::getLongValue ()
{
	return (currentValue.i);
}