# Crypto Opportunity Tracker CLI

![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg)

A simple, command-line interface (CLI) application written in C to track and manage opportunities in the crypto market. This project is a proof-of-concept for a decentralized opportunity board, allowing users to log findings across various categories.

## Features

- **Add Opportunities**: Add new findings with a category, title, and URL.
- **View Opportunities**: List all the opportunities you've saved.
- **Persistent Storage**: Your data is automatically saved to a `opportunities.dat` file and loaded every time you start the app.
- **Cross-Platform**: Compiles and runs on any system with a C compiler (Windows, macOS, Linux).

## Categories

You can log opportunities under any category you want, such as:
- Airdrops
- NFT Mints
- DeFi Yield Farms
- Node Setups
- ICOs/IDOs

## Getting Started

### Prerequisites

You need a C compiler (like **GCC**) and the **`make`** build tool.

- **On macOS**: Open Terminal and run `xcode-select --install`.
- **On Debian/Ubuntu**: Open Terminal and run `sudo apt-get install build-essential`.
- **On Windows**: You can use WSL (Windows Subsystem for Linux) or MinGW.

### Compilation and Running

1.  **Clone the repository:**
    ```sh
    git clone <your-repository-url>
    cd <your-repository-directory>
    ```

2.  **Compile the project:**
    Simply run the `make` command. This will use the `Makefile` to compile the source code and create an executable file named `opportunity_tracker`.
    ```sh
    make
    ```

3.  **Run the application:**
    ```sh
    ./opportunity_tracker
    ```
    Or you can use the shortcut:
    ```sh
    make run
    ```

4.  **Clean up:**
    To remove the compiled files and the data file, run:
    ```sh
    make clean
    ```

## How It Works

The application uses a dynamic array of C `structs` to hold the opportunity data in memory. When you exit the program, the entire array is written to a binary file (`opportunities.dat`). The next time you run the application, it checks for this file and loads its contents back into memory, giving you persistent storage.
