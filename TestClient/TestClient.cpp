#include "TestClient.h"

cuppa::net::client::TestClient::TestClient(std::string ip, int port)
	:Client(ip,port)
{

}

void cuppa::net::client::TestClient::OnMessage(Buffer& buffer)
{
	//여기서 버퍼 처리
	
}

void cuppa::net::client::TestClient::OnServerConnect(boost::asio::ip::tcp::socket socket)
{
	//여기서 connect 처리 
	printf_s("connect ... \n");
	m_session =std::make_shared<ClientSession>(SessionType::Client, m_asioContext, std::move(socket));
	m_session->ConnectToServer();
}
