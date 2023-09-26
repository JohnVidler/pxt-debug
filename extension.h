#define DMESG_ENABLE 1
#define DEVICE_DMESG_BUFFER_SIZE 1024
#define DMESG_SERIAL_DEBUG 1
#define CODAL_DEBUG 1
#define CODAL_DEBUG_STREAMS_API 1

#ifndef PXT_DEBUG_H
#define PXT_DEBUG_H

namespace CODALDebug {
    #if MICROBIT_CODAL
        void audio_stats_fiber();
    #endif
    
    void launch();
}

#endif