// https://www.youtube.com/watch?v=m-nmu-xYNZQ

/*
 *  Moves work as follows:
 *    north (^), south (v), east (>), or west (<).
 *  How many houses receive at least one present?
 *
 *  > delivers to 2 houses: 1 @ starting location, one to the east
 *  ^>v< devices 4 houses in a square: include twice to the start/end loc
 *  ^v^v^v^v^v delivers to only two houses
 */

/*
 *  Infinite two-dimensional grid is meant to throw you off
 *  You shouldn't even try to make an "infinite 2d" data structure
 *  Instead: build a hashmap of points
 *  You want something that can track things without needing boundaries
 *
 *  How many houses receive at least one present
 *  Translation: How many entries are in our hashmap
 */

#include <exception>
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>


struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

// first = x
// second = y;
typedef std::pair<int, int> Point;

int main() {
    std::string buffer;
    std::ifstream input_stream("input.txt");

    if (input_stream.is_open()) {
        input_stream >> buffer;
    }

    input_stream.close();

    Point current_position(0, 0);
    std::unordered_map<Point, int, pair_hash> houses_map;

    // starting house needs to be taken care of
    houses_map[Point(0, 0)] = 1;

    for (auto token : buffer) {
        switch(token) {
            case '<':
                current_position.first -= 1;
                break;
            case '>':
                current_position.first += 1;
                break;
            case '^':
                current_position.second += 1;
                break;
            case 'v':
                current_position.second -= 1;
                break;
            default:
                break;
        }

        // if we have visited the location before, increase visit number
        // otherwise, visit for first time
        houses_map.contains(current_position) ? houses_map[current_position]++ : houses_map[current_position] = 1;
    }

    std::cout << "Number of houses visited: " << std::to_string(houses_map.size()) << '\n';

    return 0;
}
