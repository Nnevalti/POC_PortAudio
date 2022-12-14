#include "StreamHandler.h"
#include <iostream>

int callback   (const void *input,
                void *output,
                unsigned long frameCount,
                const PaStreamCallbackTimeInfo *timeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData)
{
    unsigned int nbChannels = 2;

    std::memcpy(output, input, frameCount * nbChannels * SAMPLE_SIZE);

    /* Check return value at http://files.portaudio.com/docs/v19-doxydocs/portaudio_8h.html#ae9bfb9c4e1895326f30f80d415c66c32 */
    return paContinue; 
}

int main()
{
    StreamHandler stream;

    stream.initInput(1);
    stream.initOutput(2);
    stream.openStream(&callback);
    stream.startStream();

    char input;
    std::cout << "\nRunning ... press <enter> to quit (buffer frames = " << FRAMES_PER_BUFFER << ").\n";
    std::cin.get(input);

    stream.stopStream();

    return 0;
}
