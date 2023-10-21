# Using and setting up pybind

Following content is adapted based on this [YouTube video](https://www.youtube.com/watch?v=H2wOlriHGmM)! <br />
Ideally should automate the following into a shell script...

##  Setting up pybind11 for the first time!

1. git clone ```pybind11``` repo to the root of this repo
```
cd {root of repo}
git clone https://github.com/pybind/pybind11.git
```
2. Build the project
```
cd build
cmake ..
make
make fineng_code
make cmake_example
```
3. (Sanity checking) Check that you now see a ```.a``` and ```.so``` file in your build folder
```
ls
```
4. Building your python package ```cmake_example``` (to be renamed)
```
python3 setup.py bdist_wheel
```
5. (Sanity checking) Check that you see a ```.whl``` file in the generated ```dist``` folder
```
ls dist/
```
6. Set up a virtual environment in the ```python``` sub-folder and install the c++ package we generated
```
cd python
python3 -m venv .venv
```
7. Install the c++ package we generated to the venv
```
./venv/bin/pip install ../dist/{name of the .whl file}
```
8. (Sanity checking) Check that you see a ```.so``` file in venv packages folder
```
ls .venv/lib/{your python3 version}/site-packages/
```
9. ALL DONE! Let's now sanity check that we can actually import our module in python venv
```
./.venv/bin/python pybind_example.py
```

## Using pybind

Tbd...

