echo "Building and running tests!"

rm -r build/
rm -r src/python/.venv/

mkdir build
cd build
cmake ..
make
ctest --tests .

echo "Done! :) "