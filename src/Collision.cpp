#include "Collision.hpp"

#include <SFML/Graphics.hpp>

/*!
 * \brief Gets the pixels passed through when the centre of the circle is moved
 * in a straight line from point by dPos.
 *
 * \param point The point to start the movement.
 * \param dPos The vector to move by.
 *
 * \return A tupple containing 
 *  - a vector of a tuple containing
 *  -- the point
 *  -- the popotion of time it takes to reach that point
 *  - the time interval used in the calculation
 */
std::tuple<std::vector<std::tuple<Point, float>>, float> getTrajectory(
        const tank::Vectorf& point,
        const tank::Vectorf dPos)
{
    // If we're nearly zero we just return the current point 
    // TODO: this isn't exactly right, but its probaly a good approximaiton we
    // really want to check if we move to a different pixel by adding of dPos
    if ((std::abs(dPos.x) < 0.001 && std::abs(dPos.y) < 0.001))
    {
        return std::tuple<std::vector<std::tuple<Point, float>>, float>({
               std::tuple<Point, float>{
                {static_cast<int>(std::floor(point.x)),
                 static_cast<int>(std::floor(point.y))},
                1}}, 1);
    }

    std::vector<std::tuple<Point, float>> positionsAndTimes;

    // This is true if the line is steeper in y than x
    bool swap = std::abs(dPos.x) < std::abs(dPos.y);
    int numberOfIntervals;
    if (swap)
    {
        numberOfIntervals = std::ceil(std::abs(dPos.y));
    }
    else
    {
        numberOfIntervals = std::ceil(std::abs(dPos.x));
    }

    // We always want to do at leas one step
    if (numberOfIntervals == 0)
    {
        numberOfIntervals = 1;
    }

    // n=1 we assume we're not colliding at the moment
    for (int n = 1; n <= numberOfIntervals; ++n)
    {
        positionsAndTimes.push_back(
                std::make_tuple<Point, float>(
                    { static_cast<int>(point.x + n * dPos.x / numberOfIntervals),
                      static_cast<int>(point.y + n * dPos.y / numberOfIntervals) },
                      n / numberOfIntervals));
    }
    return std::make_tuple(positionsAndTimes, 1.0f / numberOfIntervals);
}

/*!
 * \brief This gets a 1 pixel circle around the give point, of the given
 * radius.
 *
 * \param centre The centre of the circle to get a radius around.
 * \param radius The radius of the circle.
 *
 * \return A vector of the point of the cicle.
 */
std::vector<Point> getCircleToCheck(
        const Point& centre,
        float radius)
{
    // Bresenham's circle algorithm
    std::vector<Point> pointList;
    // TODO: do this properly without converting to integers first
    int cx = centre.x;
    int cy = centre.y;
    int x = 0;
    int y = radius;
    int p = (5 - radius*4)/4;

    pointList.push_back({cx, cy + y});
    pointList.push_back({cx, cy - y});
    pointList.push_back({cx + y, cy});
    pointList.push_back({cx - y, cy});
    while (x < y)
    {
        ++x;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            --y;
            p += 2 * (x - y) + 1;
        }
        if (x == y)
        {
            pointList.push_back({cx + x, cy + y});
            pointList.push_back({cx - x, cy + y});
            pointList.push_back({cx + x, cy - y});
            pointList.push_back({cx - x, cy - y});
        }
        else if (x < y)
        {
            pointList.push_back({cx + x, cy + y});
            pointList.push_back({cx - x, cy + y});
            pointList.push_back({cx + x, cy - y});
            pointList.push_back({cx - x, cy - y});
            pointList.push_back({cx + y, cy + x});
            pointList.push_back({cx - y, cy + x});
            pointList.push_back({cx + y, cy - x});
            pointList.push_back({cx - y, cy - x});
        } 
        else
        {
            pointList.push_back({cx, cy + y});
            pointList.push_back({cx, cy - y});
            pointList.push_back({cx + y, cy});
            pointList.push_back({cx - y, cy});
        }
    }
    return pointList;
}

CollisionMap::CollisionMap(std::string file)
{
    sf::Image t;
    t.loadFromFile(file);

    auto size = t.getSize();
    width = size.x;
    height = size.y;
    collide_ = std::vector<bool>(width * height, false);

    auto collideColor = t.getPixel(0,0);

    for(unsigned int y = 0; y < size.y; ++y)
    {
        for(unsigned int x = 0; x < size.x; ++x)
        {
            collide_[x + width * y] = (t.getPixel(x,y) == collideColor);
        }
    }
}

// TODO: Make this make sense
CollisionData CollisionMap::getBallCollisionPoints(
        const tank::Vectorf& centre,
        float radius,
        const tank::Vectorf& dPos)
{
    //NB: Returns tuple of vector of tuples of vectors and floats and floats
    //No, but seriously, (vector((position, time)), time step)
    auto circleCentreTrajectory = getTrajectory(centre, dPos);

    //Retrieve the circle centres from the trajectory tuple clusterfuck
    std::vector<std::tuple<Point, float>> circleCentres =
        std::get<0>(circleCentreTrajectory);

    for (auto& currentCentre : circleCentres)
    {
        //For every circle centre, generate a circle mask to check against 
        std::vector<Point> circleToCheck =
            getCircleToCheck(std::get<0>(currentCentre), radius);

        //Remove any points that cannot be collisions
        circleToCheck.erase(std::remove_if(circleToCheck.begin(), circleToCheck.end(),
                    [this](Point const& point) {
                        return not collideAt(point.x, point.y);
                    }), circleToCheck.end());

        //If any points left, (collision points), return them in a tuple because
        //we FUCKING LOVE TUPLES.
        if (not circleToCheck.empty())
        {
            return CollisionData{circleToCheck,
                std::get<1>(currentCentre),
                std::get<1>(circleCentreTrajectory)};
        }
    }

    return CollisionData{std::vector<Point>(), 0.0f, 0.0f};
}

bool CollisionMap::collideAt(unsigned x, unsigned y) {
    if (x > width or y > height) 
        return true;
    return collide_[x + y * width];
}
