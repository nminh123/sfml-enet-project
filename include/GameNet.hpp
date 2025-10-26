#pragma once
#include <enet/enet.h>
#include <iostream>

namespace network
{
    class GameNet
    {
    private:
        ENetAddress address;
        ENetHost *server;
        ENetHost *client;

    protected:
    public:
        GameNet();
        ~GameNet();
        int initializeServer();
        int createHost();
        int createClient();
        void service(void* data);
    };
} //namespace network