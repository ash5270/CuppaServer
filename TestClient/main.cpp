#include "TestClient.h"
#include "Buffer.h"
#include <thread>
#include "Serializer.h"
#include<Vector3.h>

#include <list>

using namespace cuppa::net;

int main()
{
	////cuppa::net::client::TestClient client("127.0.0.1",3000);
	////std::thread clientUpdate(&cuppa::net::client::TestClient::Update,client);
	////client.Start();

	//std::list<cuppa::net::client::TestClient*> clients;

	//for(int i=0; i< 100; i++)
	//{
	//	auto client =new cuppa::net::client::TestClient("127.0.0.1", 3000);
	//	client->Start();
	//	clients.push_back(std::move(client));
	//}

	//while (true)
	//{
	//	cuppa::net::Buffer buffer;
	//	buffer.Write("dddddd", 6);
	////client.Send(buffer);
	//	for (auto client : clients)
	//	{
	//		client->Send(buffer);
	//	}
	//	std::this_thread::sleep_for(std::chrono::seconds(2));
	//	//client.Update();
	//}

	cuppa::Vector3 vec1(1,1,1);
	cuppa::Vector3 vec2(2,2,2);
	vec1 += vec2;


	//vec1 = vec2+vec1;
	

	//vec1 = vec2;
	
	return  0;
}