
#include <vector>
#include <cstdlib>
#include "network.h"
#include "dmiparser.h"
#include "commandparser.h"
#include "util.h"
#include "architecture.h"
#include "linuxnetwork.h"
#include "macnetwork.h"

Network::Network()
{
}

Network::~Network()
{
}

std::string Network::output()
{
    stringstream stream;
    stream << mHardware << endl;
    stream << "Adapters Count=" << mAdapters.size() << endl;
    for (int i = 0 ; i < (int)mAdapters.size(); i++) {
        stream << "Adapters" << i+1 << "=" << mAdapters[i].name << endl;
        stream << "Adapters Mac" << i+1 << "=" << mAdapters[i].mac << endl;
        stream << "Adapters IP" << i+1 << "=" << mAdapters[i].ip << endl;
        stream << "Adapters Cnt" << i+1 << "=" << mAdapters[i].count << endl;
        stream << "Adapters Suffix" << i+1 << "=" << mAdapters[i].suffix << endl;
        stream << "Adapters Subnet" << i+1 << "=" << mAdapters[i].mask << endl;
        
    }
    return stream.str();
}

void Network::read()
{

}

