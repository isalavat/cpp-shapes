/**
 * Shapes program Version 4.
 * @source - example project from module "PTI651 Fortgeschrittene Konzepte der Progr. mit C/C++"
 * at FH-Zwickau University (https://github.com/whzcpp2019/cpp/wiki/Shapes).
 * In this cpp program are defined  Point, Circle, Line classes
 * and their Basic class Shape, that has draw and move methods.
 * Child classes override these methods, but they aren't functioning in this
 * version of program. It has to be improved to be able to override methods
 * in the next version of the program.
 * This program reads several parameters from console to create
 * appropriate instance of the shape (Line or Circle). In this version of
 * the shapes program there is create_shape() method, that is resposible
 * for creating shapes
 */

#include <iostream>
using  namespace std;
class Shape{
public:
    void draw() const {
        std::cout<<"Es tut nichts sinnvolles"<<std::endl;
    }

    void move() {
        std::cout<<"Es tut nichts sinnvolles"<<std::endl;
    }
};

class Point {
public:
    Point(int x = 0, int y = 0): m_x{x}, m_y{y} {}

    int x() const { return m_x; }

    int y() const { return m_y; }

    void draw() const {
        std::cout << "Point{" << x() << "; " << y() << "}" << std::endl;
    }

    void move(const int delta_x, const int delta_y) {
        m_x += delta_x;
        m_y += delta_y;
    }

private:
    int m_x, m_y;
};

class Line : public Shape {
public:
    Line (Point start, Point end): m_start{start}, m_end{end}{}

    Point start() const { return m_start; }

    Point end() const { return m_end; };

    void move(const int delta_x, const int delta_y) {
        m_start.move(delta_x, delta_y);
        m_end.move(delta_x, delta_y);
    }

    void draw () const {
        std::cout << "Line\n"
                  << " start:\t";
        m_start.draw();
        std::cout << " end:\t";
        m_end.draw();
    }

private:
    Point m_start, m_end;
};

class Circle: public Shape {
public:
    Circle( Point center = {0, 0}, int radius = 1.0): m_center{center}, m_radius{radius} {}

    Point center () const {
        return m_center;
    }

    int radius () const {
        return m_radius;
    }

    void move(const int delta_x, const int delta_y) {
        m_center.move(delta_x, delta_y);
    }

    void draw() const {
        std::cout << "Circle\n"
                  << " center:\t";
        m_center.draw();
        std::cout << " radius:\t" << m_radius << std::endl;
    }

private:
    Point m_center;
    int m_radius;

};

/**
 *Creates appropriate shape based on given shape_type parameter
 * l - Line
 * c - Circle
 * throws an error if given parameter not correct
 */
Shape create_shape (const char shape_type) {
    switch(tolower(shape_type)) {
        case 'l':{
            int start_x, start_y, end_x, end_y;
            if(!(cin>>start_x>>start_y>>end_x>>end_y)) {
                cerr<< "Invalid input: Could not create line"<<endl;
            }
            Line l {{start_x, start_y}, {end_x, end_y}};
            cout << "Created line: (" << l.start().x() << "; " << l.start().y()
                 << ") (" << l.end().x() << "; " << l.end().y() << ")" << endl;

            break;
        }
        case  'c':{
            int center_x, center_y, radius;
            if(!(cin>>center_x>>center_y>>radius)){
                cerr<<"Invalid input: Could not create circle."<<endl;
            }
            Circle c{{center_x, center_y}, radius};
            cout << "Created circle: centre: (" << c.center().x() << "; "
                 << c.center().y() << "), radius: " << c.radius() << endl;
            break;
        }
        default: {
            throw runtime_error{string{"Could not handle shape type '"} + shape_type +
                                "'"};
        }
    }

}

int main() {
    cout << "Command line for creating a single shape:\n\t"
            "- Create line with: 'l start_x start_y end_x end_y'\n\t"
            "- Create circle with: 'c centre_x centre_y radius'\n\t"
            "- Abort: x"
         << endl;
    char shape_type;

    while(cin>>shape_type){
        if(shape_type == 'x') {
            break;
        }

        Shape s = create_shape(shape_type);
        s.draw();
    }

    return 0;
}