<h1 align="center">
    Brainfuck C Interpreter
</h1>

<p align="center">
	<a href="/../../releases/latest" title="Latest Release"><img src="https://img.shields.io/github/v/release/andreiosg/bfci.svg?sort=semver"></a>
    <a href="https://github.com/andreiosg/bfci/actions/workflows/ci.yml" title="BFCI CI"><img src="https://github.com/andreiosg/bfci/workflows/BFCI%20CI/badge.svg"></a>
    <a href="/../../commits/" title="Last Commit"><img src="https://img.shields.io/github/last-commit/andreiosg/bfci?style=flat"></a>
    <a href="/../../issues" title="Open Issues"><img src="https://img.shields.io/github/issues/andreiosg/bfci?style=flat"></a>
    <a href="./LICENSE" title="License"><img src="https://img.shields.io/badge/License-GNU%20AGPL--3.0-blue.svg?style=flat"></a>
</p>

A Brainfuck interpreter written in the C programming language.

## Usage

Invoke the interpreter binary with one positional argument, i.e., the BrainFuck program path:

```
$ ./bfci /path/to/brainfuck/program.bf
```

## Development
No additional dependencies are required besides the usual C development environment.
The `uthash` header only library requires no linking.

After cloning the repository, make sure to:
```
$ git submodule update --init
```
Or simply build the project once, since the process is automated via`CMake`.

## Build

Clone the repository via the preferred method.

Generate the build recipes via `CMake`:

```
$ mkdir build
$ cd build
build $ cmake ..
```

To enable debugging, set the `ENABLE_DEBUG` `CMake` option to `ON`, e.g.:

```
build $ cmake -D ENABLE_DEBUG=ON ..
```
This will enable program `TRACE` output to `stderr`.


Invoke the build via `Make`:

```
build $ make
```

## Examples

The `examples` directory contains `BrainFuck` example programs.

## License 
Licensed under the *GNU Affero General Public License v3.0*.

Refer to the [LICENSE](./LICENSE) file in the repository.

