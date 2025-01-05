// #include "menu.h"
#include "calulate_postfix.h"
#include "converter.h"
#include "prefix.h"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{

     Calculate_postfix post;

    auto start = std::chrono::high_resolution_clock::now();

    // Call your function here
    post.postfix();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;  // Duration in seconds

    std::cout << "Execution time: " << elapsed.count() << " seconds." << std::endl;
    return 0;
}