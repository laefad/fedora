import pathlib
from typing import List


class Config:
    headers_pattern: str = 'Fedora/Headers/**/*.h'
    sources_pattern: str = 'Fedora/**/*.cpp'
    cmake_file_path: str = 'CMakeLists.txt'
    project_name: str = 'fedora'


def get_cmake_config():
    with open(Config.cmake_file_path, 'r') as f:
        begin, rest = f.read().split('add_executable(')
        _, rest = rest.split(')', 1)
        return begin, rest


def get_cpp_files() -> List[str]:

    def path_to_relattive_str(path: pathlib.Path) -> str:
        return str(path)

    headers = list(map(
        path_to_relattive_str,
        pathlib.Path('.').glob(Config.headers_pattern)
    ))
    sources = list(map(
        path_to_relattive_str,
        pathlib.Path('.').glob(Config.sources_pattern)
    ))

    return headers + sources


def update_cmake_executable():
    files = get_cpp_files()
    begin, end = get_cmake_config()
    result = begin + \
        f'add_executable({Config.project_name}\n\t' + \
        '\n\t'.join(files) + \
        '\n)' + \
        end
    with open(Config.cmake_file_path, 'w') as f:
        f.write(result)


if __name__ == "__main__":
    update_cmake_executable()
