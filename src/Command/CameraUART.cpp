#include "CameraUART.h"

void CameraUART::SetupUART()
{
    Serial1.begin(BAUD_RATE, SERIAL_8N1, RXD_PIN, TXD_PIN);
}

void CameraUART::SendUARTData(StructBodyImage *Image)
{
    // Create A UART Message
    byte *ImageSerialization = new byte[IMAGE_SIZE];
    ImageSerialization = Serialization::SerializeBodyImage(Image);
    Serial1.write(ImageSerialization, IMAGE_SIZE);
    delete[] ImageSerialization;
}