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

std::vector<df> one_cycle_min_max_with_timechecking(const std::vector<int>& array) {
	int min = array[0];
	int max = array[0];

	std::vector<df> result;

	struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	for (int i = 0; i < array.size(); ++i) {
		if (max < array[i]) {
			max = array[i];
		}
		if (min > array[i]) {
			min = array[i];
		}

		if ((i + 1) % (array.size() / 10) == 0) {
			clock_gettime(CLOCK_MONOTONIC_RAW, &end);

			long seconds = end.tv_sec - start.tv_sec;
			long nanoseconds = end.tv_nsec - start.tv_nsec;

			if (nanoseconds < 0) {
				seconds--;
				nanoseconds += 1000000000L;
			}

			result.push_back({seconds, nanoseconds});

			clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		}
	}

	return result;
}

std::vector<df> two_cycles_min_max_with_timechecking(const std::vector<int>& array) {
	int min = array[0];
	int max = array[0];
	
	std::vector<df> result;

	struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	for (int i = 0; i < array.size(); ++i) {
		if (min > array[i]) {
			min = array[i];
		}
		
		if ((i + 1) % (array.size() / 10) == 0) {
			clock_gettime(CLOCK_MONOTONIC_RAW, &end);

			long seconds = end.tv_sec - start.tv_sec;
			long nanoseconds = end.tv_nsec - start.tv_nsec;

			if (nanoseconds < 0) {
				seconds--;
				nanoseconds += 1000000000L;
			}

			result.push_back({seconds, nanoseconds});

			clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		}
	}
	
	for (int i = 0; i < array.size(); ++i) {
		if (max < array[i]) {
			max = array[i];
		}

		if ((i + 1) % (array.size() / 10) == 0) {
			clock_gettime(CLOCK_MONOTONIC_RAW, &end);

			long seconds = end.tv_sec - start.tv_sec;
			long nanoseconds = end.tv_nsec - start.tv_nsec;

			if (nanoseconds < 0) {
				seconds--;
				nanoseconds += 1000000000L;
			}

			result.push_back({seconds, nanoseconds});

			clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		}
	}

	return result;
}

int main(int argc, char* argv[]) {
	std::vector<int> array(100000000, 0);
	for (int i = 0; i < 100000000; ++i) {
		array[i] = rand() % 11 - 5;
	}

	std::ofstream steps_data_file;
	steps_data_file.open("steps_data.csv", std::ios::out | std::ios::app);
	
	if (steps_data_file.is_open()) {
		std::vector<df> result = one_cycle_min_max_with_timechecking(array);
		for (const df& r : result) {
			steps_data_file << r.seconds << "." << 
				std::setfill('0') << std::setw(9) << r.nanoseconds << ",";
		}

		steps_data_file << "\n";
		result = two_cycles_min_max_with_timechecking(array);

		for (const df& r : result) {
			steps_data_file << r.seconds << "." << 
				std::setfill('0') << std::setw(9) << r.nanoseconds << ",";
		}

		steps_data_file << "\n\n";

		steps_data_file.close();
	}
	
	return 0;
}