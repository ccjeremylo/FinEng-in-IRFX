# Using and setting up pybind

Following content is adapted based on this [YouTube video](https://www.youtube.com/watch?v=H2wOlriHGmM)! <br />
Ideally should automate the following into a shell script...

##  Setting up ```pybind11``` for the first time!

Git clone ```pybind11``` repo to the root of this repo
```
cd {root of repo}
git clone https://github.com/pybind/pybind11.git
```
Build the project
```
cd build
cmake ..
make
make fineng_code
make cmake_example
```
(Sanity checking) Check that you now see a ```.a``` and ```.so``` file in your build folder
```
ls
```
Building our c++ package (python module) ```cmake_example``` (to be renamed...)
```
python3 setup.py bdist_wheel
```
(Sanity checking) Check that you see a ```.whl``` file in the generated ```dist``` folder
```
ls dist/
```
Set up a virtual environment in the python sub-folder
```
cd python
python3 -m venv .venv
```
Install the c++ package we generated to the venv
```
./venv/bin/pip install ../dist/{name of the .whl file}
```
(Sanity checking) Check that you see a ```.so``` file in venv packages folder
```
ls .venv/lib/{your python3 version}/site-packages/
```
ALL DONE! Let's now sanity check that we can actually import our module in python venv
```
./.venv/bin/python pybind_example.py
```

## Using pybind

Tbd...

