#include "pxt.h"
#include "extension.h"
#include "MicroBit.h"

#if MICROBIT_CODAL
#include "StreamSplitter.h"
#endif

using namespace pxt;

namespace CODALDebug {

#if MICROBIT_CODAL
    void printSplitterInfo( StreamSplitter * splitter ) {
        #if CONFIG_ENABLED(CODAL_DEBUG_STREAMS_API)
            DMESG( "%d - Active Channels: %d (isActive = %d, sampleRate = %d)", splitter->id, splitter->activeChannels, splitter->isActive, (int)splitter->upstream.getSampleRate() );
            for( int i=0; i<CONFIG_MAX_CHANNELS; i++ ){
                if( splitter->outputChannels[i] != NULL ) {
                    if( splitter->outputChannels[i]->output != NULL )
                        DMESG( "\t- %d [CONN] sent = %d failed = %d (sampleRate = %d)", i, splitter->outputChannels[i]->sentBuffers, splitter->outputChannels[i]->pullAttempts, (int)splitter->outputChannels[i]->getSampleRate() );
                    else
                        DMESG( "\t- %d [DISC] sent = %d failed = %d (sampleRate = %d)", i, splitter->outputChannels[i]->sentBuffers, splitter->outputChannels[i]->pullAttempts, (int)splitter->outputChannels[i]->getSampleRate() );
                }
            }
        #endif
    }

    void audio_stats_fiber() {
        #if CONFIG_ENABLED(CODAL_DEBUG_STREAMS_API)
            extern MicroBit uBit;

            while( true ) {
                char const CLEAR_SRC[] = {0x1B, 0x5B, 0x32, 0x4A, '\r' };
                DMESG( CLEAR_SRC );

                DMESG(
                    "ADC Channels: [%s, %s, %s, %s, %s, %s, %s, %s, %s, %s]",
                    uBit.adc.channels[0].output.isFlowing()?"F":" ",
                    uBit.adc.channels[1].output.isFlowing()?"F":" ",
                    uBit.adc.channels[2].output.isFlowing()?"F":" ",
                    uBit.adc.channels[3].output.isFlowing()?"F":" ",
                    uBit.adc.channels[4].output.isFlowing()?"F":" ",
                    uBit.adc.channels[5].output.isFlowing()?"F":" ",
                    uBit.adc.channels[6].output.isFlowing()?"F":" ",
                    uBit.adc.channels[7].output.isFlowing()?"F":" ",
                    uBit.adc.channels[8].output.isFlowing()?"F":" ",
                    uBit.adc.channels[9].output.isFlowing()?"F":" "
                );

                printSplitterInfo( uBit.audio.rawSplitter );
                printSplitterInfo( uBit.audio.splitter );

                uBit.sleep( 250 );
            }
        #endif
    }
#endif

    //% 
    void launch() {
        //#if MICROBIT_CODAL && CONFIG_ENABLED(DMESG_SERIAL_DEBUG)

            DMESG( "=== DEBUG BUILD CONFIG ===" );
            DMESG( "DMESG_SERIAL_DEBUG       = %d", DMESG_SERIAL_DEBUG );
            DMESG( "CODAL_DEBUG              = %d", CODAL_DEBUG );
            DMESG( "DEVICE_DMESG_BUFFER_SIZE = %d", DEVICE_DMESG_BUFFER_SIZE );
            DMESG( "CODAL_DEBUG_STREAMS_API  = %d", CODAL_DEBUG_STREAMS_API );
            DMESG( "=== DEBUG BUILD CONFIG ===" );

            #if CONFIG_ENABLED(CODAL_DEBUG_STREAMS_API)
                create_fiber( audio_stats_fiber );
            #endif
            
        //#endif
    }
}