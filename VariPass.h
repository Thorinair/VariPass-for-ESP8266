#ifndef VARIPASS

#define VARIPASS

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// Different results returned by the API methods.
#define VARIPASS_RESULT_ERROR_UNKNOWN        -1
#define VARIPASS_RESULT_SUCCESS              0
#define VARIPASS_RESULT_ERROR_INVALID_KEY    1
#define VARIPASS_RESULT_ERROR_INVALID_ID     2
#define VARIPASS_RESULT_ERROR_COOLDOWN       3
#define VARIPASS_RESULT_ERROR_UNCONFIRMED    4
#define VARIPASS_RESULT_ERROR_BANNED         5
#define VARIPASS_RESULT_ERROR_EMPTY_VARIABLE 6
#define VARIPASS_RESULT_ERROR_DB             7
#define VARIPASS_RESULT_ERROR_WIFI           8
#define VARIPASS_RESULT_ERROR_CONNECT        9

/*
 * Structure which defines a variable as returned by the varipassLatest function.
 *
 * id:     ID of the variable.
 * value:  Value of the variable. The value is always of String type. 
 *         Tt is up to the user to parse it.
 */
typedef struct Variable {
    char id[9];
    char value[256];
} Variable;

/*
 * Functions used to send data to VariPass.
 *
 * key:    User's API key which can be found on the website.
 * id:     ID of the variable to be written to.
 * value:  Value to write. Different types depending on function.
 * result: Reference to a result variable. Used to save the API results.
 */
void varipassWriteInt   (String key, String id, long   value, int* result);
void varipassWriteFloat (String key, String id, double value, int* result, char decimals = 2);
void varipassWriteBool  (String key, String id, bool   value, int* result);
void varipassWriteString(String key, String id, String value, int* result);

/*
 * Functions used to read data from VariPass.
 *
 * key:    User's API key which can be found on the website.
 * id:     ID of the variable to be written to.
 * result: Reference to a result variable. Used to save the API results.
 *
 * return: Value from VariPass. Different types depending on function.
 */
long   varipassReadInt   (String key, String id, int* result);
double varipassReadFloat (String key, String id, int* result);
bool   varipassReadBool  (String key, String id, int* result);
String varipassReadString(String key, String id, int* result);

/*
 * Function used to return all latest data from VariPass.
 *
 * key:    User's API key which can be found on the website.
 * count:  Reference to a count variable. Stores the number of variables that were returned. 
 *         Zero on error result.
 * result: Reference to a result variable. Used to save the API results.
 *
 * return: Pointer to an array of variable data. Will return null on error result.
 *         WARNING: To avoid memory leaks, call free() after you are done using the data.
 */
Variable * varipassLatest(String key, int* count, int* result);

/*
 * Translates a certain API response to a readable description.
 *
 * result: The integer result to retrieve the string for.
 *
 * return: A descriptive string of an API result.
 */
String varipassGetResultDescription(int result);

#endif
