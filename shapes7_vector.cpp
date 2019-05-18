#include <iostream>
#include <memory>
#include <vector>

using  namespace std;
class Shape{
public:
    virtual void draw() const {
        std::cout<<"Es tut nichts sinnvolles"<<std::endl;
    }

    virtual void move(const int, const int) {
        std::cout<<"Es tut nichts sinnvolles"<<std::endl;
    }

    virtual ~Shape() = default;
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

    virtual void move (const int delta_x, const int delta_y) override {
        m_start.move(delta_x, delta_y);
        m_end.move(delta_x, delta_y);
    }

    virtual  void draw  () const override {
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

    virtual void move (const int delta_x, const int delta_y) override {
        m_center.move(delta_x, delta_y);
    }

    virtual void draw () const override {
        std::cout << "Circle\n"
                  << " center:\t";
        m_center.draw();
        std::cout << " radius:\t" << m_radius << std::endl;
    }

private:
    Point m_center;
    int m_radius;

};

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

        unique_ptr<Shape> s = create_shape(shape_type);
        shapes.push_back(move(s));
    }

    for(const auto &s: shapes) {
        s->draw();
    }

    return 0;
}