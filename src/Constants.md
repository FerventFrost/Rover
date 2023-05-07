## SubSystem Id and Command ID

### These Sybsystem only return readings

1- Subsystem 0 -> DHT
1.1- Command ID 0 -> Acc
1.2- Command ID 1 -> Gyro
1.3- Command ID 2 -> Temp (Defualt)

2- Subsystem 1 -> MPU
2.1- Command ID 0 -> Temp
2.2- Command ID 1 -> Humd (Defualt)

3- Subsystem 3 -> UltraSonic
3.1- Command ID 0 -> Distance (Defualt)

## Command Serialization

### Header Serialization

1- FrameType -> 1 byte
2- FrameBodyLength -> 1 byte
3- CRC -> 2 byte
4- AES IV -> 16 byte
5- PacketEnchryption -> FrameBodyLength with padding 0.

### Body Serialization Sensor Data

Encryption will be 16 byte size

1- PlanID -> 2 byte
2- SequenceID -> 1 byte
3- Time -> 4 byte
4- Sensors reading -> 6 byte
5- Zero Padding -> 3 byte

### Body Serialization Camera Data

Encryption will be ...

1- PlanID -> 2 byte
2- SequenceID -> 1 byte
3- Time -> 4 byte
4- Max camera Size -> ...
5- Zero Padding -> ...

#### Note

Time will reset after online session and offline session ends.

### Body Serialization ACK

Encryption will be 16 byte size

1- ACk -> 1 byte
2- ACKType -> 1 byte
3- Zero Padding -> 14 byte

### Body Deserialization Online Body

Encryption will be 16 byte size

1- PlanID -> 2 byte
2- SequenceID -> 1 byte
3- SubSystemID -> 1 byte
4- CommandID -> 1 byte
5- Delay -> 1 byte
6- CommandRepeat -> 1 byte
7- Zero Padding -> 9 byte

### Body Deserialization Offline Body

Encryption will be 16 byte size

1- PlanID -> 2 byte
2- SequenceID -> 1 byte
3- SubSystemID -> 1 byte
4- CommandID -> 1 byte
5- Delay -> 1 byte
6- CommandRepeat -> 1 byte
7- Time -> 4 byte
7- Zero Padding -> 5 byte
