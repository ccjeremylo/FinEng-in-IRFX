echo "Launching jupyter from src folder:"

while true; do
    read -p "Have you successfully deployed the c++ package? [y/n]: " yn
    case $yn in
        [Yy]* ) "Great! We will procceed."; 
            break;;
        [Nn]* ) "Program terminated - please run: ./deploy_cpp_module.sh"; 
            exit;;
        * ) echo "Please answer y or n.";;
    esac
done

# activate .venv
cd src/python/
# source .venv/bin/activate.fish 
source .venv/bin/activate
echo "\n"

while true; do
    read -p "Do you want to install required packages to the virtual env? [y/n]: " yn
    case $yn in
        [Nn]* ) "Great! We can skip all installation."; 
            break;;
        [Yy]* ) "Installing packages:"; 
            ./.venv/bin/pip install ipykernel;
            ./.venv/bin/pip install -r requirements.txt;
        break;;
        * ) echo "Please answer y or n.";;
    esac
done

# install .venv into kernal - launch jupyter lab
ipython kernel install --user --name=.venv
cd ../
jupyter lab

# cd back to root and deactivate .venv
cd ../
deactivate
echo "\n"
echo "Script finished!! This means jupyter session has ended :D"