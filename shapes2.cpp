#include <iostream>

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

class Linie : public Shape {
public:
    Linie (Point start, Point end): m_start{start}, m_end{end}{}

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



int main() {
    std::cout << "Hello, World!" << std::endl;

    Point p1;
    Point p2 {20, 20};
    Linie linie {p1, p2};
    Circle circle ;
    p1.draw();
    p2.draw();
    linie.draw();
    circle.draw();
    return 0;
}