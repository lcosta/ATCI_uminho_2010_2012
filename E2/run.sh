LIBS_CODE="manager.c ui.c"
APP_CODE="biblo.c"
APP_EXE="biblo"

mkdir -p code/build
cd code
gcc $LIBS_CODE $APP_CODE -o build/$APP_EXE && cd ./build && ./$APP_EXE