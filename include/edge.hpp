#pragma once
#include "point.hpp"

class Triangle;

/// @brief The Edge of a Triangle
class Edge
{
public:

    /// @brief Initialize an Edge
    /// @param t A pointer to the corresponding Triangle
    /// @param p1 point 1
    /// @param p2 point 2
    Edge(Triangle* t, const ScreenPoint& p1, const ScreenPoint& p2);

    /// @brief get y Length of the Edge
    /// @return y Length of the Edge
    int getLength() const;
    /// @brief get x Length of the Edge
    /// @return x Length of the Edge
    int getWidth() const;
    /// @brief get z Length of the Edge
    /// @return z Length of the Edge
    float getDepth() const;

    ScreenPoint p1,p2;
    Triangle* t;
    /// @brief Draws the Spans between two edges
    /// @param edge2 
    void drawSpans(const Edge& edge2);
};
