printf "Formatting python code:\n\n"

# formatting
black src/python/*
black src/python/*/*
isort src/python/*
isort src/python/*/*

# format review
printf "\n\n===================\n"
printf "RUNING PEP8 checks:\n\n"
pycodestyle src/python/*

printf "\n\n===================\n"
printf "RUNING PEP8 checks for all sub-folders:\n\n"
pycodestyle src/python/*/*

printf "\n\n===================\n"
printf "RUNING pylint code review for all sub-folders\n\n"
pylint src/python/*/*