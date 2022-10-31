#include "Session.h"
#include <boost/bind.hpp>

#include "LogSystem.h"

cuppa::net::Session::Session(SessionType type, boost::asio::io_context& context, boost::asio::ip::tcp::socket socket)
	:m_socket(std::move(socket)), m_context(context), m_sessionType(type), m_sendBuffer(), m_recvBuffer(), m_user_token("")
{
	boost::asio::ip::tcp::no_delay option(true);
	m_socket.set_option(option);
	is_login = false;
}

cuppa::net::Session::Session(Session&& session):
	m_socket(std::move(session.m_socket)),
	m_context(session.m_context),
	m_sendBuffer(std::move(session.m_sendBuffer)),
	m_recvBuffer(std::move(session.m_recvBuffer)),
	m_user_token(session.m_user_token)
{

}

cuppa::net::Session::~Session()
{
	
}

bool cuppa::net::Session::ConnectToClient()
{
	if (m_sessionType == SessionType::Server)
	{
		if (m_socket.is_open())
		{
			RecvData();
			return true;
		}
	}
	return  false;
}

bool cuppa::net::Session::ConnectToServer()
{
	if (m_sessionType == SessionType::Client)
	{
		if (m_socket.is_open())
		{
			RecvData();
			return true;
		}
	}
	return  false;
}

void cuppa::net::Session::DisconnectToClient()
{
	Disconnect();	
}

void cuppa::net::Session::Disconnect()
{
	if (m_socket.is_open())
	{
		/*boost::asio::post(
			[&]()
			{*/
				OnDisconnect();
				boost::system::error_code ec;
				m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
				Log::Print("Disconnect ", ec.value());
				m_socket.close();
			//});
	}
}

void cuppa::net::Session::RecvData()
{
	m_socket.async_read_some(
		boost::asio::buffer(m_recvBuffer.GetBuffer(), m_recvBuffer.GetCapacity()),
		boost::bind(&Session::RecvDataCallBack,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void cuppa::net::Session::RecvDataCallBack(boost::system::error_code ec, size_t transferred)
{
	if (!ec)
	{
		if (transferred < sizeof(uint32_t))
		{
			printf_s("[error] recv size msg : %s  size: %llu\n", ec.message().c_str(), transferred);
		}
		else
		{
			m_recvBuffer.SetSize(transferred);
			OnRecv(m_recvBuffer, transferred);
		}
		RecvData();
	}
	else
	{
		printf_s("[error] recv function msg : %s, size: %llu\n",  ec.message().c_str(), transferred);
		Disconnect();
	}
}

void cuppa::net::Session::Send(const Buffer& buffer)
{
	//람다 -> buffer - 버퍼 없어지는거자나
	m_sendBuffer = buffer;
	m_context.post([&]()
		{
			SendData(buffer);
		});
}

void cuppa::net::Session::Send(Buffer&& buffer)
{
	m_sendBuffer = buffer;
	m_context.post([&]()
		{
			this->m_sendBuffer;
			SendData(std::move(m_sendBuffer));
		});
}



void cuppa::net::Session::Connect()
{

}

void cuppa::net::Session::SendData(Buffer&& buffer)
{
	m_socket.async_write_some(
		boost::asio::buffer(buffer.GetBuffer(), buffer.GetSize()),
		boost::bind(&Session::SendDataCallBack,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void cuppa::net::Session::SendData(const Buffer& buffer)
{
	m_socket.async_write_some(
		boost::asio::buffer(buffer.GetBuffer(), buffer.GetSize()),
		boost::bind(&Session::SendDataCallBack,
			shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void cuppa::net::Session::SendDataCallBack(boost::system::error_code ec, size_t transferred)
{
	if (!ec)
	{
		//cuppa::Log::Print("send data bytes :", transferred);
		m_sendBuffer.Clear();
	}
	else
	{
		cuppa::Log::Error("send function msg : ", ec.message());
	}
}

//void cuppa::net::Session::Notify()
//{
//
//}
