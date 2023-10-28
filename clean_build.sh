echo "Cleaning up..."

rm -r build/
rm -r dist/
rm -r *.egg-info
rm -r src/python/.venv/
rm -r src/python/.ipynb_checkpoints/
rm -r src/python/*/.ipynb_checkpoints/
rm -r Testing/
rm -r tests/CmakeFiles/
rm -r tests/Testing/
rm -r tests/*.cmake
rm -r tests/Makefile

echo "All clean! :) "