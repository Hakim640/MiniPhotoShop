#!/bin/bash
#cmake . && make \
#i686-w64-mingw32.static-qmake-qt5 && make \
git add . && \
git commit -m "release" && \
git push origin release \
