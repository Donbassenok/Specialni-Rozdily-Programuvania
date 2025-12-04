#pragma once

class KeyProcessor {
public:
    enum Mode {
        ORIGINAL,
        INVERT,
        BLUR,
        CANNY,
        SOBEL
    };

private:
    Mode mode;

public:
    KeyProcessor();
    Mode processKey(int key);
    Mode getMode() const;
};