#include <iostream>
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

using namespace std;
using namespace boost::asio;
using ip::tcp;
const static string MAIN_API = "ip-api.com";
const static string API_ARGUMENTS = "/json/";

namespace http = boost::beast::http;

class Client {
public:
	static string getResponse(string ip) {
		boost::asio::io_context io;
		boost::asio::ip::tcp::resolver resolver(io);

		tcp::socket socket(io);

		connect(socket, resolver.resolve(MAIN_API, "80"));
		string argument = API_ARGUMENTS + ip;
		http::request<http::string_body> req(http::verb::get, argument, 11);

		req.set(http::field::host, MAIN_API);
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

		http::write(socket, req);

		string response;
		{
			boost::beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(socket, buffer, res);
			response = boost::beast::buffers_to_string(res.body().data());
		}

		socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		return response;
	}
};