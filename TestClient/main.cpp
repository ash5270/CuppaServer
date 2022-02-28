#include "TestClient.h"
#include "Buffer.h"
#include <thread>
#include "Serializer.h"

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

	Buffer buffer;
	//buffer.Write('a');
	//buffer.Write('b');
	//buffer.Write('c');
	//buffer.Write('d');

	float float_data = 1.24f;

	/*const char* float_char= reinterpret_cast<const char*>(&float_data);*/

	buffer.Write(&float_data, sizeof(float));

	/*char* datas = new char[5];
	memset(datas, 0, 5);
	buffer.Read(datas, 4);

	std::string data_string(datas);*/


	unsigned int uint_data = 123;
	cuppa::to_stream(float_data, buffer);
	/*cuppa::to_stream('d', buffer);
	cuppa::to_stream(123123, buffer);*/
	cuppa::to_stream(uint_data, buffer);
	
	float float_datas;
	unsigned int uintdata;
	buffer.Read(&float_datas, sizeof(float));
	buffer.Read(&uintdata, sizeof(int));

	return  0;
}