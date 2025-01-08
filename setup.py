from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools


class CMakeBuild(build_ext):
    def run(self):
        import subprocess
        import os

        for ext in self.extensions:
            ext_dir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
            cfg = 'Debug' if self.debug else 'Release'
            cmake_args = [
                f'-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={ext_dir}',
                f'-DPYTHON_EXECUTABLE={sys.executable}',
                f'-DCMAKE_BUILD_TYPE={cfg}'
            ]

            build_args = ['--config', cfg]
            build_temp = self.build_temp

            if not os.path.exists(build_temp):
                os.makedirs(build_temp)

            subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=build_temp)
            subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=build_temp)

    def build_extension(self, ext):
        import shutil
        ext_dir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        shutil.copytree(self.build_temp, ext_dir, dirs_exist_ok=True)


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


setup(
    name='PositWrapper',
    version='0.1.0',
    author='Sylvex Hung',
    author_email='cuberobin@gmail.com',
    description='Python binding for Posit',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    # ext_modules=[CMakeExtension('positWrapper', 'src')],
    ext_modules=[CMakeExtension('positWrapper')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
    python_requires='>=3.6',
    install_requires=['pybind11>=2.6.0'],  # Include pybind11 as a dependency
)
