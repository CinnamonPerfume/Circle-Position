#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 1e-12
/*
Distance between centers
distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

distance == r1 + r2 
they touch

distance > r1 + r2
they don't touch

distance < r1 + r2
they intersect, bigger area should be the host

Internal touch
distance = r1 - r2

Overlap formula
e1 = r1^2 * acos((distance^2 + r1^2 - r2^2)/(2 * distance * r1))
e2 = r2^2 * acos((distance^2 + r2^2 - r1^2)/(2 * distance * r2))
e3 = 0.5 * sqrt((-distance + r1 + r2) * (distance + r1 - r2) * (distance - r1 + r2) * (distance + r1 + r2))
Overlap = e1 + e2 - e3
*/

int main () {
    double x1, y1, r1; //Circle 1
    double x2, y2, r2; //Circle 2
    double e1, e2, e3, overlap;
    double distance, touch;

    //User Input START
    printf("Enter circle #1 parameters:\n");
    if ( scanf("%lf %lf %lf", &x1, &y1, &r1) != 3 || r1 <= 0) {
        printf("Invalid input.\n");
        return 0;
    }

    printf("Enter circle #2 parameters:\n");
    if ( scanf("%lf %lf %lf", &x2, &y2, &r2) != 3 || r2 <= 0) {
        printf("Invalid input.\n");
        return 0;
    }
    //User Input END

    //Overlap Module START  
    distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    e1 = r1 * r1 * acos((distance * distance + r1 * r1 - r2 * r2) / (2 * distance * r1));
    e2 = r2 * r2 * acos((distance * distance + r2 * r2 - r1 * r1) / (2 * distance * r2));
    e3 = 0.5 * sqrt((-distance + r1 + r2) * (distance + r1 - r2) * (distance - r1 + r2) * (distance + r1 + r2));
    overlap = e1 + e2 - e3;
    //Overlap Module END
    touch = 0;


    //Touch Module START
    if ((fabs(x1-x2) <= fabs(x2) * EPS) && (fabs(y1-y2) <= fabs(y2) * EPS) && (fabs(r1-r2) <= fabs(r2) * EPS))
        touch = 2; //Identical
    else if (distance < fabs(r1 - r2))
        touch = 4; //One inside the other
    else if ((r1 - r2) < distance && distance < (r1 + r2))
        touch = 6; //Intersection
    else if (distance > (r1 + r2))
        touch = 5; //No contact, outside of eachother
    else if ((fabs(distance-(r1 + r2)) <= fabs(r1 + r2) * EPS))
        touch = 1; //External Touch
    else if (distance >= fabs(r1 - r2))
        touch = 3; //Internal Touch

        
    
    
    if (touch == 1)
        printf("External touch, no overlap.\n");
    else if (touch == 2)
        printf("The circles are identical, overlap: %f\n", (M_PI * r1 * r1));
    else if (touch == 3) {
        printf("Internal touch, ");
        if (M_PI * r1 * r1 > M_PI * r2 * r2) //Circle 1 area > Circle 2 area
            printf("circle #2 lies inside circle #1, overlap: %f\n", overlap);
        else
            printf("circle #1 lies inside circle #2, overlap: %f\n", overlap); }
    else if (touch == 4) {
        if (M_PI * r1 * r1 > M_PI * r2 * r2) //Circle 1 area > Circle 2 area
            printf("Circle #2 lies inside circle #1, overlap: %f\n", (M_PI * r2 * r2));
        else
            printf("Circle #1 lies inside circle #2, overlap: %f\n", (M_PI * r1 * r1)); }
    else if (touch == 5)
        printf("The circles lie outside each other, no overlap.\n");
    else if (touch == 6)
        printf("The circles intersect, overlap: %f\n", overlap);
    //Touch Module END

    return 0;
}