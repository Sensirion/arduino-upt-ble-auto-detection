# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Fixed
- Fix memory leak in NimBLE by calling clearResults after scan results are processed.
- Use unit64_t for address (device id) instead of std::string
- Fix several clang tidy issues
- Update example to call keepAlive regularly. This ensures scanning does not stop due to errors.

## [0.1.0] 
### Added
- Initial release


