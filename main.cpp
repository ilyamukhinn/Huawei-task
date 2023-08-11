#include <time.h>
#include <vector>
#include <iostream>
#include <functional>
#include <fstream>
#include <iomanip>

struct df {
	long seconds;
	long nanoseconds;
};

std::pair<int,int> one_cycle_min_max(const std::vector<int>& array) {
	int min = array[0];
	int max = array[0];
	
	for (const int& num : array) {
		if (max < num) {
			max = num;
		}
		if (min > num) {
			min = num;
		}
	}

	return {min, max};
}

std::pair<int,int> two_cycles_min_max(const std::vector<int>& array) {
	int min = array[0];
	int max = array[0];
	
	for (const int& num : array) {
		if (min > num) {
			min = num;
		}
	}
	
	for (const int& num : array) {
		if (max < num) {
			max = num;
		}
	}
	
	return {min, max};
}

df process_with_timechecking(
	std::function<std::pair<int, int>(const std::vector<int>&)> func, 
	const std::vector<int>& array) {
	struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    std::pair<int, int> min_max_pair = func(array);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;

    if (nanoseconds < 0) {
        seconds--;
        nanoseconds += 1000000000L;
    }

	std::cout << "Time difference: " << seconds << "." << 
		std::setfill('0') << std::setw(9) << nanoseconds << 
		" seconds" << std::endl;
	std::cout << "min: " << min_max_pair.first << 
		", max: " << min_max_pair.second << std::endl;

	return {seconds, nanoseconds};
}

int main(int argc, char* argv[]) {
	std::vector<int> array(100000000, 0);
	for (int i = 0; i < 100000000; ++i) {
		array[i] = rand() % 11 - 5;
	}

	std::ofstream data_file;
	data_file.open("data.csv", std::ios::out | std::ios::app);
	
	if (data_file.is_open()) {
		df result = process_with_timechecking(&one_cycle_min_max, array);
		data_file << result.seconds << "." << 
			std::setfill('0') << std::setw(9) << result.nanoseconds << ",";
		result = process_with_timechecking(&two_cycles_min_max, array);
		data_file << result.seconds << "." << 
			std::setfill('0') << std::setw(9) <<result.nanoseconds << "\n";
		data_file.close();
	}
	
	return 0;
}