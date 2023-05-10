#ifndef WebSocket_h
#define WebSocket_h

#include "Arduino.h"
#include <WebServer.h>
#include "esp_websocket_client.h"
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>

class WebSocket
{
private:
    esp_websocket_client_handle_t client;
    static void EventHandler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

public:
    WebSocket(const char *url);
    ~WebSocket();
    void AcceptText();
    void SendText(char *message, size_t len);
    void SendBinary(char *message, size_t len);
    // they are not implmented yet
    void Connect(const char *url);
    void Disconnect();
    void onMessage(void (*callback)(String message));
    void onOpen(void (*callback)());
    void onClose(void (*callback)());
    void onError(void (*callback)(String message));
};
#endif