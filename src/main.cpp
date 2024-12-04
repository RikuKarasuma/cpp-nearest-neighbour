#include <iostream>
#include <vector>
#include <algorithm>
#include "point.h"

Point findNearest(const Point& location,
                  const std::vector<Point>& allLocations,
                  const std::vector<Point>& visited) {

    float currentDistance(0);
    Point currentShortest; 
    for (const Point& otherLocation: allLocations) {

        Point alreadyVisted = *std::find(visited.begin(), visited.end(), otherLocation);

        if (alreadyVisted == otherLocation) {
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



std::vector<Point> findShortestPathNearestNeighbour(const int startingPointIndex, const std::vector<Point>& points) {

    if (startingPointIndex < 0) {
        std::cerr << "Can't start from an index less than zero." << std::endl;
    }
    else if (startingPointIndex > (points.size() - 1)) {
        std::cerr << "Can't start from an index greater than the total points provided." << std::endl;
    }

    std::vector<Point> shortestPathByIndex;
    Point currentPoint = points.at(startingPointIndex);
    shortestPathByIndex.push_back(currentPoint);
    while (shortestPathByIndex.size() != points.size()) {

        currentPoint = findNearest(currentPoint, points, shortestPathByIndex);
        shortestPathByIndex.push_back(currentPoint);
    }

    return shortestPathByIndex;
}



int main() {

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

    std::vector<Point> shortestPath = findShortestPathNearestNeighbour(4, points);

    std::cout << "Completed, listing path..." << std::endl << std::endl;

    for (Point route : shortestPath) {
        route.toString();
    }

    return 0;
}

