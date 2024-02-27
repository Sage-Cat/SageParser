# SageParser

Application for parsing some spesific CSV, XML, JSON, XLSX documents

## Building 

Build conan:
```
conan install . --output-folder=build --build=missing
```

Configure cmake with conan deps:
```
cd build
cmake .. --preset conan-debug
```

Build project:
```
cmake --build .
```

## Development

### DbC (Design by Contract)

#### Library-Wide Contract
- **Preconditions:** Ensure valid configurations for paths, file formats (xlsx, csv, xml, json), and necessary resources (memory, permissions).
- **Postconditions:** Library initializes successfully, providing file reading/writing and data processing capabilities.
- **Invariants:** Library maintains a valid state, ensuring data integrity and format compatibility.

#### Contracts for Each Object Type

##### Readers
- **Preconditions:** File must exist, be accessible, and in a supported format.
- **Postconditions:** File content is read into standard Table format, or an std::runtime_error exception is thrown.
- **Invariants:** File integrity is maintained without altering content.

##### Writers
- **Preconditions:** Table in a valid state, output path accessible.
- **Postconditions:** Data written to file in specified format or an std::runtime_error exception is thrown.
- **Invariants:** Data format integrity during the write process.

##### IProcessors (Input Processors)
- **Preconditions:** Non-standard format Table provided that should match with selected IProcessor.
- **Postconditions:** Table transformed to standard format, or an std::invalid_argument exception is thrown.
- **Invariants:** Logical structure of data maintained, no data loss.

##### OProcessors (Output Processors)
- **Preconditions:** Standard Table format provided for output.
- **Postconditions:** Table transformed to desired output format.
- **Invariants:** Integrity of Table's logical structure maintained, adapted to output requirements without loss.
