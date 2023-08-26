# Base64 Encoding and Decoding

This repository contains a C program for encoding and decoding data in Base64 format. Base64 is a widely used encoding scheme that represents binary data as a text string, making it suitable for transporting binary data over text-based protocols like email or HTTP.

## Usage

To use the Base64 encoder and decoder, follow these steps:

1. Clone this repository to your local machine.
2. Navigate to the repository directory.
3. Compile the program using a C compiler. For example, using GCC:

    ```bash
    gcc -o base64 main.c
    ```

4. Run the program with the following command:

    ```bash
    ./base64 <input>
    ```

   Replace `<input>` with the data you want to encode or decode.

## Features

- `base64_encode`: Encodes binary data into Base64 format.
- `base64_decode`: Decodes Base64 encoded strings back to binary data.

## Examples

### Encoding

```bash
./base64 "Hello, World!"
# Encoded Base64: SGVsbG8sIFdvcmxkIQ==
```

###Decoding

```bash
./base64 "SGVsbG8sIFdvcmxkIQ=="
# Decoded Value: Hello, World!
```
