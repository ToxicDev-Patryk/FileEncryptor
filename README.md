# FileEncryptor
Simple File Encryptor

## Features
- Modular Design: The encryptor is designed using an abstract base class (Encryptor) and multiple derived classes (SimpleEncryptor, CaesarEncryptor, and ReverseEncryptor) that implement different encryption algorithms. This modular approach allows for easy addition of new encryption methods.CopyCopyCopyCopy

- Multiple Encryption Algorithms:

- SimpleEncryptor: Implements a basic XOR encryption method.
- CaesarEncryptor: Uses the Caesar cipher technique, shifting characters based on the key.
- ReverseEncryptor: Encrypts data by reversing the string.
- Key Generation: The generateRandomKey function creates a random key of specified length using a combination of alphanumeric characters, enhancing security.Copy

- File I/O Operations: Functions writeFile and readFile handle reading from and writing to files in binary mode, making it suitable for various types of data.CopyCopy

- Encryption and Decryption Workflow: The encryptFile and decryptFile functions manage the entire process of encryption and decryption, including handling the random key and applying multiple encryption methods in sequence.CopyCopy

- Key Encryption: The random key used for the encryption is itself encrypted using a SimpleEncryptor before being appended to the data, adding an extra layer of security.Copy

- Command-Line Interface: The program can be run from the command line, allowing users to specify whether to encrypt or decrypt files, as well as input and output file names.

- Memory Management: The code properly manages memory by deleting dynamically allocated Encryptor objects to prevent memory leaks.Copy

- Robust Error Handling: The program checks for valid command-line arguments and provides usage instructions, helping users avoid common mistakes.

- Support for Custom Output File: Users can specify a different output file for the encrypted or decrypted data, improving flexibility.
