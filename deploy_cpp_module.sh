echo "Building and deploying python module!!"

rm -r build/
rm -r src/python/.venv/

mkdir build
cd build
cmake ..
make
make fineng_irfx

echo "FINISH BUILD!!"

cd ..
python3 setup.py bdist_wheel

cd src/python
rm -r .venv
python3 -m venv .venv
./.venv/bin/pip install ../../dist/*.whl
./.venv/bin/python pybind_example.py

cd ../../
echo "Done! :) "