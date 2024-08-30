from pathlib import Path
import json
import subprocess
import time

ROOT = Path(__file__).parent

def build(target):
    configs = json.loads((ROOT / "build.json").read_text("utf-8"))

    if target not in configs:
        print("target: {} not found in build.json".format(target))
        return
    
    config = configs[target]

    for test in ["folders", "buildFolder", "CC", "buildFlags"]:
        if test not in config:
            print("argument: {} for target: {} is missing".format(test, target))
            return
        
    CC = config["CC"]
    buildFlags = config["buildFlags"]
    headers = []

    fileTargets = {}
    folders = config["folders"].copy()
    buildRoot = ROOT / config["buildFolder"]
    while folders:
        folder : Path
        folder = folders.pop()
        
        for file in (ROOT / folder).iterdir():
            file : Path
            if file.is_file():
                if file.suffix == ".h":
                    headers.append(file.absolute().as_posix())
                else:
                    targetPath = (ROOT / buildRoot / folder / (file.with_suffix(".o")).name).absolute().as_posix()

                    fileTarget = [
                        file.absolute().as_posix()
                    ]

                    fileTargets[targetPath] = fileTarget

    for fTarget, fSource in fileTargets.items():
        print(fTarget, fSource)
        subprocess.Popen("{} -c {} -o {} {}".format(CC, fSource, fTarget, buildFlags))
        time.sleep(1)        

