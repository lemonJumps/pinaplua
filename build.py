from pathlib import Path
import json
import subprocess
import time
import platform

ROOT = Path(__file__).parent

def build(target, machine = None, system = None):
    if machine == None:
        machine = platform.machine()
    if system == None:
        system = platform.system()

    print("building for: ", machine, system, )

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
    headerFolders = set()

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
                    headerFolders.add(file.parent.absolute().as_posix())
                else:
                    targetPath = (ROOT / buildRoot / folder / (file.with_suffix(".o")).name)

                    targetPath.parent.mkdir(parents=True, exist_ok=True)

                    fileTarget = [
                        file.absolute().as_posix()
                    ]

                    fileTargets[targetPath.absolute().as_posix()] = fileTarget

    # add architecture building
    if "archBased" in config:
        if machine + "_" + system in config["archBased"]:
            for filePath in config["archBased"][machine + "_" + system]:
                file = Path(filePath)
                print(file)
                targetPath = (ROOT / buildRoot / folder / (file.with_suffix(".o")).name)
                targetPath.parent.mkdir(parents=True, exist_ok=True)
                fileTarget = [file.absolute().as_posix()]
                fileTargets[targetPath.absolute().as_posix()] = fileTarget

    def runCommand(line):
        print("running: {}".format(line))
        return subprocess.Popen(line)

    headerSting = ""
    for folder in headerFolders:
        headerSting += " -I" + folder + " "

    # compile
    procs = []

    for fTarget, fSource in fileTargets.items():
        proc = runCommand("{} -c -o {} {} {} {}".format(CC, fTarget, fSource[0], buildFlags, headerSting))
        procs.append(proc)

    for proc in procs:
        proc.wait()

    fileString = ""
    for file in fileTargets.keys():
        fileString += " " + file

    # link
    proc = runCommand("{} -o {} {}".format(CC, config["output"], fileString))

    proc.wait()