from pathlib import Path
from build import *

import subprocess

ROOT = Path(__file__).parent

build("native-test")

# proc = subprocess.Popen("test.exe")
# proc.wait()