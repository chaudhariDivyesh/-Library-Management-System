#include "Utils.h"

/**
 * @brief Retrieves the current date and time in a human-readable format.
 * 
 * This function fetches the current system time, converts it into local time, and formats it
 * into the string format "YYYY-MM-DD HH:MM:SS".
 * 
 * @return A string containing the formatted current date and time.
 */
string getCurrentDate() {
    time_t now = system_clock::to_time_t(system_clock::now());  // Get current time
    tm* localTime = localtime(&now);  // Convert to local time structure
    char buffer[20];  // Buffer to hold formatted time string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);  // Format time
    return string(buffer);
}

/**
 * @brief Converts a `time_t` value to a human-readable date-time string.
 * 
 * If the given time value is 0, it returns "N/A". Otherwise, it converts the time into
 * a formatted string "YYYY-MM-DD HH:MM:SS".
 * 
 * @param t The time value to convert.
 * @return A string representing the formatted date-time.
 */
string stringifyTime(time_t t) {
    if (t == 0) return "N/A";  // Return "N/A" for uninitialized or invalid times
    
    char buffer[20];  // Buffer to hold formatted time string
    tm* localTime = localtime(&t);  // Convert to local time structure
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);  // Format time
    return string(buffer);
}

/**
 * @brief Converts a date-time string into a `time_t` value.
 * 
 * This function takes a string in the format "YYYY-MM-DD HH:MM:SS" and converts it into
 * a `time_t` value representing that date-time. If the input is invalid or empty,
 * it returns 0.
 * 
 * @param timeStr The string representing the date-time to parse.
 * @return The corresponding `time_t` value, or 0 if parsing fails.
 */
time_t parseTimeString(const string& timeStr) {
    if (timeStr == "N/A" || timeStr.empty()) return 0;  // Return 0 for invalid or empty input
    
    struct tm tmStruct = {};  // Initialize all fields to zero
    istringstream ss(timeStr);  // Create an input string stream
    ss >> get_time(&tmStruct, "%Y-%m-%d %H:%M:%S");  // Parse the date-time format

    if (ss.fail()) {
        cerr << "Error: Invalid time format: " << timeStr << "\n";  // Print error if parsing fails
        return 0;
    }
    
    return mktime(&tmStruct);  // Convert `tm` structure to `time_t`
}
