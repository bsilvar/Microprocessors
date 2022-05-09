#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double perim(double A, double B, double C) {
   double a = A;
   double b = B;
   double c = C;
   return (a+b+c);
}

double area(double A, double B, double C){
   double a = A;
   double b = B;
   double c = C;
   double s = 0.5 * perim(a, b, c);
   //double area = (s*(s-a)*(s-b)*(s-c))*0.5;
   //return area;
   return (sqrt(s*(s-a)*(s-b)*(s-c)));
}

double read_input() {
   double num;
   scanf(" %lf", &num);
   return num;
}

void print_value(double val) {
   printf("%lf\n", val);
}

int main(void) {
   printf("Enter side a:");
   double a = read_input();
   printf("Enter side b:");
   double b = read_input();
   printf("Enter side c:");
   double c = read_input();
   printf("Area = ");
   print_value(area(a,b,c));
   return 0;
}

