echo "Building from scratch and running tests!"

rm -r build/
rm -r src/python/.venv/

cmake -S ./ -B build
cmake --build build
ctest --test-dir ./build

echo "Done! :) "