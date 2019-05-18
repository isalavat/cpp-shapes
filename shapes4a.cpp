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