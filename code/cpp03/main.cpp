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
struct Pos2d {
  Pos2d(float x, float y) : x(x), y(y) {}
  float x;
  float y;
};

std::ostream& operator<<(std::ostream& os, const Pos2d& point)
{
  os << "(" << point.x << ", " << point.y << ")";
  return os;
}


/**
 * Generate a Pos2d with x and y coordinates uniformly i.i.d.
 * in [-1, +1]
 */
Pos2d* RandomPos2d()
{
  Pos2d* new_point = new Pos2d(RandomNumber(), RandomNumber());
  std::cout << "New point " << *new_point << " created\n";
  return new_point;
}


float ManhattanToOrigin(Pos2d* point)
{
  return std::abs(point->x) + std::abs(point->y);
}


bool Pos2dIsNearOrigin(Pos2d* point)
{
  return (ManhattanToOrigin(point) < 0.5f);
}


Pos2d* NearestToOrigin(const std::vector<Pos2d*>& points,
                       float& min_distance)
{
  unsigned int min_index = 0;
  min_distance = std::numeric_limits<float>::max();
  for (unsigned int i = 0; i < points.size(); ++i)
  {
    if (ManhattanToOrigin(points[i]) < min_distance)
    {
      min_index = i;
      min_distance = ManhattanToOrigin(points[i]);
    }
  }

  return points[min_index];
}


int main()
{
  std::vector<Pos2d*> points;
  for (int i = 0; i < 100; ++i)
    points.push_back(RandomPos2d());

  int nearOrigin = 0;
  for (unsigned int i = 0; i < points.size(); ++i)
    if (Pos2dIsNearOrigin(points[i]))
      ++nearOrigin;

  std::cout << nearOrigin << " of " << points.size() 
            << " points are near the origin.\n";

  float min_distance;
  Pos2d* nearest_point = NearestToOrigin(points, min_distance);
  std::cout << "The nearest point was " << *nearest_point
            << " with distance " << min_distance << "\n";

  /// Tidy up
  for (unsigned int i = 0; i < points.size(); ++i)
    delete points[i];



  #if __cplusplus > 199711L
    std::cout << "Compiled using C++11 or later\n";
  #else
    std::cout << "Compiled using C++03 or earlier\n";
  #endif

  return EXIT_SUCCESS;
}


