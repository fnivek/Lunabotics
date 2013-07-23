// SerialCommunicationsBoost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/asio.hpp>
#include <iostream>
#include <ctime>
#include <string>

using boost::asio::ip::tcp;
using namespace std;

boost::asio::io_service io_service;
tcp::resolver resolver(io_service);

string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

int _tmain(int argc, char* argv[])
{
	//get the day time
	/*try
	{
		tcp::resolver::query query("nist1-nj.ustiming.org", "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		for(;;)
		{
			//boost::array<char, 128> buf;
			char buf[128];
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if(error == boost::asio::error::eof)
			{
				std::cout.write(buf, len);
				break;
			}
			else if (error)
				throw boost::system::system_error(error);
		}

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	char buf[128];
	std::cout << "Press enter to continue";
	std::cin.clear();
	std::cin.getline(buf, '\n');
	*/


	//day time server

	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		while(true)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			string msg = make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
		}
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}
	return 0;
}