#include "DataFilter.h"

#include <VtdToolkit/viRDBIcd.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

DataFilter::DataFilter()
{

}

DataFilter::~DataFilter()
{
}

void DataFilter::initFilter()
{
   for (unsigned int dataPackage = 1; dataPackage  < RDB_PKG_ID_SYMBOL_STATE; ++dataPackage)
        addFilter(dataPackage, false);

   for (unsigned int dataPackage = RDB_PKG_ID_CUSTOM_SCORING; dataPackage < RDB_PKG_ID_CUSTOM_LOOK_AHEAD; ++dataPackage)
        addFilter(dataPackage, false);

   for (unsigned int dataPackage = RDB_PKG_ID_CUSTOM_OPTIX_START; dataPackage <  RDB_PKG_ID_CUSTOM_USER_B_END; ++dataPackage)
        addFilter(dataPackage, false);
}

void DataFilter::addFilter(const unsigned int& packageData, bool isWrite)
{
       filter_.insert(std::pair<unsigned int, bool> (packageData, isWrite));
}

void DataFilter::changeFilter(const unsigned int& packageData, bool isWrite)
{
       filter_.find(packageData)->second = isWrite;
}

void DataFilter::writeAll()
{
    for (unsigned int dataPackage = 1; dataPackage < RDB_PKG_ID_SYMBOL_STATE; ++dataPackage)
         changeFilter(dataPackage, false);

    for (unsigned int dataPackage = RDB_PKG_ID_CUSTOM_SCORING; dataPackage < RDB_PKG_ID_CUSTOM_LOOK_AHEAD; ++dataPackage)
         changeFilter(dataPackage, false);

    for (unsigned int dataPackage = RDB_PKG_ID_CUSTOM_OPTIX_START; dataPackage  < RDB_PKG_ID_CUSTOM_USER_B_END; ++dataPackage)
         changeFilter(dataPackage, false);
}

void DataFilter::populateFilter(const std::string& filterParameters)
{
    initFilter();

    if (filterParameters == "all")
        writeAll();
    else if (filterParameters == "none")
        return;
    else
        getFilterData(filterParameters);
}

std::vector<std::string> DataFilter::getFilterData(const std::string& filterParameters)
{
    std::vector<std::string> vec;
    boost::algorithm::split(vec, filterParameters, boost::is_any_of(","));

    for (std::vector<std::string>::const_iterator itr = vec.begin(); itr != vec.end(); ++itr)
    {
        changeFilter(boost::lexical_cast<unsigned int>(*itr), true);
    }

    return vec;
}
