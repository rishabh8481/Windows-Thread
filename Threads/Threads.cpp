// Threads.cpp : Defines the entry point for the console application.
//
/*
* Aim: - To study and analysze the behaviour of different type of threads in multitheaded environment
* Developed By: - Rishabh Sharma (109874160) & Meet Shah (109875889)
* Programming Assignment: - 2
* Subject: - CSCI 244, Operating System
* Programming Language Used:- C
* Compiler: - Visual Studio c++ compiler : - Visual C++ 2015
* Ide used: - Visual Studio
* Input/Output :- File and console
* Output content: - Time taken by different threads for performing the assigned task
*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <windows.h>
#include <chrono>                         //C++11
// Total Number of threads executed at a time
#define MAX_THREAD 2
using namespace std;
using namespace std::chrono;
vector <string> line_array;
int random_value[5000];
vector <string> line_array1;
int random_value1[5000];
// vector variable store different threads priority
vector <DWORD> thread_priority;
// vector variable store different threads class
vector <DWORD> thread_class;
// file containing the output of the program
ofstream result_file("result.txt");


// function description: - perform file read operation and store the file content to a global variable line_array
void fileread() {
	string line;
	ifstream my_file("file_for_reading.txt");
	if (my_file.is_open()) {
		while (getline(my_file, line)) {
			line_array.push_back(line);
		}
		my_file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}
// function description: - perform file write operation and load the line_array content in file_for_writing.txt file
void filewrite() {
	int i = 0;
	string line;
	ofstream my_file("file_for_writing.txt");
	if (my_file.is_open())
	{
		while (!line_array.empty()) {
			line = line_array.back();
			line_array.pop_back();
			my_file << line << endl;
		}
		my_file.close();
	}
	else cout << "Unable to open file";
}
// function description: - fucntion will call file_read and file_write fucntion for performing I/O intensive task
// in a loop for 25 times. Calculate the time taken for completion of I/O task.
DWORD WINAPI file_opeation(LPVOID lpParam) {
	cout << "file operation begins..." << endl;
	result_file << "file operation begins..." << endl;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int k = 0; k < 25; k++) {
		fileread();
		filewrite();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "file operations ends..." << duration << endl;
	result_file << "file operations ends..." << duration << endl;
	return 0;
}
//function description: - perform swaping operation on two variable to swap their data.
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
//function description: - create the array of 5000 random numbers and perform bubble sort operation (CPU intensive) on the array.
// bubble sort operation is performed 500 times on the array. In time taken by the sorting fucntion is calculated and stored in output file.
DWORD WINAPI sorting(LPVOID lpParam) {
	int i, j;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	srand(time(NULL));
	cout << "sorting begin..." << endl;
	result_file << "sorting begins..." << endl;
	for (unsigned int i = 1; i < 5000; i++) {
		random_value[i] = rand();
	}
	//sorting one array 5000 times
	for (int k = 0; k < 500; k++) {
		for (i = 0; i < 5000 - 1; i++) {
			// Last i elements are already in place
			for (j = 0; j < 5000 - i - 1; j++) {
				if (random_value[j] > random_value[j + 1]) {
					swap(&random_value[j], &random_value[j + 1]);
				}
			}
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "sorting ends..." << duration << endl;
	result_file << "sorting ends..." << duration << endl;
	return 0;
}
/****************************************************************************/
// function description: - perform file read operation and store the file content to a global variable line_array
void fileread1() {
	string line;
	ifstream my_file("file_for_reading1.txt");
	if (my_file.is_open()) {
		//cout << "reading file..." << endl;
		while (getline(my_file, line)) {
			line_array1.push_back(line);
		}
		//cout << "file reading complete..." << endl;
		my_file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}
// function description: - perform file write operation and load the line_array content in file_for_writing1.txt file
void filewrite1() {
	int i = 0;
	string line;
	ofstream my_file("file_for_writing1.txt");
	if (my_file.is_open())
	{
		// cout << "writing a file..." << endl;
		while (!line_array1.empty()) {
			line = line_array1.back();
			line_array1.pop_back();
			my_file << line << endl;
		}
		my_file.close();
		// cout << "writing file complete..." << endl;
	}
	else cout << "Unable to open file";
}
// function description: - fucntion will call file_read and file_write fucntion for performing I/O intensive task
// in a loop for 25 times. Calculate the time taken for completion of I/O task.
DWORD WINAPI file_opeation1(LPVOID lpParam) {
	//reading writing 50 times each
	cout << "file operation begins1..." << endl;
	result_file << "file operation begins1..." << endl;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int k = 0; k < 25; k++) {
		fileread1();
		filewrite1();
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "file operations ends1..." << duration << endl;
	result_file << "file operations ends1..." << duration << endl;
	return 0;
}
//function description: - perform swaping operation on two variable to swap their data.
void swap1(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
//function description: - create the array of 5000 random numbers and perform bubble sort operation (CPU intensive) on the array.
// bubble sort operation is performed 500 times on the array. In time taken by the sorting fucntion is calculated and stored in output file.
DWORD WINAPI sorting1(LPVOID lpParam) {
	int i, j;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	srand(time(NULL));
	cout << "sorting begin1..." << endl;
	result_file << "sorting begins1..." << endl;
	for (unsigned int i = 1; i < 5000; i++) {
		random_value1[i] = rand();
	}
	//sorting one array 5000 times
	for (int k = 0; k < 500; k++) {
		for (i = 0; i < 5000 - 1; i++) {
			// Last i elements are already in place
			for (j = 0; j < 5000 - i - 1; j++) {
				if (random_value1[j] > random_value1[j + 1]) {
					swap1(&random_value1[j], &random_value1[j + 1]);
				}
			}
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "sorting ends1..." << duration << endl;
	result_file << "sorting ends1..." << duration << endl;
	return 0;
}
/*****************************************************************************/
/* function description: - 4 thread handlers are created for performing the following task
Thread A = TA1, TA2
Thread B = TB1, TB2
for core affinity we selected 2 cores
Core 1
Core 2
For each couple (priority, class) {
we calculate time for Thread A and Thread B when executed in the following order:
TA1 + TA2
TB1 + TB2
TA1 + TB1
}
time taken by the threads is stored in result.txt file
For each couple (priority, class) {
TA1 Core 1 + TA2 Core 1
TA1 Core 1 + TA2 Core 2
TB1 Core 1 + TB2 Core 1
TB1 Core 1 + TB2 Core 2
TA1 Core 1 + TB2 Core 1
TA1 Core 1 + TB2 Core 2
}
time taken by the threads is stored in result.txt file
*/
int main() {
	// thread TA, TB
	HANDLE cpuThread, fileThread;
	// thread TA1, TB1
	HANDLE cpuThread1, fileThread1;
	// identifier for threads
	DWORD cpuThreadIdentifier, fileThreadIdentifier;
	DWORD cpuThreadIdentifier1, fileThreadIdentifier1;
	int temp;
	DWORD dwError, dwPriClass;
	// Classes of threads that are been tested
	thread_class.push_back(IDLE_PRIORITY_CLASS);
	thread_class.push_back(BELOW_NORMAL_PRIORITY_CLASS);
	thread_class.push_back(NORMAL_PRIORITY_CLASS);
	thread_class.push_back(ABOVE_NORMAL_PRIORITY_CLASS);
	thread_class.push_back(HIGH_PRIORITY_CLASS);
	thread_class.push_back(REALTIME_PRIORITY_CLASS);
	// Priority of threads that are been tested
	thread_priority.push_back(THREAD_PRIORITY_LOWEST);
	thread_priority.push_back(THREAD_PRIORITY_NORMAL);
	thread_priority.push_back(THREAD_PRIORITY_HIGHEST);
	thread_priority.push_back(THREAD_PRIORITY_TIME_CRITICAL);
	result_file << endl << endl << endl << endl;
	result_file << "TA C1 + TB C2" << endl;
	// TA C1 + TB C2
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "File priority: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "CPU priority: -" << thread_priority.at(j) << endl;
			cout << "CPU priority: -" << thread_priority.at(j) << endl;
			cout << "File priority: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// cpu task
			cpuThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier); // returns the thread identifier
			SetThreadPriority(cpuThread, thread_priority.at(j));
			SetThreadAffinityMask(cpuThread, 1);
			// file task
			fileThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier); // returns the thread identifier
			SetThreadPriority(fileThread, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(fileThread, 2);
			// Wait until all threads have terminated.
			WaitForSingleObject(fileThread, INFINITE);
			WaitForSingleObject(cpuThread, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	result_file << "TA C1 + TB C1" << endl;

	// TA C1 + TB C1
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "File priority: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "CPU priority: -" << thread_priority.at(j) << endl;
			cout << "CPU priority: -" << thread_priority.at(j) << endl;
			cout << "File priority: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// cpu task
			cpuThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier); // returns the thread identifier
			SetThreadPriority(cpuThread, thread_priority.at(j));
			SetThreadAffinityMask(cpuThread, 1);
			// file task
			fileThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier); // returns the thread identifier
			SetThreadPriority(fileThread, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(fileThread, 1);
			// Wait until all threads have terminated.
			WaitForSingleObject(fileThread, INFINITE);
			WaitForSingleObject(cpuThread, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	result_file << "TA C1 + TA C2" << endl;


	// TA C1 + TA C2
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "CPU priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "CPU priority0: -" << thread_priority.at(j) << endl;
			cout << "CPU priority0: -" << thread_priority.at(j) << endl;
			cout << "CPU priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// cpu task 0
			cpuThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier); // returns the thread identifier
			SetThreadPriority(cpuThread, thread_priority.at(j));
			SetThreadAffinityMask(cpuThread, 1);
			// cpu task 1
			cpuThread1 = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting1, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier1); // returns the thread identifier
			SetThreadPriority(cpuThread1, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(cpuThread1, 2);
			// Wait until all threads have terminated.
			WaitForSingleObject(cpuThread, INFINITE);
			WaitForSingleObject(cpuThread1, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	result_file << "TA C1 + TA C1" << endl;
	// TA C1 + TA C1
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "CPU priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "CPU priority0: -" << thread_priority.at(j) << endl;
			cout << "CPU priority0: -" << thread_priority.at(j) << endl;
			cout << "CPU priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// cpu task 0
			cpuThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier); // returns the thread identifier
			SetThreadPriority(cpuThread, thread_priority.at(j));
			SetThreadAffinityMask(cpuThread, 1);
			// cpu task 1
			cpuThread1 = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				sorting1, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&cpuThreadIdentifier1); // returns the thread identifier
			SetThreadPriority(cpuThread1, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(cpuThread1, 1);
			// Wait until all threads have terminated.
			WaitForSingleObject(cpuThread, INFINITE);
			WaitForSingleObject(cpuThread1, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	// TB C1 + TB C2
	result_file << "TB C1 + TB C2" << endl;
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "File priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "File priority0: -" << thread_priority.at(j) << endl;
			cout << "File priority0: -" << thread_priority.at(j) << endl;
			cout << "File priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// file task0
			fileThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier); // returns the thread identifier
			SetThreadPriority(fileThread, thread_priority.at(j));
			SetThreadAffinityMask(fileThread, 1);
			// file task1
			fileThread1 = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation1, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier1); // returns the thread identifier
			SetThreadPriority(fileThread1, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(fileThread1, 2);
			// Wait until all threads have terminated.
			WaitForSingleObject(fileThread, INFINITE);
			WaitForSingleObject(fileThread1, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	//TB C1 + TB C1
	result_file << "TB C1 + TB C1" << endl;
	for (int i = 0; i < thread_class.size(); i++) {
		result_file << "Changing Process priority to : - " << thread_class.at(i) << endl;
		cout << "Changing Process priority to : - " << thread_class.at(i) << endl;
		if (!SetPriorityClass(GetCurrentProcess(), thread_class.at(i)))
		{
			dwError = GetLastError();
			_tprintf(TEXT("Failed to change priority (%d)\n"), dwError);
		}
		dwPriClass = GetPriorityClass(GetCurrentProcess());
		_tprintf(TEXT("Current priority class is 0x%x\n"), dwPriClass);
		for (int j = 0; j < thread_priority.size(); j++) {
			result_file << "File priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			result_file << "File priority0: -" << thread_priority.at(j) << endl;
			cout << "File priority0: -" << thread_priority.at(j) << endl;
			cout << "File priority1: -" << thread_priority.at(thread_priority.size() - j - 1) << endl;
			// file task0
			fileThread = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier); // returns the thread identifier
			SetThreadPriority(fileThread, thread_priority.at(j));
			SetThreadAffinityMask(fileThread, 1);
			// file task1
			fileThread1 = CreateThread(
				NULL, // default security attributes
				0, // use default stack size
				file_opeation1, // thread function name
				NULL, // argument to thread function
				0, // use default creation flags
				&fileThreadIdentifier1); // returns the thread identifier
			SetThreadPriority(fileThread1, thread_priority.at(thread_priority.size() - j - 1));
			SetThreadAffinityMask(fileThread1, 1);
			// Wait until all threads have terminated.
			WaitForSingleObject(fileThread, INFINITE);
			WaitForSingleObject(fileThread1, INFINITE);
		}
	}
	result_file << endl << endl << endl << endl;
	cin >> temp;
	return 0;
}
