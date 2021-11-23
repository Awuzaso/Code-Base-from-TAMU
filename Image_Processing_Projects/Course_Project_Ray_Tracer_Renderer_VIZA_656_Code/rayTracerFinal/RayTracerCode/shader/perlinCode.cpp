#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#define B 0x100 //BINARY 256
#define BM 0xff //BINARY 255

#define N 0x1000 //BINARY 4096
#define NP 12   /* 2^N */
#define NM 0xfff //4095

static int p[B + B + 2]; //514 p's
static float g3[B + B + 2][3]; //514x3 g3's
static float g2[B + B + 2][2]; //514x2 g2's
static float g1[B + B + 2]; //514 g1's
static int start = 1;

#define setup(i,b0,b1,r0,r1)\
    t = vec[i] + N;\
    b0 = ((int)t) & BM;\
    b1 = (b0+1) & BM;\
    r0 = t - (int)t;\
    r1 = r0 - 1.;
/////////////////////////////////////////////////////////////////
// /*S_CURVE FUNCTION*/
/////////////////////////////////////////////////////////////////
float s_curve(float t){
    float retVal=(pow(t,2)*(3.0-2.0*t));
    return retVal;
}
/////////////////////////////////////////////////////////////////
// /*LINEAR INTERPOLATION FUNCTION*/
/////////////////////////////////////////////////////////////////
float lerp(float t, float a, float b){
    float retVal= ( a + t * (b - a) );
    return retVal;
}
/////////////////////////////////////////////////////////////////
// /*TWO DIMENSIONAL NORMALIZE FUNCTION.*/
/////////////////////////////////////////////////////////////////
static void normalize2(float v[2])
{
    float s;

    s = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
}
/////////////////////////////////////////////////////////////////
// /*THREE DIMENSIONAL NORMALIZE FUNCTION.*/
/////////////////////////////////////////////////////////////////
static void normalize3(float v[3])
{
    float s;

    s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] = v[0] / s;
    v[1] = v[1] / s;
    v[2] = v[2] / s;
}
/////////////////////////////////////////////////////////////////
// /*INITIALIZE FUNCTION FOR GRADIENTS.*/
/////////////////////////////////////////////////////////////////
static void init2(void)
{
    int i, j, k;

    for (i = 0 ; i < B ; i++) {
        p[i] = i;

        g1[i] = (float)((random() % (B + B)) - B) / B;

        for (j = 0 ; j < 2 ; j++)
            g2[i][j] = (float)((random() % (B + B)) - B) / B;
        normalize2(g2[i]);

        for (j = 0 ; j < 3 ; j++)
            g3[i][j] = (float)((random() % (B + B)) - B) / B;
        normalize3(g3[i]);
    }

    while (--i) {
        k = p[i];
        p[i] = p[j = random() % B];
        p[j] = k;
    }

    for (i = 0 ; i < B + 2 ; i++) {
        p[B + i] = p[i];
        g1[B + i] = g1[i];
        for (j = 0 ; j < 2 ; j++)
            g2[B + i][j] = g2[i][j];
        for (j = 0 ; j < 3 ; j++)
            g3[B + i][j] = g3[i][j];
    }
}
/////////////////////////////////////////////////////////////////
// /*2D NOISE FUNCTION*/
/////////////////////////////////////////////////////////////////
float noise2D(float vec[2])
{
    //1)ESTABLISH VARS.
    int bx0, bx1, by0, by1, b00, b10, b01, b11;
    float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
    int i, j;//VARS FOR SPECIFYING POINTS
    
    //2)IF START ==1, THEN PROCEED.
    if (start==1) {
        start = 0;//RESET START TO 0.
        init2();//INITIALIZE GRADIENT VECTORS.
    }

    //3)SETUP THE INITIAL POINTS.
    setup(0, bx0,bx1, rx0,rx1);
    setup(1, by0,by1, ry0,ry1);

    i = p[ bx0 ];
    j = p[ bx1 ];

    //4)SETUP THE ADJACENT POINTS.
    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    //5)SETUP SX AND SY FOR INTERPOLATION VALUE FOR EASE CURVE.
    sx = s_curve(rx0);
    sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

    q = g2[ b00 ] ; u = at2(rx0,ry0);
    q = g2[ b10 ] ; v = at2(rx1,ry0);
    a = lerp(sx, u, v);

    q = g2[ b01 ] ; u = at2(rx0,ry1);
    q = g2[ b11 ] ; v = at2(rx1,ry1);
    b = lerp(sx, u, v);

    return lerp(sy, a, b);
}

float noise3D(float vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (start) {
		start = 0;
		init2();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
} 
