# SQLSplit
### SQL File Splitter and Recombiner

This project provides a utility for splitting a large SQL file into smaller SQL files, each containing the SQL script for creating a separate database table. 
Additionally, it can recombine those smaller SQL files back into a single SQL file.

## Features

- Split a large SQL file that contains multiple `CREATE TABLE` statements into separate SQL files, one for each table.
- Optionally capture and include SQL header lines in each output file.
- Recombine the smaller SQL files back into a single SQL file.
- Display the progress of the file processing in the terminal.
- Command line interface for easy usage.

## Getting Started

### Prerequisites

- A C++17 compatible compiler.
- CMake for building the project (optional).

### Compilation

Clone the repository and navigate to the project directory. Run the following commands to compile the code:

```sh
mkdir build
cd build
cmake ..
make
```

### Releases

[Releases](https://github.com/claitz/SQLSplit/releases/) are available for Windows, macOS, and Linux but we encourage you to compile the code yourself.

## Usage

### As a CLI tool

You can use the compiled binary directly from the command line:

#### Usage

```sh
SQLSplit <command> <options>
```

#### Commands:

- `split` - Splits a SQL file into multiple table files.
- `combine` - Combines multiple table files into a single SQL file.
- 
#### Options:

- For split: `<input_file> [output_directory]`
- For combine: `<input_directory> <output_file>`

#### Examples:

```sh
SQLSplit split database.sql output_directory
SQLSplit combine output_directory combined_database.sql
```


### As a Library

You can also use the project as a library in your own C++ project.

Include `FileUtil.h` in your C++ project and use the `FileUtil::splitSQL` and `FileUtil::recombineSQL` methods.

#### Example

```cpp
#include "FileUtil.h"

int main() {
    // Split SQL file
    std::vector<std::string> outputFiles = FileUtil::splitSQL("path/to/large/sql/file.sql", "path/to/output/directory");

    // Recombine SQL files
    FileUtil::recombineSQL(outputFiles, "path/to/recombined/sql/file.sql");

    return 0;
}
```

## Contributing
Contributions are welcome. Please open an issue or submit a pull request if you would like to contribute to the project.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.