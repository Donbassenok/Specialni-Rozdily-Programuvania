#include "KeyProcessor.hpp"

KeyProcessor::KeyProcessor() {
    mode = ORIGINAL;
}

KeyProcessor::Mode KeyProcessor::processKey(int key) {
    switch (key) {
        case '1': mode = INVERT; break;
        case '2': mode = BLUR; break;
        case '3': mode = CANNY; break;
        case '4': mode = SOBEL; break;
        case '0': mode = ORIGINAL; break;
    }
    return mode;
}

KeyProcessor::Mode KeyProcessor::getMode() const {
    return mode;
}