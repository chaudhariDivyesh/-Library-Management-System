#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

/**
 * @brief Gets the current date and time as a formatted string.
 * @return A string representing the current date and time in the format "YYYY-MM-DD HH:MM:SS".
 */
string getCurrentDate();

/**
 * @brief Converts a `time_t` value to a formatted string.
 * @param t The time value to be converted.
 * @return A string representing the time in "YYYY-MM-DD HH:MM:SS" format. If `t` is 0, returns "N/A".
 */
string stringifyTime(time_t t);

/**
 * @brief Parses a date-time string into a `time_t` value.
 * @param timeStr The string to be converted, expected in "YYYY-MM-DD HH:MM:SS" format.
 * @return The corresponding `time_t` value, or 0 if parsing fails.
 */
time_t parseTimeString(const string& timeStr);

#endif
