#include "CameraUART.h"

CameraUART::CameraUART()
{
}

CameraUART::~CameraUART()
{
    delete CameraSerial;
}

void CameraUART::SetupUART()
{
    CameraSerial = new HardwareSerial(1);
    CameraSerial->begin(115200, SERIAL_8N1, RXD_PIN, TXD_PIN);
}

void CameraUART::SendUARTData(StructBodyImage *Image)
{
    byte *ImageSerialization = new byte[IMAGE_SIZE];
    ImageSerialization = Serialization::SerializeBodyImage(Image);
    CameraSerial->write(ImageSerialization, IMAGE_SIZE);
    delete[] ImageSerialization;
}