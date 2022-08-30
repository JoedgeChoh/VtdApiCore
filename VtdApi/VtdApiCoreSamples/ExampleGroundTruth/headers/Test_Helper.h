#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H

#include "LogFile.h"

#include <string>

namespace test_helper
{
        void exitTest(const std::string& reasonForExit, bool verbose)
        {
            std::cout << reasonForExit << " " << std::endl;
            std::cout << "EXIT::TEST:: TEST UNSUCCESSFULLY FINISHED \n";

            if (verbose)
            {
                 g_pLogFile->textOut(BLUE, true, reasonForExit.c_str());
                 g_pLogFile->textOut(RED, true, "EXIT::TEST::TEST UNSUCCESSFULLY FINISHED");
            }

            exit(2);
        }

        void exitTest(const std::string& reasonForExit, const std::string& path, bool verbose)
        {
            std::cout << reasonForExit << " " << path << std::endl;
            std::cout << "EXIT::TEST:: TEST UNSUCCESSFULLY FINISHED \n";

            if (verbose)
            {
                 g_pLogFile->fTextOut(BLUE, true, "%s %s", reasonForExit.c_str(), path.c_str());
                 g_pLogFile->textOut(RED, true, "EXIT::TEST::TEST UNSUCCESSFULLY FINISHED");
            }

            exit(2);
        }

        
        template<typename T>
        void hex2int(T& x, const char* str)
        {
            std::stringstream ss;
            ss << std::hex << str;
            ss >> x;
        }

        template <typename T>
        void str2var (T& num, const char* str)
        {
            std::istringstream ss(str);
            ss >> num;
         }
        
        bool XOR(bool a, bool b)
        {
            return (a + b) % 2;
        }
        
        template<typename T>
        void SecDelay(T seconds)
        {
            boost::this_thread::sleep_for(boost::chrono::microseconds(boost::numeric_cast<unsigned long>(seconds * 1000000.0)));
        }
}


#endif // _EXIT_TEST_H
