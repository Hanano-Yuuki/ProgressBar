main: example.cpp include/ProgressBar.hpp
	g++ -I./include -std=c++17 -g -fopenmp example.cpp -o main