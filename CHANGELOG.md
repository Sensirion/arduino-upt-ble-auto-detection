# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.3.0]
### Fixed
- Use c++17
- Fix library versions

### Changed
- Define namespace
- Upgraded NimBLE to 2.x
- Bumped UPT core to 0.9.3
- Renamed `SensiScan` to `SensirionBleScanner`
- Updated usage example

## [0.2.0] 
### Fixed
- Fix memory leak in NimBLE by calling clearResults after scan results are processed.
- Use unit64_t for address (device id) instead of std::string
- Fix several clang tidy issues
- Update example to call keepAlive regularly. This ensures scanning does not stop due to errors.
- Fixed detection of 'Sensirion MyCO2' gadgets.

## [0.1.0] 
### Added
- Initial release


