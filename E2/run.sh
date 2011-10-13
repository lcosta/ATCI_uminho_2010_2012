LIBS_CODE=""
APP_CODE="biblo.c"

mkdir -p code/build
cd code
gcc $LIBS_CODE $APP_CODE -o build/$APP_CODE && ./build/$APP_CODE