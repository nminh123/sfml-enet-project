#include "../include/GameNet.hpp"

using namespace network;

GameNet::GameNet()
{
    this->address.host = ENET_HOST_ANY;
    this->address.port = 1234;
}

int GameNet::initializeServer()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Đã có lỗi xảy ra khi cố gắn tạo server ENet" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int GameNet::createHost()
{
    this->server = enet_host_create(&address, /* the address to bind the server host to */
                                    32,       /* allow up to 32 clients and/or outgoing connections */
                                    2,        /* allow up to 2 channels to be used, 0 and 1 */
                                    0,        /* assume any amount of incoming bandwidth */
                                    0 /* assume any amount of outgoing bandwidth */);
    if (this->server == NULL)
    {
        std::cerr << "Đã xảy lỗi khi cố gắn tạo server host với ENet" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int GameNet::createClient()
{
    this->client = enet_host_create(NULL /* create a client host */,
                              1 /* only allow 1 outgoing connection */,
                              2 /* allow up 2 channels to be used, 0 and 1 */,
                              0 /* assume any amount of incoming bandwidth */,
                              0 /* assume any amount of outgoing bandwidth */);

    if (this->client == NULL)
    {
        std::cerr << "Đã xảy lỗi khi cố gắn tạo client với ENet" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void GameNet::service(void* data)
{
    ENetEvent event;

    /* Wait up to 1000 milliseconds for an event. */
    while (enet_host_service(client, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << "A new client connected from: \n" << event.peer->address.host<< ", " << event.peer->address.port << std::endl;

            /* Store any relevant client information here. */
            event.peer->data = data;

            break;

        case ENET_EVENT_TYPE_RECEIVE:
            printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                   event.packet->dataLength,
                   event.packet->data,
                   event.peer->data,
                   event.channelID);

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy(event.packet);

            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            printf("%s disconnected.\n", event.peer->data);

            /* Reset the peer's client information. */

            event.peer->data = NULL;
        }
    }
}

GameNet::~GameNet()
{
    if (this->server != nullptr)
    {
        enet_host_destroy(this->server);
        this->server = nullptr;
    }

    if (this->client != nullptr)
    {
        enet_host_destroy(this->client);
        this->client = nullptr;
    }
    enet_deinitialize();
}