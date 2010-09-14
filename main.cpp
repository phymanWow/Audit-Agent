
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <boost/program_options.hpp>
#include "infominer.h"
#include "daemon.h"
#include <iterator>

// Namespace abbreviations
namespace po = boost::program_options;

void printUsage(std::string cmd)
{
    std::cout << "Usage: " << cmd << " [OPTIONS]" << std::endl;
    std::cout << "Options:\n";
    std::cout << "-d cmd: Starts the agent in daemon mode. cmd could be start|stop|status\n";
    std::cout << "-f filename: Writes information to filename. If not specified, information is written to STDOUT\n";
    std::cout << "-h : Prints this message\n";

}

void writeData(std::string filename)
{
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        // Write data to file
        std::ofstream of(filename.c_str());
        of << im;
        of.close();
        // Ftp file
    }
}

int main(int argc, char *argv[])
{
    std::string filename = "";
    std::string daemoncmd = "";
    bool daemon = false;

    // Parse command line options
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Prints this help message")
        ("daemon,d", po::value<std::string>(), "Start program in daemon mode, and pass command to daemon. Valid options for arg is start|stop|status")
        ("filename,f", po::value<std::string>(), "Write output to file, instead of standard output. File is FTP'ed to specified destination")
    ;
    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    if (vm.count("daemon")) {
        daemon = true;
        daemoncmd = vm["daemon"].as<std::string>();
    }
    if (vm.count("filename")) {
        filename = vm["filename"].as<std::string>();
    }

    // This will start/stop/status the daemon process
    if (daemon) {
        Daemon *d = Daemon::daemon("audit-agent");
        if (daemoncmd == "start") {
            if (!d->start()) {
                std::cout << "Could not start daemon: " << std::endl << d->statusStr() << std::endl;
                return 2;
            }
            // The main daemon loop
            while (true) {
                writeData(filename);
                sleep(60);
            }
        } else if (daemoncmd == "stop") {
            d->stop();
        } else if (daemoncmd == "status") {
            std::cout << d->statusStr() << std::endl;
        } else {
            return 2;
        }
        return 0;
    }

    writeData(filename);

    return 0;
}
