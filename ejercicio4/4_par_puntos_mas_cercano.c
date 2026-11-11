#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int compareX(const void* a, const void* b){
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if(p1->x != p2->x) return (p1->x > p2->x) - (p1->x < p2->x);
    return (p1->y > p2->y) - (p1->y < p2->y);
}

int compareY(const void* a, const void* b){
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if(p1->y != p2->y) return (p1->y > p2->y) - (p1->y < p2->y);
    return (p1->x > p2->x) - (p1->x < p2->x);
}

double dist(Point p1, Point p2){
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point* P, int n){
    double min = 1000000000.0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            double d = dist(P[i], P[j]);
            if(d < min) min = d;
        }
    }
    return min;
}

double stripClosest(Point* strip, int size, double d){
    double min = d;
    qsort(strip, size, sizeof(Point), compareY);
    
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; j++){
            double distVal = dist(strip[i], strip[j]);
            if(distVal < min) min = distVal;
        }
    }
    return min;
}

double closestUtil(Point* P, int n){
    if(n <= 3){
        return bruteForce(P, n);
    }
    
    int mid = n / 2;
    Point midPoint = P[mid];
    
    double dl = closestUtil(P, mid);
    double dr = closestUtil(P + mid, n - mid);
    
    double d = dl < dr ? dl : dr;
    
    Point* strip = (Point*)malloc(n * sizeof(Point));
    int j = 0;
    for(int i = 0; i < n; i++){
        if(fabs(P[i].x - midPoint.x) < d){
            strip[j++] = P[i];
        }
    }
    
    double minStrip = stripClosest(strip, j, d);
    free(strip);
    
    return minStrip < d ? minStrip : d;
}

int main(){
    int n;
    while(scanf("%d", &n) == 1 && n != 0){
        Point* points = (Point*)malloc(n * sizeof(Point));
        for(int i = 0; i < n; i++){
            scanf("%lf %lf", &points[i].x, &points[i].y);
        }
        
        if(n <= 1){
            printf("INFINITY\n");
            free(points);
            continue;
        }
        
        qsort(points, n, sizeof(Point), compareX);
        double minDistance = closestUtil(points, n);
        
        if(minDistance >= 10000.0){
            printf("INFINITY\n");
        }else{
            printf("%.4f\n", minDistance);
        }
        free(points);
    }
    return 0;
}
