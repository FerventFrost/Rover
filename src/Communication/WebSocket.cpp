#include "WebSocket.h"

ByteQueue *WebSocket::DataQueue;

WebSocket::WebSocket(const char *url, ByteQueue *queue)
{
    DataQueue = queue;
    esp_websocket_client_config_t websocket_cfg = {
        .uri = url,
    };

    client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, &WebSocket::EventHandler, (void *)client);

    esp_websocket_client_start(client);
}

WebSocket::~WebSocket()
{
    esp_websocket_client_destroy(client);
}

void WebSocket::SendText(char *message, size_t len)
{
    esp_websocket_client_send_text(client, message, len, portMAX_DELAY);
}

void WebSocket::SendBinary(const char *data, size_t len, size_t chunkSize)
{
    size_t remainingLen = len;
    size_t offset = 0;
    while (remainingLen > 0)
    {
        size_t CurrentChunkSize = std::min(remainingLen, chunkSize);
        esp_websocket_client_send_bin(client, &data[offset], CurrentChunkSize, portMAX_DELAY);

        remainingLen -= CurrentChunkSize;
        offset += CurrentChunkSize;
    }
}

void WebSocket::EventHandler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;

    switch (event_id)
    {
    case WEBSOCKET_EVENT_CONNECTED:
        Serial.println("WEBSOCKET_EVENT_CONNECTED");
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        Serial.println("WEBSOCKET_EVENT_DISCONNECTED");
        break;
    case WEBSOCKET_EVENT_DATA:
        if (data->data_len != 0 && data->data_ptr != NULL)
        {
            DataQueue->enqueue((byte *)data->data_ptr, data->data_len);
        }
        break;
    case WEBSOCKET_EVENT_ERROR:
        Serial.println("WEBSOCKET_EVENT_ERROR");
        break;
    }
}

// // This method handles URL received from the client
// void WebSocket::HandleData()
// {
//     if (server->hasArg("text"))
//     {
//         ReceivedURL = server->arg("text");
//         server->send(200);
//     }
//     else
//         server->send(400);
// }

// // Call this function only once in the whole program lifetime or delete this object after finishing using it
// WebServer *WebSocket::InitWebSocketConnectListner()
// {
//     server = new WebServer(80);
//     server->on("/ConnectToWebSocket", HTTP_POST, WebSocket::HandleData);
//     return server;
// }

// // Check if the client is connected to the server
// bool WebSocket::IsConnected()
// {
//     server->handleClient();

//     if (ReceivedURL.isEmpty())
//         return false;
//     return true;
// }

// // delete the returned char* after using it
// char *WebSocket::GetSocketsURL()
// {
//     char *URL = new char[ReceivedURL.length() + 1];
//     strcpy(URL, ReceivedURL.c_str());
//     ReceivedURL = "";
//     return URL;
// }