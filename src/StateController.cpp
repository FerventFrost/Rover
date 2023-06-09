#include "StateController.h"

void printBytesAsHex(const uint8_t *bytes, size_t length)
{
    std::cout << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << std::setw(2) << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::dec << std::setfill(' ') << std::endl;
}

StateController::StateController(WebSocket *DataSocket, ByteQueue *Queue)
{
    _dataSocket = DataSocket;
    _dataQueue = Queue;
    currentState = State::TelemeteryState;
}

StateController::~StateController()
{
}

void StateController::TelemeteryState()
{
    byte PlanCounter = 1;
    bool NextPlan = true;
    bool TelemeteryImage = true;

    // Init Telemetery
    // byte *buffer = InitTelemeteryRequest();

    // Send All Telemetery
    while (true)
    {
        // Open the file for reading
        if (NextPlan && PlanCounter == 1)
        {
            TelemeteryInstance.SetPath(PlanFilePath.Plan1);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 2)
        {
            TelemeteryInstance.RemoveData(PlanFilePath.Plan1);
            TelemeteryInstance.CloseFile();
            TelemeteryInstance.SetPath(PlanFilePath.Plan2);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 3)
        {
            TelemeteryInstance.RemoveData(PlanFilePath.Plan2);
            TelemeteryInstance.CloseFile();
            TelemeteryInstance.SetPath(PlanFilePath.Plan3);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 4)
        {
            TelemeteryInstance.RemoveData(PlanFilePath.Plan3);
            TelemeteryInstance.CloseFile();
            TelemeteryInstance.SetPath(PlanFilePath.Plan4);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 5)
        {
            TelemeteryInstance.RemoveData(PlanFilePath.Plan4);
            TelemeteryInstance.CloseFile();
            TelemeteryInstance.SetPath(PlanFilePath.Plan5);
            TelemeteryInstance.OpenFile();
            PlanCounter++;
            NextPlan = false;
        }
        else if (NextPlan && PlanCounter == 6)
        {
            TelemeteryInstance.RemoveData(PlanFilePath.Plan5);
            TelemeteryInstance.CloseFile();
            // byte *buffer = EndTelemetryRequest();
            break;
        }
        else
        {
            if (TelemeteryImage)
            {
                NextPlan = SendTelemetery(TelemeteryImage);
                TelemeteryImage = false;
            }
            else
                NextPlan = SendTelemetery(TelemeteryImage);
        }

        delay(500);
    }

    currentState = State::AcceptPlanState;
}

void StateController::AcceptPlanState()
{
    byte *data = new byte[64];
    while (true)
    {
        if (!_dataQueue->isEmpty())
        {
            data = _dataQueue->dequeue().data;
            StructHeader header = Serialization::DeserializeHeader(data);
            if (header.Type == FrameType::Request)
            {
                ReceivedRequest(&header, &data[21]);
                // Untill implementing the ReceivedRequest Method
                // this if will break the loop.
                break;
            }
            else
            {
                if (!ReceivedData(&header, &data[21], false))
                {
                    // byte *buffer = ResendPlanRequest();
                }
                else
                {
                    // byte *buffer = DonePlanRequest();
                }
            }
            // delete[] data;
            // data = nullptr;
        }
    }
    delete[] data;
}

void StateController::OnlineState()
{
    bool EndOnline = false;
    QueueNodeData QueueNode;
    while (true)
    {
        if (EndOnline)
            break;
        if (!_dataQueue->isEmpty())
        {
            Serial.println("Controller state: OnlineState");
            QueueNode = _dataQueue->dequeue();
            EndOnline = ExecuteOnlineCommandState(QueueNode.data);
        }
        SendOnlineDataState();
    }
}

bool StateController::ExecuteOnlineCommandState(byte *data)
{
    // StructHeader header = Serialization::DeserializeHeader(data);
    // if (header.Type == FrameType::Request)
    // {
    //     ReceivedRequest(&header, data[]);
    //     return true;
    // }
    StructHeader header;
    header.Type = FrameType::Command;
    ReceivedData(&header, data, true);
    return false;
}

void StateController::SendOnlineDataState()
{ 
    // SendOnlineDataInstance.SendCamera();
    for (int i = 0; i < 6; i++)
    {
        byte *buffer = new byte[37];
        buffer = SendOnlineDataInstance.SendData(i);
        _dataSocket->SendText((const char *)buffer, 37);
        delay(100);
        delete[] buffer;
    }
}

// Send Telemetery Data of the current plan in the opened file till the end of the file
bool StateController::SendTelemetery(bool TelemeteryImage)
{
    byte *buffer = TelemeteryInstance.GetTelemetery();
    if (buffer == NULL)
    {
        delete[] buffer;
        buffer = nullptr;
        return true;
    }

    if (TelemeteryImage)
    {
        int PlanID = buffer[21] << 8 | buffer[22];
        byte SequenceID = buffer[23];
        SendImageTelemetry(PlanID, SequenceID);
    }

    _dataSocket->SendText((const char *)buffer, 37);
    delay(100);
    delete[] buffer;
    buffer = nullptr;
    return false;
}

// Send Telemetery Image Request to the Esp32 cam to get all telemetry images of the current plan using UART
// Note: This method is called once pre-plan
void StateController::SendImageTelemetry(int PlanID, byte SequenceID)
{
    // send image telemetery
    StructBodyImage bodyImage;
    bodyImage.PlanID = PlanID;
    bodyImage.SequenceID = SequenceID;
    bodyImage.OperationType = 2;
    byte *buffer = Serialization::SerializeBodyImage(&bodyImage);
    SendSocketData(buffer);
    delete[] buffer;
    buffer = nullptr;
}

// Check if the Data Received from the socket is a Valid or not.
// if not return false.
// if the data is valid, return true and do:
// 1- Save Data to Queue if the Packet Type is Plan.
// 2- Save Data to ESPFlash if the Packet Type is Command.
bool StateController::ReceivedData(StructHeader *Header, byte *data, bool isOnline)
{
    // check if the data is corrupted or not
    // if (!Serialization::isValidCRC(&data[21], Header->FrameLength, Header->CRC))
    //     return false;

    if (Header->Type == FrameType::Plan)
    {
        // save plan
        StructPlanBody planBody = Serialization::DeserializePlanBody(data);
        // Queue.Push(data);
    }
    else if (Header->Type == FrameType::Command && !isOnline)
    {
        // execute command
        StructBody command = Serialization::DeserializeBodyOffline(data);
        ESPFlash::WriteCommand(command);
    }
    else if (Header->Type == FrameType::Command && isOnline)
        ExecuteOnlineCommandInstance.RoverMovement(data);

    return true;
}

// I See this method as a redundant method,
// because There is only one request type that is received from the GS after Init Accept Plan phase.
// which is End Accept plan phase.
void StateController::ReceivedRequest(StructHeader *Header, byte *data)
{
}

// byte *StateController::InitTelemeteryRequest()
// {
//     Serial.println("Init Telemetry");
//     byte *buffer = new byte[4]{0, 69, 69, '\0'};
//     return buffer;
// }

// byte *StateController::EndTelemetryRequest()
// {
//     Serial.println("End Telemetry");
//     byte *buffer = new byte[4]{1, 69, 69, '\0'};
//     return buffer;
// }

fs::File StateController::OpenFile(const char *path)
{
    // open file
    SDCard::OpenRead(SD, path);
    fs::File file = SDCard::GetFile();
    return file;
}

void StateController::CloseFile(fs::File file)
{
    // close file
    file.close();
}

void StateController::DeleteData(fs::File file, const char *path)
{
    // delete file
    SDCard::RemoveFileData(path);
    file.close();
    SD.remove(path);
}

void StateController::CreateFile(const char *path)
{
    // create file
    SDCard::OpenAppend(SD, path);
    fs::File file = SDCard::GetFile();
    file.close();
}
