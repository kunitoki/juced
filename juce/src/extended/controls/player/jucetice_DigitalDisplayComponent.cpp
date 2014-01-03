/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2009 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU General Public License, as published by the Free Software Foundation;
 either version 2 of the License, or (at your option) any later version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================

	original author: Michel Wassink (See copyright below for more details)
	juce version:    Arlen Albert Keshabyan (ptomaine)
    tweaker:         Asnaghi Lucio (kRAkEn/gORe)

 ==============================================================================
*/

#include "../../../core/juce_StandardHeader.h"

#if 0

BEGIN_JUCE_NAMESPACE

#include "jucetice_DigitalDisplayComponent.h"

//==============================================================================
class DigitalDisplayComponentUtils
{
public:

    static void bezier (double u, const double *a, const double *b, double x4, double y4, double &z, double &s)
    {
	    double x, y;
	    double dx4, dy4;
	    double dx, dy;

	    x = a[0] + u * (a[1] + u * (a[2] + u * a[3]));
	    y = b[0] + u * (b[1] + u * (b[2] + u * b[3]));
	    dx4 = x - x4;
	    dy4 = y - y4;
	    dx = a[1] + u * (a[2] + a[2] + u * 3 * a[3]);
	    dy = b[1] + u * (b[2] + b[2] + u * 3 * b[3]);
	    z = dx * dx4 + dy * dy4;
	    s = dx4 * dx4 + dy4 * dy4;
    }

    static double distanceError (const double *x, const double *y, const double *Rawdata, int n)
    {
	    int i;
	    double a[4];
	    double b[4];
	    double u, u1, u2;
	    double z, z1, z2, s, s1;
	    double temp;
	    double totalerror;
	    double stepsize;
	    double x4, y4;

	    totalerror = 0;
	    a[3] = (x[3] - x[0] + 3 * (x[1] - x[2])) / 8;
	    b[3] = (y[3] - y[0] + 3 * (y[1] - y[2])) / 8;
	    a[2] = (x[3] + x[0] - x[1] - x[2]) * 3 / 8;
	    b[2] = (y[3] + y[0] - y[1] - y[2]) * 3 / 8;
	    a[1] = (x[3] - x[0]) / 2 - a[3];
	    b[1] = (y[3] - y[0]) / 2 - b[3];
	    a[0] = (x[3] + x[0]) / 2 - a[2];
	    b[0] = (y[3] + y[0]) / 2 - b[2];

	    stepsize = 2.0 / (n);
	    s = u1 = z1 = s1 = 0;
	    for (i = 2; i <= n - 3; i += 2)
	    {
		    x4 = Rawdata[i];
		    y4 = Rawdata[i+1];
		    for (u = -1; u <= 1.01; u += stepsize)
		    {
			    bezier(u, a, b, x4, y4, z, s);
			    if (s == 0)
			    {
				    u1 = u;
				    z1 = z;
				    s1 = s;
				    break;
			    }

			    if (u == -1)
			    {
				    u1 = u;
				    z1 = z;
				    s1 = s;
			    }

			    if (s < s1)
			    {
				    u1 = u;
				    z1 = z;
				    s1 = s;
			    }
		    }
		    if (s1 != 0)
		    {
			    u = u1 + stepsize;
			    if (u > 1)
				    u = 1 - stepsize;

			    bezier(u, a, b, x4, y4, z, s);

			    while (s != 0 && z != 0)
			    {
				    u2 = u;
				    z2 = z;
				    temp = z2-z1;

				    if (temp != 0)
					    u = (z2 * u1-z1*u2)/temp;
				    else
					    u = (u1 + u2)/2;

				    if (u > 1)
					    u = 1;
				    else
					    if (u < -1)
						    u = -1;

				    if (fabs(u-u2) < 0.001)
					    break;

				    u1 = u2;
				    z1 = z2;

				    bezier(u, a, b, x4, y4, z, s);
			    }
		    }

		    totalerror += s;
	    }

	    return totalerror;
    }

    static void calculateBezier (const double *Rawdata, int n, double *Control)
    {
	    double	x[4];
	    double	y[4];
	    double	e1, e2, e3;
	    int		Retry;
	    double	x1a, x2a, y1a, y2a;

	    x[0] = Rawdata[0];
	    y[0] = Rawdata[1];

	    x[1] = Rawdata[2];
	    y[1] = Rawdata[3];

	    x[2] = Rawdata[n-4];
	    y[2] = Rawdata[n-3];

	    x[3] = Rawdata[n-2];
	    y[3] = Rawdata[n-1];

	    // seed with linear interpolation...
	    x[1] += x[1] - x[0];
	    y[1] += y[1] - y[0];
	    x[2] += x[2] - x[3];
	    y[2] += y[2] - y[3];

	    e1 = distanceError(x, y, Rawdata, n);

	    for (Retry = 1; Retry <= 2; Retry++)
	    {
		    e3 = 0.5;
		    x1a = x[1];
		    while (fabs(e3) >= 0.01)
		    {
			    x[1] += (x[1] - x[0]) * e3;
			    e2 = distanceError(x, y, Rawdata, n);

			    if (e2 == e1)
				    break;

			    if (e2 > e1)
			    {
				    x[1] = x1a;
				    e3 /= -3;
			    }
			    else
			    {
				    e1 = e2;
				    x1a = x[1];
			    }
		    }

		    e3 = 0.5;
		    y1a = y[1];

		    while (fabs(e3) >= 0.01)
		    {
			    y[1] += (y[1] - y[0]) * e3;
			    e2 = distanceError(x, y, Rawdata, n);

			    if (e2 == e1)
				    break;

			    if (e2 > e1)
			    {
				    y[1] = y1a;
				    e3 /= -3;
			    }
			    else
			    {
				    e1 = e2;
				    y1a = y[1];
			    }
		    }

		    e3 = 0.5;
		    x2a = x[2];

		    while (fabs(e3) >= 0.01)
		    {
			    x[2] += (x[2] - x[3]) * e3;
			    e2 = distanceError(x, y, Rawdata, n);

			    if (e2 == e1)
				    break;

			    if (e2 > e1)
			    {
				    x[2] = x2a;
				    e3 /= -3;
			    }
			    else
			    {
				    e1 = e2;
				    x2a = x[2];
			    }
		    }

		    e3 = 0.5;
		    y2a = y[2];

		    while (fabs(e3) >= 0.01)
		    {
			    y[2] += (y[2] - y[3]) * e3;
			    e2 = distanceError(x, y, Rawdata, n);
			    if (e2 == e1)
				    break;

			    if (e2 > e1)
			    {
				    y[2] = y2a;
				    e3 /= -3;
			    }
			    else
			    {
				    e1 = e2;
				    y2a = y[2];
			    }
		    }
	    } // for

	    Control[0] = x[1];
	    Control[1] = y[1];
	    Control[2] = x[2];
	    Control[3] = y[2];
    }
};

// Segment numbering:
// -----          13		 -----          0
//|\ | /|      8  0  12		|     |      1     2
//| \|/ |        1 2		|     |
// -- --   ==    6 7	     -----   ==     3
//| /|\ |        3 4	    |     |
//|/ | \|      9  5  11		|     |      4     5
// -----          10	     -----          6

#define PT_CLOSEFIGURE      0x01
#define PT_LINETO           0x02
#define PT_BEZIERTO         0x04
#define PT_MOVETO           0x06

#define MAXSEGCHAR7		    12		// Number of supported 7 segment characters
#define MAXSEGCHAR14	    45		// Number of supported 14 segment characters
#define MAXSEGSEMCOL	    2		// Number of supported 3 segment characters
#define NORM_DIGIHEIGHT	    83		// All characters must have this height

// please uncomment the following line if you want nicer scrolling
// and all characters get same width
//#define _WIDE_SEMICOLON

//==============================================================================
// For 14 segments display...
//									   SP		0		1		2		3		4		5		6
int16 CHAR_SEGM14[MAXSEGCHAR14]  = {0x0000, 0x3F00, 0x1800, 0x36C0, 0x3CC0, 0x19C0, 0x2DC0, 0x2FC0,
//		7		8		9		-		A		B		C		D		E		F		G		H
   0x3800, 0x3FC0, 0x3DC0, 0x00C0, 0x3BC0, 0x3CA1, 0x2700, 0x3C21, 0x27C0, 0x23C0, 0x2F80, 0x1BC0,
//		I		J		K		L		M		N		O		P		Q		R		S		T
   0x2421, 0x1E00, 0x0354, 0x0700, 0x1B06, 0x1B12, 0x3F00, 0x33C0, 0x3F10, 0x33D0, 0x2DC0, 0x2021,
//		U		V		W		X		Y		Z		*		+		(		)	Back/		/
   0x1F00, 0x030C, 0x1B18, 0x001E, 0x11E0, 0x240C, 0x00FF, 0x00E1, 0x0014, 0x000A, 0x0012, 0x000C,
//		'
   0x0001 };
// straight style
Point  PtSeg14N0[5]	 = {Point(20, 13), Point(20, 36), Point(24, 40), Point(28, 36), Point(28, 13)};
Point  PtSeg14N1[4]	 = {Point(5, 5), Point(15, 35), Point(20, 37), Point(18, 25)};
Point  PtSeg14N6[6]	 = {Point(6, 41), Point(14, 45), Point(18, 45), Point(22, 41), Point(18, 37), Point(14, 37)};
Point  PtSeg14N8[4]	 = {Point(4, 7), Point(4, 40), Point(11, 36), Point(11, 26)};
Point PtSeg14N13[4]  = {Point(6, 4), Point(11, 11), Point(37, 11), Point(42, 4)};
int8   TpSeg14N0[5]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   TpSeg14N1[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   TpSeg14N6[6]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   TpSeg14N8[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8  TpSeg14N13[4]  = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};

//==============================================================================
// smooth style PT_BEZIERTO
Point  PtSeg14N0S[13] = {Point(20, 12), Point(20, 25), Point(22, 36), Point(23, 39), Point(24, 40),
						Point(25, 39), Point(26, 36), Point(28, 25), Point(28, 12), Point(26, 10),
						Point(24, 9), Point(22, 10), Point(20, 12)};
Point  PtSeg14N1S[10] = {Point(10, 10), Point(10, 13), Point(11, 20), Point(13, 28), Point(21, 38),
						Point(21, 37), Point(19, 26), Point(15, 16), Point(11, 10), Point(10, 10)};
Point   PtSeg14N6S[6] = {Point(8, 41), Point(12, 45), Point(16, 45), Point(23, 41), Point(16, 37),
						Point(12, 37)};
Point  PtSeg14N8S[10] = {Point(4, 7), Point(4, 39), Point(5, 40), Point(6, 40), Point(9, 37),
						Point(11, 33), Point(11, 25), Point(9, 14), Point(5, 6), Point(4, 7)};
Point PtSeg14N13S[17] = {Point(8, 4), Point(7, 5), Point(7, 6), Point(9, 8), Point(12, 9),
						Point(14, 11), Point(19, 11), Point(21, 9), Point(24, 7), Point(27, 9),
						Point(29, 11), Point(34, 11), Point(36, 9), Point(39, 8), Point(41, 6),
						Point(41, 5), Point(40, 4)};
int8   TpSeg14N0S[13] = {PT_MOVETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_BEZIERTO, PT_BEZIERTO, PT_LINETO, PT_LINETO, PT_BEZIERTO,
						PT_BEZIERTO, PT_BEZIERTO, PT_LINETO};
int8   TpSeg14N1S[10] = {PT_MOVETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO,
						PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO};
int8    TpSeg14N6S[6] = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO,
						PT_LINETO};
int8   TpSeg14N8S[10] = {PT_MOVETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_BEZIERTO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO};
int8  TpSeg14N13S[17] = {PT_MOVETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_LINETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_LINETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_BEZIERTO, PT_LINETO};

//==============================================================================
// For 7 segments display...
//									 SP		0	  1		2	  3		4	  5
int8 CHAR_SEGM7[MAXSEGCHAR7]    = {0x00, 0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B,
// 	  6		7	  8		9	  -
   0x7B, 0x25, 0x7F, 0x6F, 0x08};
// straight style
Point PtSeg7N0[4]	 = {Point(5, 4), Point(12, 11), Point(36, 11), Point(43, 4)};
Point PtSeg7N1[4]	 = {Point(4, 6), Point(4, 40), Point(11, 36), Point(11, 13)};
Point PtSeg7N3[6]	 = {Point(6, 41), Point(14, 45), Point(34, 45), Point(42, 41), Point(34, 37),
						Point(14, 37)}; // 3
int8   TpSeg7N0[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   TpSeg7N1[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   TpSeg7N3[6]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO,
						PT_LINETO};

//==============================================================================
// smooth style PT_BEZIERTO
Point  PtSeg7N0S[7]	 = {Point(6, 4), Point(5, 5), Point(5, 6), Point(8, 9), Point(12, 11),
						Point(36, 11), Point(39, 4)};
Point  PtSeg7N1S[7]	 = {Point(4, 9), Point(4, 39), Point(6, 40), Point(7, 40), Point(9, 38),
						Point(11, 36), Point(11, 12)};
Point PtSeg7N2S[10]  = {Point(37, 36), Point(39, 38), Point(41, 40), Point(42, 40), Point(44, 39),
						Point(44, 6), Point(42, 4), Point(41, 4), Point(39, 8), Point(37, 12)};
Point  PtSeg7N3S[6]	 = {Point(8, 41), Point(12, 45), Point(36, 45), Point(40, 41), Point(36, 37),
						Point(12, 37)};
int8   TpSeg7N0S[7]	 = {PT_MOVETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO,
						PT_LINETO, PT_LINETO};
int8   TpSeg7N1S[7]	 = {PT_MOVETO, PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO,
						PT_LINETO, PT_LINETO};
int8  TpSeg7N2S[10]  = {PT_MOVETO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO, PT_LINETO,
						PT_LINETO, PT_BEZIERTO, PT_BEZIERTO, PT_BEZIERTO, PT_LINETO};
int8   TpSeg7N3S[6]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO, PT_LINETO,
						PT_LINETO};

// For 3 segments semicoloncombi display...
//									  .		:
int8 CHAR_SEMCOL[MAXSEGSEMCOL]  = {0x04, 0x03};

#ifdef _WIDE_SEMICOLON
	// for wide semicolon character space
	Point PtSegScN0[4]	 = {Point(19, 23), Point(19, 32), Point(32, 32), Point(32, 23)};
	Point PtSegScN1[4]	 = {Point(19, 50), Point(19, 59), Point(32, 59), Point(32, 50)};
	Point PtSegScN2[4]	 = {Point(19, 68), Point(19, 77), Point(32, 77), Point(32, 68)};
#else
	// small semicolon character space
	Point PtSegScN0[4]	 = {Point(4, 23), Point(4, 32), Point(13, 32), Point(13, 23)};
	Point PtSegScN1[4]	 = {Point(4, 50), Point(4, 59), Point(13, 59), Point(13, 50)};
	Point PtSegScN2[4]	 = {Point(4, 68), Point(4, 77), Point(13, 77), Point(13, 68)};
#endif
int8   	  TpSegScN0[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   	  TpSegScN1[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};
int8   	  TpSegScN2[4]	 = {PT_MOVETO, PT_LINETO, PT_LINETO, PT_LINETO};


//==============================================================================
// Functions for mirroring points...
Point pointMirror(const Point &P, const Point &M)
{
	return Point(P.getX() + 2 * (M.getX() - P.getX()), P.getY() + 2 * (M.getY() - P.getY()));
}

Point lineMirrorX(const Point &P, int X)
{
	return Point(P.getX() + 2 * (X - P.getX()), P.getY());
}

Point lineMirrorY(const Point &P, int Y)
{
	return Point(P.getX(), P.getY() + 2 * (Y - P.getY()));
}

//==============================================================================
// A simple Rectangle class with double precision for accurate drawing.
class DRectangle
{
public:

	void setRect(double x1, double y1, double x2, double y2)
	{
		left = x1; top = y1; right = x2; bottom = y2;
	}

	double getWidth() const
	{
		return right - left;
	}

	double getHeight() const
	{
		return bottom - top;
	}

	void clear()
	{
		left = top = right = bottom = 0.0;
	}

	double left, top, right, bottom;
};

//==============================================================================
class CDSegment
{
public:

	CDSegment()
	  : m_paPoints (0),
	    m_paTypes (0),
	    m_nCount (0)
	{
	}
	
/*
	CDSegment (const CDSegment& Segment)
	{
	    m_nCount = Segment.m_nCount;
	    m_paPoints = new Point[m_nCount];
	    m_paTypes = new int8[m_nCount];

	    if (m_paPoints != 0 && m_paTypes != 0)
	    {
		    memcpy (m_paPoints, Segment.m_paPoints, m_nCount * sizeof(Point));
		    memcpy (m_paTypes, Segment.m_paTypes, m_nCount * sizeof(int8));
	    }
	}
*/
	
	~CDSegment()
	{
    	freeSegment();
	}

	void defPoints (const Point* lpaPoints, const int8* lpaTypes, int nCount)
	{
	    freeSegment();

	    m_paPoints = new Point[nCount];
	    m_paTypes = new int8[nCount];
	    m_nCount = nCount;

	    if (m_paPoints != 0 && m_paTypes != 0)
	    {
		    memcpy (m_paPoints, lpaPoints, m_nCount * sizeof(Point));
		    memcpy (m_paTypes, lpaTypes, m_nCount * sizeof(int8));
	    }
    }
	
	void draw (Path &path, const DRectangle &DrawPlace, int iWidth)
    {
	    int i, nBez,b;
	    Point * paPoints;
	    double daContr[4];
	    double *pBezPts;
	    double dRelWidth, dRelHeight;

	    paPoints = new Point[m_nCount];

	    if (paPoints == NULL)
		    return;

	    dRelWidth = DrawPlace.getWidth() / iWidth;
	    dRelHeight = DrawPlace.getHeight() / NORM_DIGIHEIGHT;

	    for (i = 0; i < m_nCount; i++)
	    {
		    if (m_paTypes[i] != PT_BEZIERTO)
		    {
			    paPoints[i] = Point(int(DrawPlace.left + dRelWidth	 * m_paPoints[i].getX() + 0.5),
								     int(DrawPlace.top  + dRelHeight * m_paPoints[i].getY() + 0.5));
		    }
	    }

	    for (i = 0; i < m_nCount; i++)
	    {
		    if (m_paTypes[i] == PT_MOVETO)
		    {
			    path.startNewSubPath(paPoints[i].getX(), paPoints[i].getY());
		    }
		    else
			    if (m_paTypes[i] == PT_LINETO)
			    {
				    path.lineTo(paPoints[i].getX(), paPoints[i].getY());
			    }
			    else
				    if (m_paTypes[i] == PT_BEZIERTO)
				    {
					    // Look for the first non-bezier point(This is the EndPoint)...
					    nBez = 0;

					    do
					    {
						    nBez++;
					    } while (m_paTypes[i+nBez] == PT_BEZIERTO);

					    pBezPts = new double[2*(nBez+2)];

					    for (b = 0; b < (nBez+2)*2; b += 2)
					    {
						    pBezPts[b  ] = DrawPlace.left + dRelWidth	* m_paPoints[i-1+b/2].getX();
						    pBezPts[b+1] = DrawPlace.top  + dRelHeight	* m_paPoints[i-1+b/2].getY();
					    }
					    DigitalDisplayComponentUtils::calculateBezier (pBezPts, 2*(nBez+2), daContr);
					    delete[] pBezPts;

					    paPoints[i  ].setXY(float(daContr[0] + 0.5), float(daContr[1] + 0.5));
					    paPoints[i+1].setXY(float(daContr[2] + 0.5), float(daContr[3] + 0.5));
					    paPoints[i+2]	= paPoints[i+nBez];

					    path.cubicTo (paPoints[i].getX(), paPoints[i].getY(),
									  paPoints[i + 1].getX(), paPoints[i + 1].getY(),
									  paPoints[i + 2].getX(), paPoints[i + 2].getY());
					    i += nBez;
				    }
	    } // for

	    delete[] paPoints;
    }

	void freeSegment ()
    {
	    delete[] m_paPoints;
	    delete[] m_paTypes;
    }

/*
	CDSegment operator=(const CDSegment &Segment)
    {
	    Point *pNewPoints;
	    int8 * pNewTypes;

	    m_nCount = Segment.m_nCount;

	    pNewPoints = new Point[m_nCount];
	    pNewTypes = new int8[m_nCount];

	    memcpy (pNewPoints, Segment.m_paPoints, m_nCount * sizeof(Point));
	    memcpy (pNewTypes, Segment.m_paTypes, m_nCount * sizeof(int8));

	    freeSegment();			// Get rid of old stuff

	    m_paPoints = pNewPoints;
	    m_paTypes = pNewTypes;

	    return *this;
    }
*/

public:

	Point		*m_paPoints;			// array with point
	int8		*m_paTypes;			// array with connecting info for point
	int			m_nCount;			// number of points
};


//==============================================================================
class CDigiChar
{
public:

	CDigiChar ()
	  : m_Width (49),
	    m_wSegmData (0x0000),
	    m_NSegments (0),
	    m_bNoOff (false)
    {
    }

/*	
	CDigiChar (const CDigiChar& DigiChar)
	{
	    m_NSegments		  = DigiChar.m_NSegments;
	    m_OffColor		  = DigiChar.m_OffColor;
	    m_OnColor		  = DigiChar.m_OnColor;
	    m_SegmentArray    = DigiChar.m_SegmentArray;
	    m_Width			  = DigiChar.m_Width;
	    m_wSegmData		  = DigiChar.m_wSegmData;
	    m_bNoOff	      = DigiChar.m_bNoOff;
    }
*/
	
	virtual ~CDigiChar()
    {
    }

	virtual void setElementData (int16 wSegmData, int iDispStyle)
	{
	    m_wSegmData = wSegmData;
	    m_bNoOff = (iDispStyle & DigitalDisplayComponent::DS_NO_OFF) > 0;
    }

	void draw (Graphics *pDC, const DRectangle &DrawPlace, Colour OffColour, Colour OnColour,
	           Brush &OffBrush, Brush &OnBrush, bool makeStroke)
    {
	    int16 SegMask;
	    int iSeg;

	    SegMask = 1;
	    int l_iSize = m_SegmentArray.size();

	    for (iSeg = 0; iSeg < l_iSize; iSeg++)
	    {
		    if (m_wSegmData & SegMask)
		    {
			    pDC->setColour (OnColour);
			    pDC->setBrush (&OnBrush);
		    }
		    else
		    {
			    pDC->setColour (OffColour);
			    pDC->setBrush (&OffBrush);
		    }

		    if (!m_bNoOff || (m_wSegmData & SegMask))
		    {
			    Path path;
			    m_SegmentArray.getUnchecked (iSeg)->draw(path, DrawPlace, m_Width);
			    path.closeSubPath();

			    pDC->fillPath(path);

			    if(makeStroke)
				    pDC->strokePath(path, PathStrokeType(1.f));
		    }

		    SegMask <<= 1;
	    }
    }
	                      
	void setColor (Colour OffColor, Colour OnColor)
	{
	    m_OffColor = OffColor;
	    m_OnColor = OnColor;
	}
	
	int getNormWidth () const
	{
	    return m_Width;
    }

/*
	CDigiChar operator= (const CDigiChar &DigiChar)
    {
	    m_NSegments		  = DigiChar.m_NSegments;
	    m_OffColor		  = DigiChar.m_OffColor;
	    m_OnColor		  = DigiChar.m_OnColor;
	    m_SegmentArray    = DigiChar.m_SegmentArray;
	    m_Width			  = DigiChar.m_Width;
	    m_wSegmData		  = DigiChar.m_wSegmData;
	    m_bNoOff		  = DigiChar.m_bNoOff;

	    return *this;
    }
*/

	Colour getColor(void) const
	{
		return m_OnColor;
	}

protected:

	int				      m_Width;        // Width of character
	int16			      m_wSegmData;    // segments to highlight (binairy encoded)
	OwnedArray<CDSegment> m_SegmentArray; // Character is array of segments
	int				      m_NSegments;	 // Number of segments
	Colour			      m_OffColor;     // Color of segment when off
	Colour			      m_OnColor;      // Color of segment when on
	bool			      m_bNoOff;       // Do not draw segments that are off
};

//==============================================================================
class CDigiColonDotChar : public CDigiChar
{
public:
	CDigiColonDotChar();
	void setElementData(int16 wSegmData, int iDispStyle);
};

CDigiColonDotChar::CDigiColonDotChar()
{
#ifdef _WIDE_SEMICOLON
	m_Width		= 49;
#else
	m_Width		= 18;
#endif
	m_NSegments = 3;
}

void CDigiColonDotChar::setElementData(int16 wSegmData, int iDispStyle)
{
	int i;
	CDSegment* DSegment;
	Point* lpSegPoints	= NULL;
	int8*  lpType	= NULL;
	int nCount = 0;

	m_SegmentArray.clear(true);

	for (i = 0; i < m_NSegments; i++)
	{
		// Find data for segment in correct style...
		switch(i)
		{
			case 0:lpSegPoints = PtSegScN0;
				lpType = TpSegScN0;
				nCount = 4;

				break;

			case 1:
				lpSegPoints = PtSegScN1;
				lpType = TpSegScN1;
				nCount = 4;

				break;

			case 2:
				lpSegPoints = PtSegScN2;
				lpType = TpSegScN2;
				nCount = 4;

				break;
		}

		// Copy data to segment array...
		DSegment = new CDSegment();
		DSegment->defPoints (lpSegPoints, lpType, nCount);
		m_SegmentArray.add (DSegment);
	}

	CDigiChar::setElementData(wSegmData, iDispStyle);
}

//==============================================================================
class CDigi7Segment : public CDigiChar
{
public:
	CDigi7Segment();
	void setElementData(int16 wSegmData, int iDispStyle);
};

CDigi7Segment::CDigi7Segment()
{
	m_Width		= 49;
	m_NSegments = 7;
}

void CDigi7Segment::setElementData(int16 wSegmData, int iDispStyle)
{
	int i, p;
	CDSegment* TmpSegm;
	Point* lpTmpSegPoints = NULL;
	Point* lpSegPoints	= NULL;
	int8*  lpType		= NULL;
	int nCount	=0;

	m_SegmentArray.clear(true);
	for (i = 0; i < m_NSegments; i++)
	{
		// Find data for segment in correct style...
		switch(i)
		{
			case 0:
			case 6: if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg7N0S;
						lpType = TpSeg7N0S;
						nCount = 7;
					}
					else
					{
						lpSegPoints = PtSeg7N0;
						lpType = TpSeg7N0;
						nCount = 4;
					}

					break;

			case 1:
			case 4:if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg7N1S;
						lpType = TpSeg7N1S;
						nCount = 7;
					}
					else
					{
						lpSegPoints = PtSeg7N1;
						lpType = TpSeg7N1;
						nCount = 4;
					}

					break;

			case 2:
			case 5: if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg7N2S;
						lpType = TpSeg7N2S;
						nCount = 10;
					}
					else
					{
						lpSegPoints = PtSeg7N1;
						lpType = TpSeg7N1;
						nCount = 4;
					}

					break;

			case 3: if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg7N3S;
						lpType = TpSeg7N3S;
						nCount = 6;
					}
					else
					{
						lpSegPoints = PtSeg7N3;
						lpType = TpSeg7N3;
						nCount = 6;
					}

					break;
		}
		// For nondefined segments use mirroring...
		switch(i)
		{
		case 6: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;

		case 2: if (!(iDispStyle & DigitalDisplayComponent::DS_SMOOTH))
				{
					lpTmpSegPoints = new Point[nCount];
					for (p = 0; p < nCount; p++)
						lpTmpSegPoints[p] = lineMirrorX(lpSegPoints[p], (m_Width-1)/2);
				}

				break;

		case 4: lpTmpSegPoints = new Point[nCount];
				for (p = 0; p < nCount; p++)
					lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;

		case 5: lpTmpSegPoints = new Point[nCount];
				for (p = 0; p < nCount; p++)
				{
					if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
						lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);
					else
						lpTmpSegPoints[p] = pointMirror(lpSegPoints[p], Point((m_Width-1)/2, 41));
				}

				break;
		}

		// Copy data to segment array...
        TmpSegm = new CDSegment ();

		if (lpTmpSegPoints == NULL)
		{
			// point is an original.
			TmpSegm->defPoints(lpSegPoints, lpType, nCount);
		}
		else
		{
			// point is mirrored.
			TmpSegm->defPoints(lpTmpSegPoints, lpType, nCount);
			delete[] lpTmpSegPoints;
			lpTmpSegPoints = NULL;
		}

		m_SegmentArray.add (TmpSegm);
	}

	CDigiChar::setElementData(wSegmData, iDispStyle);
}


//==============================================================================
class CDigi14Segment : public CDigiChar
{
public:
	CDigi14Segment();
	void setElementData(int16 wSegmData, int iDispStyle);
};

CDigi14Segment::CDigi14Segment()
{
	m_Width		= 49;
	m_NSegments = 14;
}

void CDigi14Segment::setElementData(int16 wSegmData, int iDispStyle)
{
	int i, p;
	CDSegment* TmpSegm;
	Point* lpTmpSegPoints = NULL;
	Point* lpSegPoints		= NULL;
	int8* lpType			= NULL;
	int nCount				= 0;

	m_SegmentArray.clear (true);
	for (i = 0; i < m_NSegments; i++)
	{
		// Find data for segment in correct style...
		switch(i)
		{
			case 0:
			case 5:	if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg14N0S;
						lpType = TpSeg14N0S;
						nCount = 13;
					}
					else
					{
						lpSegPoints = PtSeg14N0;
						lpType = TpSeg14N0;
						nCount = 5;
					}

					break;
			case 1:
			case 2:
			case 3:
			case 4:	if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg14N1S;
						lpType = TpSeg14N1S;
						nCount = 10;
					}
					else
					{
						lpSegPoints = PtSeg14N1;
						lpType = TpSeg14N1;
						nCount = 5;
					}

					break;

			case 6:
			case 7:	if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg14N6S;
						lpType = TpSeg14N6S;
						nCount = 6;
					}
					else
					{
						lpSegPoints = PtSeg14N6;
						lpType = TpSeg14N6;
						nCount = 6;
					}

					break;

			case 8:
			case 9:
			case 11:
			case 12:
					if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg14N8S;
						lpType = TpSeg14N8S;
						nCount = 10;
					}
					else
					{
						lpSegPoints = PtSeg14N8;
						lpType = TpSeg14N8;
						nCount = 4;
					}

					break;
			case 13:
			case 10:
					if (iDispStyle & DigitalDisplayComponent::DS_SMOOTH)
					{
						lpSegPoints = PtSeg14N13S;
						lpType = TpSeg14N13S;
						nCount = 17;
					}
					else
					{
						lpSegPoints = PtSeg14N13;
						lpType = TpSeg14N13;
						nCount = 4;
					}

					break;

		}
		// For nondefined segments use mirroring...
		switch(i)
		{
		case 5: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;

		case 2: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorX(lpSegPoints[p], (m_Width-1)/2);

				break;

		case 3: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;

		case 4: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = pointMirror(lpSegPoints[p], Point((m_Width-1)/2, 41));

				break;

		case 7: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorX(lpSegPoints[p], (m_Width-1)/2);

				break;

		case 9: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;

		case 11: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = pointMirror(lpSegPoints[p], Point((m_Width-1)/2, 41));

				break;

		case 12: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorX(lpSegPoints[p], (m_Width-1)/2);

				break;

		case 10: lpTmpSegPoints = new Point[nCount];
			for (p = 0; p < nCount; p++)
				lpTmpSegPoints[p] = lineMirrorY(lpSegPoints[p], 41);

				break;
		}

		// Copy data to segment array...
		TmpSegm = new CDSegment ();
		
		if (lpTmpSegPoints == NULL)
		{
			// point is an original.
			TmpSegm->defPoints(lpSegPoints, lpType, nCount);
        }
		else
		{
			// point is mirrored.
			TmpSegm->defPoints(lpTmpSegPoints, lpType, nCount);
			delete[] lpTmpSegPoints;
			lpTmpSegPoints = NULL;
		}

		m_SegmentArray.add (TmpSegm);
	}

	CDigiChar::setElementData(wSegmData, iDispStyle);
}


//==============================================================================
DigitalDisplayComponent::DigitalDisplayComponent (const String& componentName, const String& labelText)
  : Label (componentName, labelText),
	m_OffColor (Colours::darkgreen),
	m_OnColor (Colours::lightgreen),
	m_BackColor (Colours::black),
	m_DispStyle (DS_SZ_PROP | DS_SOFT),
	m_bTransparent (false),
	m_bMakeStroke (true)
{
}

DigitalDisplayComponent::~DigitalDisplayComponent()
{
	m_CharArray.clear(true);
}

void DigitalDisplayComponent::setColours(const Colour &OffColor, const Colour &OnColor)
{
	if (m_OnColor == OnColor && m_OffColor == OffColor)
		return;

	m_OnColor = OnColor;
	m_OffColor = OffColor;

	repaint();
}

Colour DigitalDisplayComponent::setBackgrondColour (const Colour &BackColor /* = BLACK */)
{
	Colour PrevBkColor(m_BackColor);

	if (m_BackColor == BackColor)
		return m_BackColor;

	m_BackColor = BackColor;

	repaint();

	return PrevBkColor;
}

bool DigitalDisplayComponent::modifyDigiStyle (int dwRemove, int dwAdd)
{
	if (dwRemove & dwAdd)
		return false;

	m_DispStyle |= dwAdd;
	m_DispStyle &= ~dwRemove;

    textHasChanged ();

	repaint();

	return true;
}

CDigiChar *DigitalDisplayComponent::defineChar (tchar cChar)
{
	int iIndex;
	CDigiChar *pDChar = 0;

	if ((cChar >= T('0') && cChar <= T('9'))
		|| (cChar == T(' ') || cChar == T('-')))
	{
		// these characters can be 7 or 14 segments...
		if (cChar == T(' '))
		{
			iIndex = 0;
		}
		else
			if (cChar == T('-'))
			{
				iIndex = 11;
			}
			else
			{
				iIndex = cChar - T('0') + 1;
			}

		if (m_DispStyle & DS_STYLE14)
		{
			pDChar = new CDigi14Segment;
			pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);
		}
		else
		{
			pDChar = new CDigi7Segment;
			pDChar->setElementData(CHAR_SEGM7[iIndex], m_DispStyle);
		}
	}
	else
		if (cChar >= T('A') && cChar <= T('Z'))
		{
			// 14 segment only...
			iIndex = cChar - T('A') + 12;
			pDChar = new CDigi14Segment;
			pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);
		}
		else
		{
			// Spcial characters...
			iIndex = 0;

			switch(cChar)
			{
				case T(':'): iIndex++;
				case T('.'): pDChar = new CDigiColonDotChar;
						pDChar->setElementData(CHAR_SEMCOL[iIndex], m_DispStyle);

						break;

				case T('*'): iIndex = MAXSEGCHAR14 - 7; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T('+'): iIndex = MAXSEGCHAR14 - 6; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T('('): iIndex = MAXSEGCHAR14 - 5; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T(')'): iIndex = MAXSEGCHAR14 - 4; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T('\\'): iIndex = MAXSEGCHAR14 - 3; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T('/'): iIndex = MAXSEGCHAR14 - 2; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;

				case T('\''): iIndex = MAXSEGCHAR14 - 1; pDChar = new CDigi14Segment;
						pDChar->setElementData(CHAR_SEGM14[iIndex], m_DispStyle);

						break;
			}
	}

	return pDChar;
}

void DigitalDisplayComponent::textHasChanged ()
{
	CDigiChar* pDChar;

	m_CharArray.clear(true);

    String strText = getText ();

	if (strText == T("?"))
		strText = getName();

	strText.toUpperCase();

	for (int i = 0; i < strText.length(); i++)
	{
		if ((pDChar = defineChar(strText[i])) != NULL)
		{
			m_CharArray.add (pDChar);
		}
	}
}

void DigitalDisplayComponent::paint(Graphics &gc)
{
	int width = getWidth();
	int height = getHeight();
	DRectangle CharRect;
	int r, g, b;
	Colour	PenColor1;
	Colour	PenColor2;

	if(!m_bTransparent)
		gc.fillAll(m_BackColor);

	SolidColourBrush hBrushOff (m_OffColor), hBrushOn (m_OnColor);
	gc.setBrush (&hBrushOn);

	if (m_DispStyle & DS_SOFT)
	{
		r = int(m_OffColor.getRed() * 0.75 + m_BackColor.getRed() * 0.25);
		g = int(m_OffColor.getGreen() * 0.75 + m_BackColor.getGreen() * 0.25);
		b = int(m_OffColor.getBlue() * 0.75 + m_BackColor.getBlue() * 0.25);

		PenColor1 = Colour(r,g,b);
	}
	else
		PenColor1 = m_OffColor;

	PathStrokeType ptype = PathStrokeType::curved;

	if (m_DispStyle & DS_SOFT)
	{
		r = int(m_OnColor.getRed() * 0.75 + m_BackColor.getRed() * 0.25);
		g = int(m_OnColor.getGreen() * 0.75 + m_BackColor.getGreen() * 0.25);
		b = int(m_OnColor.getBlue() * 0.75 + m_BackColor.getBlue() * 0.25);

		PenColor2 = Colour(r,g,b);
	}
	else
		PenColor2 = m_OnColor;

	int iTotWidth = 0;
	double dRelWidth, dRelHeight;

	// Calculate resizing factors...
	int iChar;
	for (iChar = 0; iChar < m_CharArray.size(); iChar++)
	{
		iTotWidth += m_CharArray.getUnchecked (iChar)->getNormWidth();
	}

	dRelWidth = double(width) / double(iTotWidth);
	dRelHeight = double(height) / double(NORM_DIGIHEIGHT);

	// If proportional make offset for centered text
	if (m_DispStyle & DS_SZ_PROP)
	{
		if (dRelWidth < dRelHeight)
			dRelHeight = dRelWidth;
		else
			dRelWidth = dRelHeight;

		CharRect.left = (width - dRelWidth * iTotWidth) / 2;
		CharRect.top = (height - dRelHeight * NORM_DIGIHEIGHT) / 2;
	}
	else
		CharRect.clear();

	// Draw all characters...
	for (iChar = 0; iChar < m_CharArray.size(); iChar++)
	{
	    CDigiChar* currentChar = m_CharArray.getUnchecked (iChar);
	    
		CharRect.setRect (CharRect.left, CharRect.top,
						  CharRect.left + dRelWidth * currentChar->getNormWidth(),
						  CharRect.top  + dRelHeight * NORM_DIGIHEIGHT);

		currentChar->draw (&gc, CharRect, PenColor1, PenColor2, hBrushOff, hBrushOn, m_bMakeStroke);

		CharRect.left += dRelWidth * currentChar->getNormWidth();
	}
}

void DigitalDisplayComponent::setTransparent(bool bSet)
{
	if(m_bTransparent != bSet)
	{
		m_bTransparent = bSet;

		repaint();
	}
}

void DigitalDisplayComponent::setMakeStroke(bool makeStroke)
{
	if(m_bMakeStroke != makeStroke)
	{
		m_bMakeStroke = makeStroke;

		repaint();
	}
}

END_JUCE_NAMESPACE

#endif

/*
 ==============================================================================

	Original Author

	Copyright (C) 2000 by Michel Wassink
	All rights reserved

	This is free software.
	This code may be used in compiled form in any way you desire. This
	file may be redistributed unmodified by any means PROVIDING it is
	not sold for profit without the authors written consent, and
	providing that this notice and the authors name and all copyright
	notices remains intact. If the source code in this file is used in
	any  commercial application then a statement along the lines of
	"Portions Copyright (c) 2002 Michel Wassink" must be included in
	the startup banner, "About" box or printed documentation. An email
	letting me know that you are using it would be nice as well. That's
	not much to ask considering the amount of work that went into this.

	No warrantee of any kind, expressed or implied, is included with this
	software; use at your own risk, responsibility for damages (if any) to
	anyone resulting from the use of this software rests entirely with the
	user.

	Send bug reports, bug fixes, enhancements, requests, flames, etc., and
	I'll try to keep a version up to date.  I can be reached as follows:
        micways@hotmail.com	                (private site)
	An email letting me know that you are using it would be nice.

 ==============================================================================
 */

