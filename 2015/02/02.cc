/*
 *  GETTING LINE BY LINE CALCULATIONS
 *  1. Get line count of file
 *  2. Write a for loop which iterates through the file
 *  3. For every line in the file, remove 'x'
 *  3a. For every digit in the line, run: (2*L*W) + (2*W*H) + (2*H*L)
 *  4. Add sum to total sum
 *  5. Return total sum
 */


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

/*
 *  Get smallest two digits
 *  Then calculate smallest perimeter + cubic area
 *  ex. 2(a + b) + (a*b*c)
 */
int ribbonCalculation(std::string line) {
    int sum{};
    int area{};
    int perimeter{};

    // replace 'x' in string so istringstream can parse
    std::replace( line.begin(), line.end(), 'x', ' ');
    std::stringstream is(line);

    int num{};

    std::vector<int> v;
    while ( is >> num )
        v.push_back( num );

    std::sort(v.begin(), v.end());

    area = v[0] * v[1] * v[2];
    perimeter = v[0] + v[0] + v[1] + v[1];

    sum = area + perimeter;
    return sum;
}

int paperCalculation(std::string line) {
    // dimensions of prism
    int length{};
    int width{};
    int height{};

    // sides
    int a{};
    int b{};
    int c{};
    int smallest{};

    // sum of surface area + remaining paper
    int sum{};

    // replace 'x' in string so istringstream can parse
    std::replace( line.begin(), line.end(), 'x', ' ');
    std::istringstream is(line);

    while ( is >> length >> width >> height) {
        a = length*width;
        b = width*height;
        c = height*length;

        smallest = std::min({a, b, c});

        sum = (2*length*width) + (2*width*height) + (2*height*length) + smallest;
    }


    return sum;
}

int main() {
    int wrappingPaperSum{};
    int ribbonSum{};

    std::ifstream inputFile("input.txt");

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            wrappingPaperSum += paperCalculation(line);
            ribbonSum += ribbonCalculation(line);
        }
    }

    std::cout << "Total wrapping paper: " << wrappingPaperSum <<'\n';
    std::cout << "Total ribbon: " << ribbonSum << '\n';
}
