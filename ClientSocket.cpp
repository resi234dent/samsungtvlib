#include "ClientSocket.h"
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

ClientSocket::ClientSocket(std::string ipAddress, int port)
        : mIpAddress(std::move(ipAddress)), mPort(port) {
    mIoContextPtr = std::make_unique<net::io_context>();
    mSslContextPtr = std::make_unique<ssl::context>(ssl::context::tlsv12_client);

    mWebSocketPtr = std::make_unique<websocketstream>(*mIoContextPtr, *mSslContextPtr);

    auto base64ControlName = encode64(REMOTE_CONTROL_NAME);
    mRemoteControlUrl = boost::replace_all_copy(PARAMETERISED_REMOTE_CONTROL_URL, REMOTE_CONTROL_URL_PARAMETER_NAME,
                                                    base64ControlName);

    std::cout << "Preparation is complete.\n";
}

bool ClientSocket::connectSync() {
    net::ip::tcp::endpoint hostEndpoint(net::ip::address::from_string(mIpAddress), mPort);

    mWebSocketPtr->next_layer().next_layer().connect(hostEndpoint);
    mWebSocketPtr->next_layer().handshake(ssl::stream_base::client);

    const auto host(":" + std::to_string(mPort));

    mWebSocketPtr->handshake(host, mRemoteControlUrl);
    std::cout << "Connection to the TV is established\n";

    return true;
}

void ClientSocket::sendSync(const std::string &command) {
    auto preparedCommand = boost::replace_all_copy(PARAMETERISED_COMMAND, COMMAND_PARAMETER_NAME, command);
    mWebSocketPtr->write(net::buffer(preparedCommand));

    std::cout << "Command has been sent!\n";
}

ClientSocket::~ClientSocket() {
    mWebSocketPtr->close(websocket::close_code::normal);
}

std::string ClientSocket::encode64(const std::string &text) {
    using namespace boost::archive::iterators;

    using itr = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto encodedText = std::string(itr(std::begin(text)), itr(std::end(text)));
    return encodedText.append((3 - text.size() % 3) % 3, '=');
}

