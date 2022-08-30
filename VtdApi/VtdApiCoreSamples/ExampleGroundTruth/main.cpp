#include "Mode1.h"

template<typename T>
void str2var (T &i, char const *s, int base = 0)
{
    char *end;
    long  l;
    errno = 0;
    l = strtol(s, &end, base);

    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
        std::cerr << "Overflow" << std::endl;

    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
        std::cerr << "Underflow" << std::endl;

    if (*s == '\0' || *end != '\0')
        std::cerr << "Inconvertible" << std::endl;

    i = static_cast<T>( l );
    std::cerr << "Success" << std::endl;
}

void Usage()
{

    printf("********************************************************************************\n");
    printf("***************************** Test Automation **********************************\n");
    printf("********************************************************************************\n");
    printf("*                                                                              *\n");
    printf("********************************************************************************\n");
    printf("*                                                                              *\n");
    printf("*    -configfile       : Path to config file                                   *\n");
    printf("*                                                                              *\n");
    printf("********************************************************************************\n");
    printf("***************************** Test Automation **********************************\n");
    printf("********************************************************************************\n");
    printf("\n");
}

int main(int argc, char** argv)
{
    std::string configFileName = "";
    int counter = 0;

    if (argc < 3)
    {
        Usage();
        return EXIT_FAILURE;
    }

    for(counter = 1; counter < argc; ++counter)
    {
        if (!strcmp("configfile", argv[counter]))
        {
            configFileName = argv[counter + 1];
            continue;
        }
    }

    Mode1 mode1(configFileName);
    mode1.readConfigFile();
    mode1.runMode1();
    return 0;
}
