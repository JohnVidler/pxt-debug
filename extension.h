#ifndef PXT_DEBUG_H
#define PXT_DEBUG_H

namespace CODALDebug {
    #if MICROBIT_CODAL
        void audio_stats_fiber();
    #endif
    
    void launch();
}

#endif