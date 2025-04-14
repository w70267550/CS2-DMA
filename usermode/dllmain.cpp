// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.hpp"


extern Map G_map;

void web_radar()
{

    try
    {
        while (1)
        {
            if (G_map.EnableWebRadar) {

                //system("Radar\\start.bat");

                std::cout << " [ > ] Web-Radar Starting..." << std::endl;

                // @easywsclient
                WSADATA wsa_data{};
                const auto wsa_startup = WSAStartup(MAKEWORD(2, 2), &wsa_data);
                if (wsa_startup != 0)
                {
                    std::cout << " [ ! ] wsclient could not start..." << std::endl;
                    this_thread::sleep_for(chrono::seconds(5));
                    continue;
                }

                const auto ipv4_address = utils::get_ipv4_address();
                if (ipv4_address.empty())
                {
                    std::cout << " [ ! ] iPv4 address empty..." << std::endl;
                    this_thread::sleep_for(chrono::seconds(5));
                    continue;
                }

                const auto formatted_address = format("ws://{}:22006/cs2_webradar", utils::get_ipv4_address());
                auto web_socket = easywsclient::WebSocket::from_url(formatted_address);//easywsclient::WebSocket::from_url("ws://192.168.2.243:22006/cs2_webradar");
                if (!web_socket)
                {
                    std::cout << " [ ! ] Could not connect to app... Make sure to open start.bat" << std::endl;
                    this_thread::sleep_for(chrono::seconds(5));
                    continue;
                }

                //LOG("web socket ('%s')", formatted_address.data());
                std::cout << " [ > ] Web-Radar Connected... [ " << ipv4_address << ":5173 ]" << std::endl;


                //ShellExecute(0, 0, L"http://localhost:5173", 0, 0, SW_SHOW);

                auto start = chrono::system_clock::now();

                for (;;)
                {
                    const auto now = chrono::system_clock::now();
                    const auto duration = now - start;
                    if (duration >= chrono::milliseconds(2)) // delay to send data to radar
                    {
                        start = now;

                        m_features.run();
                        try
                        {
                            // LOG("%s", m_features.get_data().dump().data());
                            web_socket->send(m_features.get_data().dump());
                        }
                        catch (...)
                        {
                            cout << " [ ! ] Radar error 1" << endl;
                        }

                    }

                    web_socket->poll();
                    if (web_socket->getReadyState() == 1)
                    {
                        break;
                    }

                    this_thread::sleep_for(chrono::milliseconds(1));
                }
                std::cout << " [ ! ] Web-Radar Disconnected???" << std::endl;
                //system("pause");
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << " [ ! ] Radar error 2" << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << " [ ! ] Radar error 3" << std::endl;
    }

    return;
}