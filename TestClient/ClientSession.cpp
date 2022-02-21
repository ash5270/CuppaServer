#include "ClientSession.h"

cuppa::net::client::ClientSession::ClientSession(SessionType type, boost::asio::io_context& context,
	boost::asio::ip::tcp::socket socket): Session(type,context,std::move(socket))
{

}

void cuppa::net::client::ClientSession::OnRecv(Buffer buffer, size_t recvSize)
{
	Session::OnRecv(buffer, recvSize);
}

void cuppa::net::client::ClientSession::OnDisconnect()
{
	Session::OnDisconnect();
}
