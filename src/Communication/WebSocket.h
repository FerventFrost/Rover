#ifndef WebSocket_h
#define WebSocket_h

#include "StructPlan.h"
#include "Arduino.h"
#include <WiFi.h>
#include <WebServer.h>
#include "esp_websocket_client.h"
#include "Command\Queue.h"
#include <esp_log.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>

class WebSocket
{
private:
    esp_websocket_client_handle_t client;
    static ByteQueue *DataQueue;
    // this part is for First Requests that indicate the GS try to connect to Rover
    // static WebServer *server;
    static String ReceivedURL;
    static void HandleData();

    static void EventHandler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
    void AcceptText();
    void ExecuteCommand(char *Body, FrameType Type);

public:
    WebSocket(const char *url, ByteQueue *queue);
    ~WebSocket();
    void SendText(char *message, size_t len);
    void SendBinary(const char *data, size_t len, size_t chunkSize);
    void DeserializeHeader(char *message, size_t len);
    void AESEncryptCBC(char *message, size_t len, char *IV);
    void AESDecryptCBC(char *message, size_t len, char *IV);

    // static WebServer *InitWebSocketConnectListner();
    // static bool IsConnected();
    // static char *GetSocketsURL();
    // they are not implmented yet
    // void Connect(const char *url);
    // void Disconnect();
    // void onMessage(void (*callback)(String message));
    // void onOpen(void (*callback)());
    // void onClose(void (*callback)());
    // void onError(void (*callback)(String message));
};
#endif