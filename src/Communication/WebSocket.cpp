#include "WebSocket.h"

WebSocket::WebSocket(const char *url)
{
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

void WebSocket::SendBinary(char *data, size_t len)
{
    esp_websocket_client_send_bin(client, data, len, portMAX_DELAY);
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
        Serial.println("WEBSOCKET_EVENT_DATA");
        break;
    case WEBSOCKET_EVENT_ERROR:
        Serial.print("Received: ");
        Serial.println(data->data_len);
        Serial.print("Data: ");
        Serial.println((char *)data->data_ptr);
        break;
    }
}
