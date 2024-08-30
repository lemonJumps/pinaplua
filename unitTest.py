from pathlib import Path
from build import *

ROOT = Path(__file__).parent

build("native-test")
