echo "Building and deploying c++ package as python module!!"

while true; do
    read -p "Do you want to rebuild project? [y/n]: " yn
    case $yn in
        [Yy]* ) "Building project from scratch."; 
            rm -r build/;
            rm -r src/python/.venv/;
            cmake -S ./ -B build;
            cmake --build build;
            ctest --test-dir ./build;
            break;;
        [Nn]* ) "Great, we can continue"; 
            break;;
        * ) echo "Please answer y or n.";;
    esac
done

# deploying the c++ package as a python module
python3 setup.py bdist_wheel

# install c++ package into .venv
cd src/python
python3 -m venv .venv
./.venv/bin/pip install ../../dist/*.whl

# testing python module by running example script
./.venv/bin/python pybind_example.py

cd ../../
echo "Done! :) "