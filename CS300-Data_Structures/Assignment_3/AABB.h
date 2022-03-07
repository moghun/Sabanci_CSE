//Muhammed Orhun Gale - 26754

#include <iostream>
#ifndef _AABB
#define _AABB
struct AABB{
    // The coordinates that define the AABB
    // (minX, minY) is the point that defines the bottom left corner 
    // (maxX, maxY) the point that defines the upper right corner
    //  Example: A = (minX, minY), B = (maxX, maxY)
    //  +---B
    //  |   |
    //  A---+
    int minX, minY, maxX, maxY;
    // Construct the AABB
    AABB(int _minX, int _minY, int _maxX, int _maxY):minX(_minX), maxX(_maxX), minY(_minY), maxY(_maxY){}
    // get the area of the current AABB
    int getArea() const{
        return (maxX-minX)*(maxY-minY);
    }
    // Create an AABB that contains both the calling object
    // and rhs
    AABB operator+(const AABB& rhs) const{
        return  AABB(getMin(minX, rhs.minX), getMin(minY, rhs.minY), getMax(maxX, rhs.maxX), getMax(maxY, rhs.maxY));
    }
    // Check if the calling object and the AABB rhs are identical
    bool operator!=(const AABB & rhs){
        return  minX!=rhs.minX || 
                minY!=rhs.minY ||
                maxX!=rhs.maxX ||
                maxY!=rhs.maxY;
    }
    // Check if the calling object and the AABB rhs collide
    bool collide(const AABB & rhs) const{
        return maxX >= rhs.minX && minX <= rhs.maxX && maxY >= rhs.minY && minY <= rhs.maxY;
    }
    // Print the information of this AABB to the stream "out"
    void printAABB(std::ostream& out){
        out << "min = (" << minX << ", " << minY << "), ";
        out << "max = (" << maxX << ", " << maxY << "), ";
        out << "Area = " << getArea();
    }

    ////////
    // Static functions (they don't need a calling object)
    ///////
    
    // Get the minimum value between x and y
    static int getMin(int x, int y) {
        return (x < y) ? x : y;
    }
    // Get the maximum value between x and y
    static int getMax(int x, int y) {
        return (x > y) ? x : y;
    }
    // Return the area of the AABB that will cover (or contain)
    // the AABBs lhs and rhs
    static int unionArea(const AABB & lhs, const AABB& rhs) {
        return  (getMax(lhs.maxX, rhs.maxX) - getMin(lhs.minX, rhs.minX)) *
                (getMax(lhs.maxY, rhs.maxY) - getMin(lhs.minY, rhs.minY));
    }
};


#endif