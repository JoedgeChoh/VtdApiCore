#include "LogFile.h"
#include <stdarg.h>
#include <stdio.h>
#include <ctime>

CLogFile::CLogFile()
{

}

CLogFile::~CLogFile()
{
	// End of log file and close of the file
	textOut("<br><br>End of Log File</font></body></html>");
	fclose(logFile_);
}

void CLogFile::createLogFile(const char* logName)
{
    logFile_ = fopen(logName, "w");
    textOut("<html><head><title>Log File</title><head/>");
	textOut("<body><font face='courier new'>");
    writeTopic("VTD software funcionality test", 4);
    std::time_t startTime = std::time(0);
    char* start = std::ctime(&startTime);
    writeTopic(start, 2);
#ifdef DEBUG
    textOut("BUILD: DEBUG<br>");
#else 
    textOut("BUILD: RELEASE<br>");
#endif // DEBUG

	// Link for email adrese
    textOut("<a href='mailto:vires@vires.com?subject=LogFile'>");
    textOut("Send E-Mail to VIRES Simulationstechnologie GmbH </a><br><br>");
	// Close log file and with append open
	fclose(logFile_);
    logFile_ = fopen(logName, "a");
}
	 
void CLogFile::writeTopic(const char* topic, int size) 
{
	textOut("<table cellspacing='0' cellpadding='0' width='100%%' ");
	textOut("bgcolor='#DFDFE5'>\n<tr>\n<td>\n<font face='arial' ");
	fTextOut("size='+%i'>\n", size);
	textOut(topic);
	textOut("</font>\n</td>\n</tr>\n</table>\n<br>");
	fflush(logFile_);

}

void CLogFile::textOut(const char* text)
{
	fprintf(logFile_, text);
	fflush(logFile_);
}

void CLogFile::textOut(int color, const char* text)
{
	textOut(color, false, text);
}

void CLogFile::textOut(int color, bool list, const char* text)
{
	if (list == L_OK)
	{
		textOut("<li>");
	}

	switch (color)
	{
	case BLACK:
		textOut("<font color=black>");
		break;

	case RED:
		textOut("<font color=red>");
		break;

	case GREEN:
		textOut("<font color=green>");
		break;

	case BLUE:
		textOut("<font color=blue>");
		break;
		
	case PURPLE:
		textOut("<font color=purple>");
		break;
		
	default:
		break;
	}

	textOut(text);
	textOut("</font>");
	if (list == L_FAIL)
	{
		textOut("<br>");
	}
	else
	{
		textOut("</li>");
	}
}

void CLogFile::fTextOut(const char* text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;
	va_start(pArgList, text);
    vsnprintf(buffer, MAX_BUFFER, text, pArgList);
	va_end(pArgList);
	textOut(buffer);
} // black color

void CLogFile::fTextOut(int color, const char* text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;
	va_start(pArgList, text);
    vsnprintf(buffer, MAX_BUFFER, text, pArgList);
	va_end(pArgList);
	textOut(color, buffer);
}// color text out

void CLogFile::fTextOut(int color, bool list, const char* text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;
	va_start(pArgList, text);
    vsnprintf(buffer, MAX_BUFFER, text, pArgList);
	va_end(pArgList);
	textOut(color, list, buffer);
}// color text out

void CLogFile::functionResult(const char* name, bool result)
{
	if (L_OK == result)
	{
		textOut("<table width='100%%' cellSpacing='1' cellPadding='5'");
		textOut("border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextOut("'#FFFFFF' width=35%%>%s</TD>", name);
		textOut("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		textOut("'green'>OK</FONT></TD><td bgcolor='#FFFFFF' ");
		textOut("width='30%%'>-/-</TD></tr></table>");
	}
	else
	{
		textOut("<table width='100%%' cellSpacing='1' cellPadding='5'");
		textOut("border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextOut("'#FFFFFF' width=35%%>%s</TD>", name);
		textOut("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		textOut("'green'>ERROR</FONT></TD><td bgcolor='#FFFFFF' ");
		textOut("width='30%%'>-/-</TD></tr></table>");
	}
}
