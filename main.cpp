#include <iostream>
#include <ciso646>
#include <iomanip>
#include <vector>
#include <cmath>


struct Point
{
    double x;
    double y;
};

enum class Figures
{
    CIRCLE,
    RECTANGLE,
    TRIANGLE
};

class IFigure
{
public:
    virtual IFigure* getPtr() = 0;
    virtual Figures getType() = 0;
};

class Rectangle : public IFigure
{
friend double calculatingArea(IFigure* figure);

private:
    Point first_point, second_point, third_point, fourth_point;

public:
    Rectangle(Point p1, Point p2, Point p3, Point p4) {
        first_point.x = p1.x;
        first_point.y = p1.y;
        second_point.x = p2.x;
        second_point.y = p2.y;
        third_point.x = p3.x;
        third_point.y = p3.y;
        fourth_point.x = p4.x;
        fourth_point.y = p4.y;
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

        return (a==b and b==c and c==d);
    }

    Figures getType() override {
        return Figures::RECTANGLE;
    }

};

class Triangle : public IFigure
{
friend double calculatingArea(IFigure* figure);

private:
    Point first_point, second_point, third_point;

public:
    Triangle(Point p1, Point p2, Point p3) {
        first_point.x = p1.x;
        first_point.y = p1.y;
        second_point.x = p2.x;
        second_point.y = p2.y;
        third_point.x = p3.x;
        third_point.y = p3.y;
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

    Figures getType() override {
        return Figures::TRIANGLE;
    }
};

class Circle : public IFigure
{
friend double calculatingArea(IFigure* figure);

private:
    Point center_point;
    double radius;

public:
    Circle(Point p, double radius) {
        center_point.x = p.x;
        center_point.y = p.y;
        this->radius = radius;
    }

    Circle* getPtr() override {
        return this;
    }

    Figures getType() override {
        return Figures::CIRCLE;
    }
};

double calculatingArea(IFigure* figure) {
    double area;
    if(figure->getType() == Figures::RECTANGLE) {
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
    else if(figure->getType() == Figures::TRIANGLE){
        Triangle *tr = dynamic_cast<Triangle*>(figure);
        if(tr) {
            double length_AB = std::sqrt(std::pow(tr->second_point.x - tr->first_point.x, 2) + \
                                         std::pow(tr->second_point.y - tr->first_point.y, 2));
            double length_AC = std::sqrt(std::pow(tr->third_point.x - tr->first_point.x, 2) + \
                                         std::pow(tr->third_point.y - tr->first_point.y, 2));
            double length_BC = std::sqrt(std::pow(tr->third_point.x - tr->second_point.x, 2) + \
                                       std::pow(tr->third_point.y - tr->second_point.y, 2));

            double semiperimeter = 0.5*(length_AB + length_BC + length_AC);

            area = std::sqrt(semiperimeter*(semiperimeter - length_AB)*(semiperimeter - length_BC)*(semiperimeter - length_AC));
        }
    }
    else if(figure->getType() == Figures::CIRCLE) {
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

    figures.emplace_back(new Circle({0.0, 0.0}, 2.0));
    figures.emplace_back(new Triangle({1.0, 1.0}, {1.0, 5.0}, {4.0, 1.0}));
    figures.emplace_back(new Rectangle({5.0, 5.0}, {5.0, 10.0}, {10.0, 10.0}, {10.0, 5.0}));
    figures.emplace_back(new Rectangle({2.0, 2.1}, {2.0, 4.1}, {6.0, 4.1}, {6.0, 2.1}));

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
