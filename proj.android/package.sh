#!/bin/sh

sh build_native.sh
ant release
adb install bin/RunQuicky-release.apk