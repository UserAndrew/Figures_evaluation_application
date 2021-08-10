#include <algorithm>
#include <iostream>
#include <ciso646>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>


struct Point
{
    double x;
    double y;
};

class IFigure
{
public:
    virtual IFigure* getPtr() = 0;
    virtual std::string getType() = 0;
};

class Rectangle : public IFigure
{
public:
    Point first_point, second_point, third_point, fourth_point;
    std::string type;

    Rectangle(double x1, double y1, double x2, double y2, \
               double x3, double y3, double x4, double y4) {
        first_point.x = x1;
        first_point.y = y1;
        second_point.x = x2;
        second_point.y = y2;
        third_point.x = x3;
        third_point.y = y3;
        fourth_point.x = x4;
        fourth_point.y = y4;
    }

    Rectangle* getPtr() override {
        return this;
    }

    bool isSquare() {
        double a = std::sqrt(std::pow(second_point.x-first_point.x, 2) + \
                             std::pow(second_point.y-first_point.y, 2));
        double b = std::sqrt(std::pow(third_point.x-second_point.x, 2) + \
                             std::pow(third_point.y-second_point.y, 2));
        double c = std::sqrt(std::pow(fourth_point.x-third_point.x, 2) + \
                             std::pow(fourth_point.y-third_point.y, 2));
        double d = std::sqrt(std::pow(fourth_point.x-first_point.x, 2) + \
                             std::pow(fourth_point.y-first_point.y, 2));

        return (a==b);
    }

    std::string getType() override {
        std::string type = "Rectangle";

        return type;
    }

};

class Triangle : public IFigure
{
public:
    Point first_point, second_point, third_point;
    std::string type;

    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        first_point.x = x1;
        first_point.y = y1;
        second_point.x = x2;
        second_point.y = y2;
        third_point.x = x3;
        third_point.y = y3;
    }

    Triangle* getPtr() override {
        return this;
    }


    double lengthTheLargestSide() {
        double first_side = std::sqrt(std::pow(second_point.x-first_point.x, 2) + \
                                    std::pow(second_point.y-first_point.y, 2));
        double second_side = std::sqrt(std::pow(third_point.x-second_point.x, 2) + \
                                       std::pow(third_point.y-second_point.y, 2));
        double third_side = std::sqrt(std::pow(third_point.x-first_point.x, 2) + \
                                      std::pow(third_point.y-first_point.y, 2));

        double max_side = std::max(std::max(first_side, second_side), third_side);

        return max_side;

    }

    std::string getType() override {
        std::string type = "Triangle";

        return type;
    }
};

class Circle : public IFigure
{
public:
    Point center_point;
    double radius;
    std::string type;

    Circle(double x0, double y0, double radius) {
        center_point.x = x0;
        center_point.y = y0;
        this->radius = radius;
    }

    Circle* getPtr() override {
        return this;
    }

    std::string getType() override {
        std::string type = "Circle";

        return type;
    }
};

double calculatingArea(IFigure* figure) {
    double area;
    if(figure->getType() == "Rectangle") {
        Rectangle *rec = dynamic_cast<Rectangle*>(figure);
        if(rec) {
            if(rec->isSquare()) {
                throw "The Rectangle is a square!";
            }
            else {
                double a = std::sqrt(std::pow(rec->second_point.x - rec->first_point.x, 2) + \
                                     std::pow(rec->second_point.y - rec->first_point.y, 2));
                double b = std::sqrt(std::pow(rec->third_point.x - rec->second_point.x, 2) + \
                                     std::pow(rec->third_point.y - rec->second_point.y, 2));

                area = a*b;
            }
        }
    }
    else if(figure->getType() == "Triangle"){
        Triangle *tr = dynamic_cast<Triangle*>(figure);
        if(tr) {
            double length_AB = std::sqrt(std::pow(tr->second_point.x - tr->first_point.x, 2) + \
                                         std::pow(tr->second_point.y - tr->first_point.y, 2));
            double length_AC = std::sqrt(std::pow(tr->third_point.x - tr->first_point.x, 2) + \
                                         std::pow(tr->third_point.y - tr->first_point.y, 2));
            double length_BC = std::sqrt(std::pow(tr->third_point.x - tr->second_point.x, 2) + \
                                       std::pow(tr->third_point.y - tr->second_point.y, 2));

            double semiperimeter = 0.5*(length_AB + length_BC + length_AC);

            area = std::sqrt(semiperimeter*(semiperimeter - length_AB)*(semiperimeter - length_AC)*(semiperimeter - length_AC));
        }
    }
    else if(figure->getType() == "Circle") {
        Circle *crl = dynamic_cast<Circle*>(figure);
        if(crl) {
            area = M_PI*(crl->radius)*(crl->radius);
        }
    }
    return area;
}

int main()
{
    std::vector<IFigure*> figures;

    figures.emplace_back(new Circle(0, 0, 2));
    figures.emplace_back(new Triangle(1.0, 1.0, 1.0, 5.0, 4.0, 1.0));
    figures.emplace_back(new Rectangle(5, 5, 5, 10, 10, 10, 10, 5));
    figures.emplace_back(new Rectangle(2.0, 2.1, 2.0, 4.1, 6.0, 4.1, 6.0, 2.1));

    for(auto& figure : figures) {
        try {
            std::cout << std::fixed << std::setprecision(2) << calculatingArea(figure) << std::endl;
        }
        catch (const char* msg) {
            std::cout << msg << std::endl;
        }
    }

    for(auto& figure : figures) delete figure;

    return 0;
}
