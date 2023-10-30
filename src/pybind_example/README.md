# Using and setting up pybind

## Setting up ```pybind11``` for the first time

The following content is adapted based on this [YouTube video](https://www.youtube.com/watch?v=H2wOlriHGmM)! <br />
The following has been automated into a simple shell script ```deploy_cpp_module.sh``` (only works for linux and macOS). <br />

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
make fineng_irfx
```

(Sanity checking) Check that you now see a ```.a``` and ```.so``` file in your build folder

```
ls
```

Building our c++ package (python module) ```fineng_irfx```

```
cd ..
python3 setup.py bdist_wheel
```

(Sanity checking) Check that you see a ```.whl``` file in the generated ```dist``` folder

```
ls dist/
```

Set up a virtual environment in the python sub-folder

```
cd src/python
python3 -m venv .venv
```

(Sanity checking) Check that you see a hidden folder ```.venv```

```
ls -a
```

Install the c++ package we generated to the venv

```
./.venv/bin/pip install ../../dist/{name of the .whl file}
```

(Sanity checking) Check that you see a ```.so``` file in venv packages folder

```
ls .venv/lib/{your python3 version}/site-packages/
```

ALL DONE! Let's now sanity check that we can actually import the module in python venv

```
./.venv/bin/python pybind_example.py
```

## Set up ```pybind11``` for jupyter notebooks for the first time

The following has been automated into a simple shell script ```launch_jupyter.sh``` (only works for linux/macOS) <br />

Assume you have already set up the virtual environment ```.venv``` appropriately, we now activate the venv

```
source .venv/bin/activate
```

Personally, I use [fish](https://fishshell.com/) as my unix shell, so to activate the venv, I run instead

```
source .venv/bin/activate.fish
```

Make sure you have deactivated your base environment (sometimes it is automatically activated). Now install ```ipykernel```

```
./.venv/bin/pip install ipykernel
```

Install all the required packages

```
./.venv/bin/pip install -r requirements.txt
```

Install a Jupyter kernel in our virtual environment

```
ipython kernel install --user --name=.venv
```

Launch jupyter notebook/lab (I prefer ```jupuyter lab```)

```
jupyter lab
```

Make sure you run your notebooks with the kernel ```.venv```! See [this link](https://www.linkedin.com/pulse/how-use-virtual-environment-inside-jupyter-lab-sina-khoshgoftar/) for reference. <br />

For sanity checking, try running the notebook ```pybind_example_nb.ipynb``` to make sure everything works!
