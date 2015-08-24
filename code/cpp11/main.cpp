/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2015 Nikolaus Mayer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <cmath>     // std::fabs
#include <cstdlib>   // EXIT_SUCCESS
#include <iostream>
#include <limits>    // std::numeric_limits
#include <memory>
#include <vector>
#if __cplusplus > 199711L
  #include <random>  // std::random_device, std::mt19937, ...
#else
  #include <ctime>
#endif


/**
 * Generate a uniformly random number in [-1, +1]
 *
 * This function is irrelevant for the hands-on exercises, but
 * is a good example for random number generation in C++11
 */
float RandomNumber()
{
  #if __cplusplus > 199711L
    /// Raw randomness
    static std::random_device randdev;
    /// Mersenne Twister engine for high quality randomness
    static std::mt19937 mersenne(randdev());
    /// Uniform distribution [-1, +1]
    static std::uniform_real_distribution<float> uniform(-1.f, 1.f);

    return uniform(mersenne);
  #else
    /// Seed PRNG on first run
    static bool firstrun=true;
    if (firstrun) {
      firstrun = false;
      srand(time(NULL));
    }

    return 2.f*(rand()/(float)RAND_MAX)-1.f;
  #endif
}



/////////////////////////////////////////////////////////////////////
/// Hands-on part
/////////////////////////////////////////////////////////////////////

/**
 * A point in 2d space
 */
struct Point {
  Point(float x, float y) : x{x}, y{y} {}
  float x;
  float y;
};
typedef std::shared_ptr<Point> Point_ptr;
typedef std::shared_ptr<const Point> Point_cptr;

std::ostream& operator<<(std::ostream& os, const Point& point)
{
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}


/**
 * Generate a Point with x and y coordinates uniformly i.i.d.
 * in [-1, +1]
 */
Point_ptr RandomPoint()
{
  auto new_point = std::make_shared<Point>(RandomNumber(), RandomNumber());
  std::cout << "New point " << *new_point << " created\n";
  return new_point;
}


float ManhattanToOrigin(Point_cptr point)
{
  return std::fabs(point->x) + std::fabs(point->y);
}



std::tuple<Point_cptr, float> NearestToOrigin(
                          const std::vector<Point_ptr>& points
                                             )
{
  Point_cptr min_point{nullptr};
  float min_distance = std::numeric_limits<float>::max();
  for (auto point: points)
  {
    if (ManhattanToOrigin(point) < min_distance)
    {
      min_point = point;
      min_distance = ManhattanToOrigin(point);
    }
  }

  return std::make_tuple(min_point, min_distance);
}


int main()
{
  std::vector<Point_ptr> points;
  for (int i = 0; i < 100; ++i)
    points.push_back(RandomPoint());

  auto PointIsNearOrigin = [](Point_cptr point) -> bool
  {
    return (ManhattanToOrigin(point) < 0.5f);
  };


  int nearOrigin = 0;
  for (auto point: points)
    if (PointIsNearOrigin(point))
      ++nearOrigin;

  std::cout << nearOrigin << " of " << points.size() 
            << " points are near the origin.\n";

  Point_cptr nearest_point;
  float min_distance;
  std::tie(nearest_point, min_distance) = NearestToOrigin(points);
  std::cout << "The nearest point was " << *nearest_point
            << " with distance " << min_distance << "\n";


  #if __cplusplus > 199711L
    std::cout << "Compiled using C++11 or later\n";
  #else
    std::cout << "Compiled using C++03 or earlier\n";
  #endif

  return EXIT_SUCCESS;
}


