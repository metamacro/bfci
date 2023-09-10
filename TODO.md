# TODO:

## Tests
- add CTest tests utilizing `examples/`

## CI
- upload Build (`build.yml`) workflow build artifacts
- add new Tests (`tests.yml`) workflow
    - runs on `build.yml` completion
    - on success, runs `ctest` for each build artifact
