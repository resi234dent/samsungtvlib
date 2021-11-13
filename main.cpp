#include "ClientSocket.h"
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv) {
    try {
        po::options_description desc{"Options"};
        desc.add_options()
                ("help, h", "Help screen")
                ("ip", po::value<std::string>(), "TV IP Address")
                ("port", po::value<uint16_t>()->default_value(8002), "TV port number")
                ("command", po::value<std::string>(), "TV command name");

        po::variables_map variablesMap;
        store(parse_command_line(argc, argv, desc), variablesMap);
        notify(variablesMap);

        if (variablesMap.count("help")) {
            std::cout << desc << '\n';
            return 1;
        }

        auto ipItr = variablesMap.find("ip");
        if (ipItr != variablesMap.end()) {
            std::cout << "IP address : " << ipItr->second.as<std::string>() << '\n';
        } else {
            std::cout << "TV IP address is missing!\n";
            return 1;
        }

        auto portItr = variablesMap.find("port");
        assert(portItr != variablesMap.end());
        std::cout << "Port number : " << portItr->second.as<uint16_t>() << '\n';

        auto commandItr = variablesMap.find("command");
        if (commandItr != variablesMap.end()) {
            std::cout << "TV command : " << commandItr->second.as<std::string>() << '\n';
        } else {
            std::cout << "TV command is missing!\n";
            return 1;
        }

        ClientSocket clientSocket(ipItr->second.as<std::string>(),
                                  portItr->second.as<uint16_t>());

        if (!clientSocket.connectSync()) {
            std::cout << "Unable to connect...exiting.";
            return 1;
        }

        clientSocket.sendSync(commandItr->second.as<std::string>());
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

