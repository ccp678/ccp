void circle::getPoint_circle_circle(circle &C,Point *p1,Point *p2)
{
    //先考虑两个圆没有交点的情况，1.两个圆处于包含关系，2.两个圆点的距离超过两个圆半径之和
    double X1 = C.P0.x;
    double Y1 = C.P0.y;
    double X0 = P0.x;
    double Y0 = P0.y;
    double distance = sqrt((X1-X0)*(X1-X0)+(Y1-Y0)*(Y1-Y0));
    if(distance > C.R + R||distance < fabs(C.R - R))
    {

        p1->sign = p2 ->sign = false;
    }
    //考虑有交点的情况
    //将两个圆的方程联立起来得到的直线方程造不同的情况下有不同的意义
    //若是在相切的情况下则表示两个圆的切线,在相交的情况下，表示两个圆的交点连线。我们可以庸置疑性质求出交点
    double A0  = 2*(X0-X1);
    double B0 = 2*(Y0-Y1);
    double C0 = X1*X1-X0*X0 + Y1*Y1-Y0*Y0 + R*R - C.R*C.R;
    line l(A0,B0,C0);
    getPoint_Line_circle(l,p1,p2);  //获得交点
}
