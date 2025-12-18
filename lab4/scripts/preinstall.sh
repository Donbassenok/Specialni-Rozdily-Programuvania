#!/bin/bash
sudo apt update
sudo apt install -y libopencv-dev cmake g++ make wget

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
wget -q -P "$PROJECT_DIR/resources" https://raw.githubusercontent.com/opencv/opencv/master/samples/dnn/face_detector/deploy.prototxt
wget -q -P "$PROJECT_DIR/resources" https://raw.githubusercontent.com/opencv/opencv_3rdparty/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel
wget -q -P "$PROJECT_DIR/resources" https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp

echo "Preinstall complete."
