#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/FL_Button.H>
#include <RtAudio.h>

#include "gilbertcore/gilbert.cpp"

gilbert *g = new gilbert();

int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData ){
    if ( status ){
        std::cout << "Stream overflow detected!" << std::endl;
    }
    std::vector<double> toGilbert((float *)inputBuffer,(float *)inputBuffer+nBufferFrames);
    std::cout<<toGilbert.at(1)<<std::endl;
    // g->audioIn(toGilbert);
    // Do something with the data in the "inputBuffer" buffer.
    return 0;
}

int main(int argc, char **argv) {
    RtAudio adc;
    if ( adc.getDeviceCount() < 1 ) {
        std::cout << "\nNo audio devices found!\n";
        exit( 0 );
    }
    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 256; // 256 sample frames
    try {
        adc.openStream( NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record );
        adc.startStream();
    }
    catch ( RtAudioError& e ) {
        e.printMessage();
        exit( 0 );
    }

    Fl_Window *window = new Fl_Window(340,180);
    Fl_Box *box = new Fl_Box(10,10,130,20,"Gilbert Development");
    Fl_Button *drumA = new Fl_Button(10, 40, 25, 25, "A");
    // drumA->callback(synth::setVolume_static, s);
    Fl_Button *drumB = new Fl_Button(40, 40, 25, 25, "B");
    // drumB->callback(synth::setVolume_static, s);
    Fl_Button *drumC = new Fl_Button(70, 40, 25, 25, "C");
    // drumC->callback(synth::setVolume_static, s);
    Fl_Button *drumD = new Fl_Button(100, 40, 25, 25, "D");
    // drumD->callback(synth::setVolume_static, s);
    box->box(FL_UP_BOX);
    box->labelsize(12);
    window->end();
    window->show(argc, argv);
    return Fl::run();
}