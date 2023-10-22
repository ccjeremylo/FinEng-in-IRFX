echo "Cleaning up..."

rm -r build/
rm -r dist/
rm -r *.egg-info
rm -r src/python/.venv/
rm -r src/python/.ipynb_checkpoints/
rm -r src/python/*/.ipynb_checkpoints/
git clean -f

echo "All clean! :) "