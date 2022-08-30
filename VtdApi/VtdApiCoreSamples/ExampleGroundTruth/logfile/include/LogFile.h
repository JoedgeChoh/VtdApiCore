#ifndef  LOG_FILE_H
#define  LOG_FILE_H

#include <stdio.h>

#include "Singletons.h"

#define MAX_BUFFER 1024 // Maximal siye of buffer
#define L_FAIL false // func succesfull
#define L_OK true // func unseccesfull
#define g_pLogFile CLogFile::Get() // Makro for simplier use
// colors could be extended
enum FONTCOLORS
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	PURPLE
};

/**
 * @brief The CLogFile class for logging data
 */
class CLogFile : public Singletons<CLogFile> 
{
public:
    /**
     * @brief CLogFile - constructor
     */
	CLogFile();
	
    /**
      * @brief ~CLogFile - destructor
      */
    ~CLogFile();

    /**
     * @brief createLogFile - create file
     * @param logName - file name
     */
	void createLogFile(const char* logName);

    /**
     * @brief writeTopic - write topic
     * @param topic - topic name
     * @param size - font size
     */
	void writeTopic(const char* topic, int size);

    /**
     * @brief textOut - write text
     * @param text - text to be write
     */
	void textOut(const char* text);

    /**
     * @brief textOut - write text
     * @param color - color
     * @param text - text to be write
     */
	void textOut(int color, const char* text);

    /**
     * @brief textOut - write text
     * @param color - text color
     * @param list - list or not
     * @param text - text to be write
     */
	void textOut(int color, bool list, const char* text);

    /**
     * @brief fTextOut - write text
     * @param text - paramters
     * @param ... - data to be written
     */
	void fTextOut(const char* text, ...);

    /**
     * @brief fTextOut - write text
     * @param text - paramters
     * @param ... - data to be written
     * @param color - text color
     */
	void fTextOut(int color, const char* text, ...);

    /**
     * @brief fTextOut - write text
     * @param text - paramters
     * @param ... - data to be written
     * @param color - text color
     * @param list - true or not
     */
	void fTextOut(int color, bool list, const char* text, ...);

    /**
     * @brief functionResult -
     * @param name -
     * @param result - true or not if function succes
     */
	void functionResult(const char* name, bool result);

private:
	FILE* logFile_;
};

#endif //LOG_FILE_H
