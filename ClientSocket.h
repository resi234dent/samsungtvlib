#ifndef SAMSUNGTVLIB_CLIENTSOCKET_H
#define SAMSUNGTVLIB_CLIENTSOCKET_H

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;

class ClientSocket {
private:
    using websocketstream = websocket::stream<beast::ssl_stream<tcp::socket>>;

    const std::string mIpAddress;
    const int mPort;
    std::string mRemoteControlUrl;

    std::unique_ptr<net::io_context> mIoContextPtr;
    std::unique_ptr<ssl::context> mSslContextPtr;
    std::unique_ptr<websocketstream> mWebSocketPtr;

    const std::string REMOTE_CONTROL_NAME = "samsungtvlib";

    const std::string COMMAND_PARAMETER_NAME = "$DataOfCmd$";
    const std::string PARAMETERISED_COMMAND = R"({"method": "ms.remote.control", "params": {"Cmd": "Click", "DataOfCmd": "$DataOfCmd$", "Option": "false", "TypeOfRemote": "SendRemoteKey"}})";

    const std::string REMOTE_CONTROL_URL_PARAMETER_NAME = "$name$";
    const std::string PARAMETERISED_REMOTE_CONTROL_URL = "/api/v2/channels/samsung.remote.control?name=$name$&token=12345678";

    static std::string encode64(const std::string &text);
public:
    explicit ClientSocket(std::string ipAddress, int port);
    ~ClientSocket();
    bool connectSync();
    void sendSync(const std::string& command);
};

#endif //SAMSUNGTVLIB_CLIENTSOCKET_H
