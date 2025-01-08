mkdir build
python3 -m venv build/env
source build/env/bin/activate
pip install numpy~=1.22.2
pip install -U pip setuptools wheel
pip install .

