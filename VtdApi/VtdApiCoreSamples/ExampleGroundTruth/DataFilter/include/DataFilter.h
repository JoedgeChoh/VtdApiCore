#ifndef  _DATA_FILTER_H
#define  _DATA_FILTER_H

#include <map>
#include <vector>
#include <string>

class DataFilter
{
public:

	DataFilter();
	
    virtual ~DataFilter();

    virtual void initFilter();

    virtual void writeAll();

    virtual void populateFilter(const std::string& filterParameters);

    std::vector<std::string> getFilterData(const std::string& filterParameters);

protected:

    std::map<unsigned int, bool> filter_;
    
private:

    void changeFilter(const unsigned int& packageData, bool isWrite);

    void addFilter(const unsigned int& packageData, bool isWrite);
};

#endif
