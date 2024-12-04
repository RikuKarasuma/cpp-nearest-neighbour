#ifndef POINT_H // Include guard
#define POINT_H

    #include <string>

    class Point {

        private:
            float x;
            float y;
            std::string name;

        public:
            Point();
            Point(std::string name, float x, float y);

            float getX() const;

            float getY() const;

            std::string getName() const;

            float findDistance(const Point& toCompare) const;

            void toString() const;

            bool operator==(const Point& other) const {
                return 
                    name == other.name &&
                    x == other.x &&
                    y == other.y;
            }

            bool operator!=(const Point& other) const {
                return 
                    name != other.name ||
                    x != other.x ||
                    y != other.y;
            }
    };

#endif
