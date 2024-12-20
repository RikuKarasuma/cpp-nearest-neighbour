#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include "point.h"


class StartingIndexError : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Can't start from an index less than zero.";
        }
};

class IndexBoundaryError : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Can't start from an index greater than the total points provided.";
        }
};

static Point findNearest(const Point& location,
                         const std::vector<Point>& allLocations,
                         const std::vector<Point>& visited) {

    float currentDistance(0);
    Point currentShortest; 
    for (const Point& otherLocation: allLocations) {

        std::vector<Point>::const_iterator alreadyVisted = std::find(
            visited.begin(),
            visited.end(),
            otherLocation
        );

        // Need to check for finding failure before dereferencing
        // or else we will encounter issues on linux.
        if (alreadyVisted != visited.end() || *alreadyVisted == otherLocation) {
            continue;
        }
        
        const float distanceToNextLocation = location.findDistance(otherLocation);

        if (currentDistance == 0 || distanceToNextLocation < currentDistance) {
            currentDistance = distanceToNextLocation;
            currentShortest = otherLocation;
        }
    }

    return currentShortest;
}

static std::vector<Point> findShortestPathNearestNeighbour(const int startingPointIndex,
                                                           const std::vector<Point>& points) {

    if (startingPointIndex < 0)
        throw StartingIndexError();
    else if (startingPointIndex > (points.size() - 1))
        throw IndexBoundaryError();

    std::vector<Point> shortestPathByIndex;
    Point currentPoint = points.at(startingPointIndex);
    shortestPathByIndex.push_back(currentPoint);
    while (shortestPathByIndex.size() != points.size()) {

        currentPoint = findNearest(currentPoint, points, shortestPathByIndex);
        shortestPathByIndex.push_back(currentPoint);
    }

    return shortestPathByIndex;
}

static void executeNearestNeighbour() {

    std::cout << std::endl;
    std::cout << "Initializing points..." << std::endl;

    std::vector<Point> points;
    points.push_back(Point("Intersection", 14, 10));
    points.push_back(Point("Corner", 40, 30));
    points.push_back(Point("Old Mill", 24, 2));
    points.push_back(Point("Industrial Park", 20, 2));
    points.push_back(Point("Costco", 3, 3));

    std::cout << std::endl;

    for (const Point point : points) {
        point.toString();
    }

    std::cout << std::endl << points.size() << " total, processing..."<< std::endl << std::endl;

    std::cout << "Calculating shortest path..." << std::endl << std::endl;

    std::vector<Point> shortestPath = findShortestPathNearestNeighbour(0, points);

    std::cout << "Completed, listing path..." << std::endl << std::endl;

    for (Point route : shortestPath) {
        route.toString();
    }
}



int main() {

    try {
        executeNearestNeighbour();
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

