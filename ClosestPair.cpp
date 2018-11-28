/*
    Created by ustcwzy at 2018/11/21.   
*/

#include<ctime>
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

#define _INFINITY 1000000;

typedef struct point {
    double x;
    double y;
}point;

//Generate the random points.
class dataGenerator {
    public:
        void generate(point *p, int n) {
            srand((unsigned) time(NULL));
            cout << "--The original data is:" << endl;
            for (int i = 0; i < n; i++) {
                p[i].x = (double)(rand() % 20001 - 10000) / (double)100;
                p[i].y = (double)(rand() % 20001 - 10000) / (double)100;
                cout << "(" << p[i].x << ", " << p[i].y << ") ";
            }
            cout << endl;
        }
};

bool compare(point a, point b) {
    return a.x < b.x;
}

class Closest {
    public:
        inline double dist(point p1, point p2) {
            return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
        }

        double ClosestPair(point points[], int length, point &a, point &b)
        {
            double distance = 1000;        //the min distance. 
            double d1,d2;           //the min distance of the two parts.
            int i=0,j=0,k=0;
            point a1,b1,a2,b2;     //the closest pair points

            if(length < 2) return _INFINITY;    //if the length is less than 2, the distance is defined infinity.
            if(length == 2) {
                a = points[0];
                b = points[1];
                distance = dist(points[0], points[1]);
            } else {
                point *pts1 = new point[length];
                point *pts2 = new point[length];  

                sort(points, points+length, compare);   //sort with the compare
                // cout << "--The sorted points are:" << endl;
                // for (int i = 0; i < length; i++) {
                //     cout << "(" << points[i].x << ", " << points[i].y << ") ";
                // }
                // cout << endl;
                double mid = points[(length-1)/2].x;  //find the median

                //Divide
                for(i = 0; i < length/2; i++)
                    pts1[i] = points[i];
                for(j = 0,i = length/2; i < length; i++)
                    pts2[j++] = points[i];

                //Recusion
                d1 = ClosestPair(pts1, length/2, a1, b1);          
                d2 = ClosestPair(pts2, length-length/2, a2, b2);

                //determine the min distance and the closest points now. 
                if (d1 < d2) { 
                    distance = d1;
                    a = a1;
                    b = b1;
                } else { 
                    distance = d2;
                    a = a2;
                    b = b2;
                }

                //Compute the points near the mid.
                point *pts3 = new point[length];
                // cout << "--The mid is " << mid << ". The min distance now is " << distance << endl;
                // cout << "--The points near the mid are:" << endl;
                for(i = 0, k = 0; i < length; i++) {
                    if(abs(points[i].x - mid) <= distance) {
                        // cout << "(" << points[i].x << ", " << points[i].y << ") ";
                        pts3[k++] = points[i];
                    }
                }
                // cout << endl;


                //Combine.
                for(i = 0; i < k; i++) {
                    for(j = i+1; j <= i+7 && j < k; j++) {
                        if(dist(pts3[i], pts3[j]) < distance) {
                            distance = dist(pts3[i], pts3[j]);
                            a=pts3[i];
                            b=pts3[j];
                        }
                    }
                }
            }
            return distance;
        }
};

int main() {
    int length;
    cout << "--Input the number of the points:";
    cin >> length;

    dataGenerator d;
    point *p = new point[length];
    d.generate(p, length);

    point r1, r2;
    Closest Solution;
    double dist = Solution.ClosestPair(p, length, r1, r2);
    cout <<"The closest points are (" << r1.x << ", " << r1.y << ") and (" << r2.x << ", " << r2.y << ")."<< endl;
    cout << "The closest distance is " << dist << endl;
    // double min = 10000000;
    // for (int i = 0; i < length; i++) {
    //     for (int j = i+1; j < length; j++) {
    //         if(Solution.dist(p[i], p[j]) < min) {
    //             min = Solution.dist(p[i], p[j]);
    //             r1 = p[i];
    //             r2 = p[j];
    //         }
    //     }
    // }
    // cout << endl;
    // cout <<"The closest points are (" << r1.x << ", " << r1.y << ") and (" << r2.x << ", " << r2.y << ")."<< endl;
    // cout << "The closest distance is " << min << endl;
    system("pause");
    return 0;
}