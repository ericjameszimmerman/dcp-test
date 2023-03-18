#!/usr/bin/env python3

import subprocess
import pathlib

def main():
    script_dir = pathlib.Path(__file__).resolve().parent
    build_dir = script_dir.joinpath('build')
    build_dir.mkdir(exist_ok=True)

    print(script_dir)
    print(build_dir)

    # Configure CMake
    result = subprocess.call('cmake -B"." -S".." -G"Unix Makefiles"', cwd=str(build_dir), shell=True)
    print(f'configure result = {result}')

    # build
    result = subprocess.call('cmake --build .', cwd=str(build_dir), shell=True)
    print(f'build result = {result}')

if __name__ == "__main__":
    main()
