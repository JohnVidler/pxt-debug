#include "pxt.h"
#include "extension.h"
#include "MicroBit.h"

using namespace pxt;

namespace CODALDebug {

    void printSplitterInfo( StreamSplitter * splitter ) {
        #if MICROBIT_CODAL
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
        #if MICROBIT_CODAL
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

    //%
    void launch_cpp_fibers() {
        create_fiber( PXT_Debug::audio_stats_fiber );
    }
}