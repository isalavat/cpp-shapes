/**
 * Shapes program Version 10.
 * @source - example project from module "PTI651 Fortgeschrittene Konzepte der Progr. mit C/C++"
 * at FH-Zwickau University (https://github.com/whzcpp2019/cpp/wiki/Shapes).
 * In this cpp program are defined  Point, Circle, Line classes
 * and their basic abstract class Shape, that has draw and move methods.
 * Child classes override these methods. In these version of the program
 * the inheritance functions correctly by using virtual methods and destructor.
 * This program reads several parameters from console to create
 * appropriate instance of the shape (Line or Circle). In this version of
 * the shapes program there is create_shape() method, that is responsible
 * for creating shapes. This method creates and retuns unique pointer of the created
 * shape object to avoid the problem with inheritance and memory (call stack and heap meories).
 * This programm allows to create as many shapes as we want by using std::vector data structure.
 * Shape class is now abstract.
 * In this version is standart std << operator overridden to make it much more easier by using
 * friend key word.
 * In this thenth version was new shape polygon added by using std::vector
 */
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using  namespace std;
class Shape{
public:
    /**
     * Methods without body and with "= 0 " are marked as abstract
     */
    virtual void draw() const = 0;

    virtual void move(const int, const int) = 0;

    virtual ~Shape() = default;
};

class Point {
public:
    Point(int x = 0, int y = 0): m_x{x}, m_y{y} {}

    int x() const { return m_x; }

    int y() const { return m_y; }

    void draw() const {
        std::cout << *this << std::endl;
    }

    void move(const int delta_x, const int delta_y) {
        m_x += delta_x;
        m_y += delta_y;
    }

    friend std::ostream &operator<<(std::ostream &, const Point &);

private:
    int m_x, m_y;
};

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os<<"Point { "<<p.m_x<<";"<<p.m_x<<"}";
    return os;
}

class Line : public Shape {
public:
    Line (Point start, Point end): m_start{start}, m_end{end}{}

    Point start() const { return m_start; }

    Point end() const { return m_end; };

    virtual void move (const int delta_x, const int delta_y) override {
        m_start.move(delta_x, delta_y);
        m_end.move(delta_x, delta_y);
    }

    virtual void draw() const override { cout << *this << endl; }

    friend ostream &operator<<(ostream &, const Line &);

private:
    Point m_start, m_end;
};

std::ostream &operator<<(std::ostream &os, const Line &l) {
    os << "Line start: " << l.m_start << "; end: " << l.m_end;
    return os;
}

class Circle: public Shape {
public:
    Circle( Point center = {0, 0}, int radius = 1.0): m_center{center}, m_radius{radius} {}

    Point center () const {
        return m_center;
    }

    int radius () const {
        return m_radius;
    }

    virtual void move (const int delta_x, const int delta_y) override {
        m_center.move(delta_x, delta_y);
    }

    virtual void draw () const override {
        std::cout << *this << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &, const Circle &);

private:
    Point m_center;
    int m_radius;

};

std::ostream &operator<<(std::ostream &os, const Circle &c){
    os<<"Circle { center - "<<c.m_center<<"; radius - "<<c.m_radius<<"}";
}

class Polygon : public Shape {
private:
    std::vector<Point> m_points;

public:
    Polygon(std::initializer_list<Point> points) : m_points{points} {
        if(points.size() < 3) throw std::logic_error{"A polygon must consist of at least three points."};
    }

    virtual void draw() const override {
        std::cout << "Polygon\n";
        for (const auto p : m_points) {
            std::cout<<p<<std::endl;
        }
    }

    virtual void move(int delta_x, int delta_y) override {
        // TODO
        for (auto &p : m_points) {
            p.move(delta_x, delta_y);
        }
    }

    void add_point(const Point &p) { m_points.emplace_back(p); }

    friend ostream &operator<<(ostream &, const Polygon &);
};

/**
 * Creates appropriate shape based on given shape_type parameter
 * l - Line
 * c - Circle
 * throws an error if given parameter not correct
 *
 *  the created shape object will be returned as a unique pointer, that allows us
 *  to persist the objects in heap and to manage their lifecycle.
 *  Using of unique pointer solves the problem of the incorrect memory access.
 *  Read about call stack vs heap!
 *
 */
unique_ptr<Shape> create_shape (const char shape_type) {
    switch(tolower(shape_type)) {
        case 'l':{
            int start_x, start_y, end_x, end_y;
            if(!(cin>>start_x>>start_y>>end_x>>end_y)) {
                cerr<< "Invalid input: Could not create line"<<endl;
            }
            unique_ptr<Shape> p =
                    make_unique<Line>(Point {start_x, start_y},Point  {end_x, end_y});

            return p;
        }
        case  'c':{
            int center_x, center_y, radius;
            if(!(cin>>center_x>>center_y>>radius)){
                cerr<<"Invalid input: Could not create circle."<<endl;
            }
            return make_unique<Circle>(Point{center_x, center_y}, radius);
        }
        default: {
            throw runtime_error{string{"Could not handle shape type '"} + shape_type +
                                "'"};
        }
    }

}

int main() {
    vector<unique_ptr<Shape>> shapes;

    shapes.push_back(make_unique<Polygon>(Polygon{{10, 20}, {20,30},{100, 200}}));

    cout << "Command line for creating a single shape:\n\t"
            "- Create line with: 'l start_x start_y end_x end_y'\n\t"
            "- Create circle with: 'c centre_x centre_y radius'\n\t"
            "- Abort: x"
         << endl;

    char shape_type;
    /**
     * allows to create many shapes by using std::vector
     */
    while(cin>>shape_type){
        if(shape_type == 'x') {
            break;
        }

        unique_ptr<Shape> s = create_shape(shape_type);
        shapes.push_back(move(s));
    }

    for(const auto &s: shapes) {
        s->draw();
    }

    return 0;
}